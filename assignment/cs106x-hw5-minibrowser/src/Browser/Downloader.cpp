#include "Downloader.h"
#include "urlstream.h"
#include "error.h"
#include "strlib.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <unordered_map>
using namespace std;

namespace {
    /* Links are just a source/target pair. */
    struct Link {
        std::string displayText;
        std::string target;
    };

    /* Raw page data consists of a pair of text, plus a map locating where the links occur. */
    struct RawPage {
        std::string text;
        std::unordered_map<std::size_t, Link> links;
    };

    /* Special pages for things like "the program started," "we screwed up," etc. */
    const unordered_map<string, RawPage> kSpecialPages = {
        {
          "special:error",
          {
            "== Internal Error ==\n"
            "Sorry! Something went wrong downloading that page.\n\n"
            "You might not be connected to the internet.\n\n"
            "This is an error on our end. You didn't do anything wrong.", {}
          }
        },
        {
          "special:welcome",
          {
            "== Welcome to MiniBrowser! ==\n"
            "This is a mini Wikipedia browser. Use the top URL bar to select which page "
            "to visit, or navigate using links or the forward/back buttons.", {}
          }
        },
        {
          "special:notfound",
          {
            "== Page Not Found ==\n"
            "Sorry, but we couldn't find that page on Wikipedia.\n\n"
            "It's possible that you mistyped the page name. Check the spelling and try again.\n\n"
            "Remember that Wikipedia article titles are case-sensitive, so \"kirk's dik-dik\""
                "and \"Kirk's Dik-Dik\" represent different pages.\n\n", {}
          }
        },
    };

    /* Exception type used to signal that a page doesn't exist. */
    class PageDoesntExistException: public exception {
    public:
        virtual const char* what() const noexcept override {
            return "Page does not exist.";
        }
    };

    /* User-Agent string to set. Wikipedia requires us to provide a custom User-Agent string
     * with contact information.
     */
    const string kUserAgentString = "MiniBrowser, a CS assignment developed at Stanford. Contact: troccoli@stanford.edu";

    /* Given a piece of text, encodes it in a format suitable for use in a URL. */
    string urlSanitize(const string& text) {
        ostringstream result;
        for (char ch: text) {
            result << "%" << setfill('0') << setw(2) << hex << (unsigned int)(unsigned char)ch;
        }

        return result.str();
    }

    /* Given a unicode code point, returns a UTF-8 encoding of that code point. */
    string toUTF8(uint32_t charCode) {
        ostringstream result;

        /* Anything 7 bits or less just gets directly mapped to itself. */
        if (charCode < (1u << 7)) {
            result << char(charCode);
        }
        /* Anything using 11 bits or less gets broken into
         * 110xxxxx 10xxxxxx
         */
        else if (charCode < (1u << 11)) {
            uint32_t highFive = charCode >> 6;
            uint32_t lowSix   = charCode & 0b111111;

            result << char(highFive | 0b11000000) << char(lowSix | 0b10000000);
        }
        /* Anything using 16 bits or less gets broken into
         * 1110xxxx 10xxxxxx 10xxxxxx
         */
        else if (charCode < (1u << 16)) {
            uint32_t highFour = charCode >> 12;
            uint32_t midSix   = (charCode >> 6) & 0b111111;
            uint32_t lowSix   = charCode & 0b111111;

            result << char(highFour | 0b11100000)
                   << char(midSix | 0b10000000)
                   << char(lowSix | 0b10000000);
        }
        /* Anything using 21 bits or less gets broken into
         * 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
         */
        else if (charCode < (1u << 22)) {
            uint32_t highThree = charCode >> 18;
            uint32_t topSix    = (charCode >> 12) & 0b111111;
            uint32_t midSix    = (charCode >>  6) & 0b111111;
            uint32_t lowSix    = charCode & 0b111111;

            result << char(highThree | 0b11110000)
                   << char(topSix | 0b10000000)
                   << char(midSix | 0b10000000)
                   << char(lowSix | 0b10000000);
        }
        else {
            error("Unicode value out of range: " + to_string(charCode));
        }

        return result.str();
    }

    /* Given a string with Wikipedia-style escapes (\n, \", \uXXXX, \\), converts that
     * string into a UTF-8 encoded equivalent string.
     */
    string resolveEscapesIn(const string& text) {
        istringstream input(text);
        ostringstream result;

        /* Process characters as they appear. */
        for (char ch; input.get(ch); ) {
            /* If this isn't an escape character, there's nothing to do. */
            if (ch != '\\') result.put(ch);
            else {
                char type;
                if (!input.get(type)) error("Unresolved escape sequence found.");

                /* See what this is. */
                if      (type == 'n')  result.put('\n');
                else if (type == 't')  result.put(' ');
                else if (type == '\\') result.put('\\');
                else if (type == '"')  result.put('"');
                else if (type == 'u') {
                    /* The next four bytes will determine the unicode value. We can't use
                     * regular formatted extraction here because we may have a string like
                     * \u002288, which is meant to be interpreted as '\u0022' followed by
                     * two copies of the character '8'.
                     *
                     * Instead, we'll pull four characters into a string and then convert
                     * that string to an integer.
                     */
                    string strCharCode;
                    input >> setw(4) >> strCharCode;
                    if (!input || strCharCode.size() != 4) error("Malformed \\u escape.");

                    uint32_t charCode = stringToInteger(strCharCode, 16);

                    /* There are two options here. First, we may have something that's part of a
                     * surrogate pair (a pair of two 16-bit escape sequences that codes for a
                     * single 21-bit Unicode character). In that case, there's more to decode.
                     * Otherwise, this is a singleton and can be decoded directly.
                     */

                    /* If this is part of a surrogate pair, read the other half of the pair and use
                     * that to compute the net character code.
                     */
                    if (charCode >= 0xD800 && charCode <= 0xDFFF) {
                        /* Confirm this is the first half of a surrogate pair. */
                        if (charCode >= 0xDC00) error("Found second half, but not first half, of surrogate pair.");

                        /* Confirm that this is immediately followed by \uXXXX. */
                        input >> setw(6) >> strCharCode;
                        if (!input || strCharCode.size() != 6 || !startsWith(strCharCode, "\\u")) {
                            error("Found first half, but not second half, of a surrogate pair.");
                        }

                        /* Decode the numeric value of the second half. */
                        uint32_t secondPair = stringToInteger(strCharCode.substr(2), 16);
                        if (secondPair < 0xDC00 || secondPair > 0xDFFF) error("Second surrogate out of range.");

                        /* Reconstruct the code point. */
                        charCode = 0x10000 + ((charCode - 0xD800) << 10) + (secondPair - 0xDC00);
                    }

                    /* By this point, we know the character code that needs to be mapped to UTF-8. */
                    result << toUTF8(charCode);
                }
                else error("Unknown escape sequence: " + string(1, type));
            }
        }

        return result.str();
    }

    string downloadURL(const string& url) {
        iurlstream input;

        /* Wikipedia requires a custom User-Agent string. */
        input.setHeader("User-Agent", kUserAgentString);
        input.open(url);

        if (!input) error("Error opening URL " + url + ": " + to_string(input.getErrorCode()));

        ostringstream buffer;
        buffer << input.rdbuf();

        return buffer.str();
    }

    /* Given the full HTML of a Wikipedia article, extracts the contents of that article. */
    string extractBodyFrom(const string& text) {
        /* Look for "<textarea", find the first close brace after it, and then grab everything
         * up through the start of the </textarea> tag.
         */
        size_t textareaStart = text.find("<textarea");
        if (textareaStart == string::npos) error("Couldn't find <textarea> tag.");

        size_t start = text.find('>', textareaStart);
        if (start == string::npos) error("Couldn't find end to <textarea> tag.");

        size_t end = text.find("</textarea>", start);
        if (end == string::npos) error("Couldn't find </textarea> tag.");

        return { text.begin() + start + 1, text.begin() + end };
    }

    /* Given a string, returns a new string formed by resolving all HTML entities (or replacing the
     * unknown entities with ?'s).
     */
    string fixEntitiesIn(string article) {
        static const vector<pair<string, string>> kReplacements = {
            { "&lt;",       "<" },
            { "&gt;",       ">" },
            { "&nbsp;",     " " },
            { "&amp;lt;",   "<" },
            { "&amp;gt;",   ">" },
            { "&amp;nbsp;", " " },
            { "&amp;",      "&" } // <--  This must go last!
        };

        for (const auto& entry: kReplacements) {
            article = stringReplace(article, entry.first, entry.second);
        }

        return article;
    }

    string contentsOf(const string& articleTitle) {
        auto editPageContents = downloadURL("https://en.wikipedia.org/w/index.php?title=" + urlSanitize(articleTitle) + "&action=edit");
        return fixEntitiesIn(extractBodyFrom(editPageContents));
    }

    string plaintextOf(const string& articleTitle) {
        string contents = downloadURL("https://en.wikipedia.org/w/api.php?action=query&format=json&titles=" + urlSanitize(articleTitle) + "&prop=extracts&explaintext&exlimit=1");

        /* We now have the file contents. We can check whether the page is missing by looking
         * for the string "missing":"", which is only sent over if the page can't be found.
         */
        if (contents.find(R"(missing":"")") != string::npos) throw PageDoesntExistException();

        /* The body of the article is in a section labeled "extract." */
        string header = R"("extract":")";
        size_t start = contents.find(header);

        if (start == string::npos) error("Can't find header.");

        size_t endBufferSize = 5; // "}}}}
        if (start + endBufferSize > contents.size()) error("Content doesn't align as expected.");

        return resolveEscapesIn({ contents.begin() + start + header.size(), contents.end() - endBufferSize });
    }


    vector<Link> linksIn(const string& articleTitle) {
        string body = contentsOf(articleTitle);
        vector<Link> result;
        for (size_t i = 0; i = body.find("[[", i), i != string::npos; ) {
            /* There are two formats we could be seeing:
                 *   [[ the actual article name ]]
                 *   [[ the real article name | the display name ]]
                 * Find the nearest close braces and see if there's a | in-between.
                 */
            size_t linkEnd = body.find("]]", i);
            if (linkEnd == string::npos) error("Unterminated link.");

            size_t pipe = body.find('|', i);
            string target;
            string text;

            if (pipe != string::npos && pipe < linkEnd) {
                /* Extract the actual target and the link text. */
                target = trim({ body.begin() + i + 2, body.begin() + pipe });
                text   = trim({ body.begin() + pipe + 1, body.begin() + linkEnd });
            } else {
                target = text = trim({ body.begin() + i + 2, body.begin() + linkEnd });
            }

            /* Certain links aren't needed / supported and can be skipped. */
            if (!startsWith(target, "Category:") &&
                !startsWith(target, "File:") &&
                !startsWith(target, "Talk:") &&
                !startsWith(target, "wiki:")) {

                /* Trim off any hash marks from the target. */
                size_t hash = target.find('#');
                if (hash != string::npos) {
                    target = target.substr(0, hash);
                }

                result.push_back({ text, target });
            }
            i = linkEnd + 2;
        }
        return result;
    }

    /* Given a page, returns the name of the page that we should actually look up. */
    string redirectTargetFor(const string& articleTitle) {
        string contents = downloadURL("https://en.wikipedia.org/w/api.php?action=query&format=json&titles=" + urlSanitize(articleTitle) + "&redirects");

        /* The JSON string should contain something of the form "title":"[article name]". */
        string header = R"("title":")";
        size_t index = contents.find(header);

        if (index == string::npos) error("Can't find redirect header.");

        index += header.length();

        string result;

        /* Keep reading characters, accumulating them into the result. Convert escaped quotes into quotes. */
        while (true) {
            if (index == contents.size()) error("Unterminated JSON string.");
            if (contents[index] == '"') break;
            if (contents[index] == '\\') {
                if (index + 1 == contents.size()) error("Malformed JSON string.");
                if (contents[index + 1] == '"') {
                    result += '"';
                    index += 2; // Skip \"
                    continue;
                }
            }
            result += contents[index];
            index++;
        }

        return resolveEscapesIn(result);
    }

    RawPage downloadRemotePage(const string& articleTitle) {
        /* First, see if we need to do a redirect. */
        auto targetPage = redirectTargetFor(articleTitle);

        auto text = plaintextOf(targetPage);
        unordered_map<size_t, Link> links;

        for (auto link: linksIn(targetPage)) {
            /* Find an occurrence of the text. */
            size_t index = text.find(link.displayText);
            while (index != string::npos) {
                /* It's possible that something has already been tagged here. Use the rule of maximal
                 * munch to break ties.
                 */
                auto itr = links.find(index);
                if (itr == links.end() || itr->second.displayText.size() < link.displayText.size()) {
                    links[index] = link;
                    break;
                }

                /* Otherwise, skip forward. */
                index = text.find(link.displayText, index + 1);
            }
        }

        return { text, links };
    }

    vector<HTMLToken> tokenize(const RawPage& page) {
        vector<HTMLToken> result;

        for (size_t i = 0; i < page.text.size(); ) {
            /* If there's a link here, scan to the end of the link and use that as a token. */
            auto itr = page.links.find(i);
            if (itr != page.links.end()) {
                HTMLToken token;
                token.text = itr->second.displayText;
                token.attributes = {{ "Link", itr->second.target }};
                result.push_back(token);

                /* Skip past the text of this token. */
                i += itr->second.displayText.length();
            }
            /* Otherwise, if this is a space character, make it its own token. */
            else if (isspace(page.text[i])) {
                result.push_back({ string(1, page.text[i]) });
                i++;
            }

            /* Otherwise, scan until we hit EOF, whitespace, or the start of a link */
            else {
                size_t end = i + 1;
                while (end < page.text.size() && !isspace(page.text[end]) && !page.links.count(end)) {
                    end++;
                }

                result.push_back({ {page.text.begin() + i, page.text.begin() + end} });
                i = end;
            }
        }
        return result;
    }

    /* Given an article title, returns the raw data from that article (plaintext and
     * link info.)
     */
    RawPage rawDataFrom(const string& articleTitle) {
        /* If the requested page is one of the special pages, just go return it. */
        if (kSpecialPages.count(articleTitle)) {
            return kSpecialPages.at(articleTitle);
        }

        try {
            return downloadRemotePage(articleTitle);
        } catch (const PageDoesntExistException& ) {
            return kSpecialPages.at("special:notfound");
        } catch (const exception& e) {
            return kSpecialPages.at("special:error");
        }
    }
}

vector<HTMLToken> downloadPage(const string& articleTitle) {
    return tokenize(rawDataFrom(articleTitle));
}

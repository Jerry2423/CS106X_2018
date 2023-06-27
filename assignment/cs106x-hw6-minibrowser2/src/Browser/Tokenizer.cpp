#include "Tokenizer.h"
using namespace std;

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
            result.push_back({ string(1, page.text[i]), {} });
            i++;
        }

        /* Otherwise, scan until we hit EOF, whitespace, or the start of a link */
        else {
            size_t end = i + 1;
            while (end < page.text.size() && !isspace(page.text[end]) && !page.links.count(end)) {
                end++;
            }

            result.push_back({ {page.text.begin() + i, page.text.begin() + end}, {} });
            i = end;
        }
    }
    return result;
}

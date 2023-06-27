#pragma once

#include <string>
#include <unordered_map>
#include <map>
#include <sstream>
#include "encoding.h"

struct HTMLToken {
    std::string text;
    std::map<std::string, std::string> attributes;
};

/* Links are just a source/target pair. */
struct Link {
    std::string displayText;
    std::string target;
};

/* Raw page data consists of a pair of text, plus a map locating where the links occur.
 * RawPages also have the ability to compress and uncompress themselves. */
struct RawPage {
    std::string text;
    std::unordered_map<std::size_t, Link> links;
    bool compressed;
    size_t decompressedByteSize;

    RawPage(const std::string& text, const std::unordered_map<std::size_t, Link>& links) {
        this->text = text;
        this->links = links;
        decompressedByteSize = this->text.length();
        compressed = false;
    }

    RawPage() {
        this->text = "";
        decompressedByteSize = 0;
        compressed = false;
    }

    void compressPage() {
        if (!compressed) {
            std::istringstream input(text);
            ostringbitstream output;
            compress(input, output);
            text = output.str();
            compressed = true;
        }
    }

    void uncompressPage() {
        if (compressed) {
            istringbitstream input(text);
            std::ostringstream output;
            uncompress(input, output);
            text = output.str();
            compressed = false;
        }
    }
};

bool operator ==(const RawPage& page1, const RawPage& page2);
bool operator ==(const Link& page1, const Link& page2);

#pragma once

#include <string>
#include <map>
#include <vector>

struct HTMLToken {
    std::string text;
    std::map<std::string, std::string> attributes;
};

/**
 * Given the title of an article, returns the article with that title.
 *
 * The resulting WikipediaPage object is guaranteed to be valid. In the event of an error
 * downloading the page - either a failed network connection, or a bad page title, etc. -
 * this function will return an error page.
 */
std::vector<HTMLToken> downloadPage(const std::string& articleTitle);

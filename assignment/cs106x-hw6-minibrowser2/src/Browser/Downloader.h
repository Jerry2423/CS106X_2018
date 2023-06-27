#pragma once

#include <string>
#include "PageTypes.h"

/**
 * Given the title of an article, returns the raw article with that title.
 *
 * The resulting object is guaranteed to be valid. In the event of an error
 * downloading the page - either a failed network connection, or a bad page title, etc. -
 * this function will return an error page.
 */
RawPage downloadRawPage(const std::string& articleTitle);

#pragma once

#include "PageTypes.h"
#include <vector>

/**
 * Given a raw page, this function tokenizes the page into a format that can be displayed.
 */
std::vector<HTMLToken> tokenize(const RawPage& page);

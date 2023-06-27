#pragma once

#include "LineManager.h"
#include <memory>
#include <vector>

/**
 * Given a series of HTML tokens, assembles them into lines and returns a LineManager
 * holding those lines.
 *
 * @param pageContents The contents of the page, expressed as a sequence of HTMLTokens.
 * @param contentWidth The width of the area where that content will be displayed.
 * @return A LineManager configured to hold those lines.
 */
std::shared_ptr<LineManager> layOutPage(const std::vector<HTMLToken>& pageContents,
                                        double contentWidth);

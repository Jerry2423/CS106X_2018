#pragma once

#include <string>

namespace GraphicsConstants {
    /* Font to use for rendering text. */
    /* TODO: This is likely system-dependent. There doesn't seem to be a standardized
     * monospace font.
     */
    static const std::string kBrowserFont = "Monospaced";

    /* Font size. */
    static constexpr std::size_t kBrowserFontSize = 24;

    /* Font metrics - how wide and tall each character is. */
    static constexpr double kCharacterWidth  = kBrowserFontSize / 2;
    static constexpr double kCharacterHeight = kBrowserFontSize;

    /* Line spacing, which is greater than the character height for readability. */
    static constexpr double kLineSpacing = kBrowserFontSize * 1.25;

    /* Paragraph spacing, which is the amount of whitespace to put between paragraphs
     * initiated with a hard line break (\n).
     */
    static constexpr double kParagraphSpacing = kBrowserFontSize * 1.75;

    /* Number of rows and columns to display in the main window. */
    static constexpr std::size_t kDisplayedRows = 20;
    static constexpr std::size_t kDisplayedCols = 80;

    /* Size of the main window. */
    static constexpr double kWindowWidth  = kDisplayedCols * kCharacterWidth;
    static constexpr double kWindowHeight = kDisplayedRows * kLineSpacing;
}

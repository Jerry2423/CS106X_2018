#pragma once

#include "Panel.h"
#include "gwindow.h"
#include <string>
#include "ginteractors.h"

/* A type representing a text indicator for displaying compression information. */
class CompressPanel: public Panel {
public:
    CompressPanel(GWindow& window);

    /* Sets the currently-displayed compression savings. */
    void setInfo(size_t totalBytes, size_t compressedBytes);

private:
    /* Label that displays the compression savings in the cache */
    GLabel *compressLabel;
};

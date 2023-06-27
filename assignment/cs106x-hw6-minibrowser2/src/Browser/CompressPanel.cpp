#include "CompressPanel.h"
#include "strlib.h"
using namespace std;

CompressPanel::CompressPanel(GWindow& window) {
    compressLabel = new GLabel("Compression savings:");
    window.addToRegion(compressLabel,"SOUTH");
}

void CompressPanel::setInfo(size_t totalBytes, size_t compressedBytes) {
    int total = totalBytes;
    int diff = total - compressedBytes;
    double percentDiff = 1.0 * diff / total * 100;
    compressLabel->setText("Compression savings:  " + doubleToString(percentDiff) + "% (" + doubleToString(diff / 1000.0) + " KB)");
}

#include "Frame.h"
#include "error.h"
#include <memory>
using namespace std;

/* Frame implementation. */
Frame::Frame(double x, double y, double width, const HTMLToken& token) {
    theBounds = { x, y, width, Frame::kFrameHeight };
    theText = token.text;

    auto itr = token.attributes.find("Link");
    if (itr != token.attributes.end()) {
        theLink = itr->second;
    }
}

double Frame::x() const {
    return theBounds.getX();
}

double Frame::y() const {
    return theBounds.getY();
}

double Frame::height() const {
    return Frame::kFrameHeight;
}

double Frame::width() const {
    return theBounds.getWidth();
}

bool Frame::contains(double x, double y) const {
    return theBounds.contains(x, y);
}

bool Frame::contains(const GPoint& pt) const {
    return contains(pt.getX(), pt.getY());
}

string Frame::text() const {
    return theText;
}

bool Frame::isLink() const {
    return !theLink.empty();
}

string Frame::linksTo() const {
    return theLink;
}

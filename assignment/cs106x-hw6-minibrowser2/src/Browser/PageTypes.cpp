#include "PageTypes.h"

bool operator ==(const RawPage& page1, const RawPage& page2) {
    return page1.text == page2.text && page1.links == page2.links;
}

bool operator ==(const Link& link1, const Link& link2) {
    return link1.displayText == link2.displayText && link1.target == link2.target;
}

#include "LineManagerTests.h"
#include "LineManager.h"
#include "set.h"
#include <cmath>
#include <climits>
using namespace std;
ENABLE_TESTS();

namespace {
    /* Comparing two doubles directly using == is not a good idea because doubles
     * have some degree of inaccuracy. Instead, we'll use this handy little
     * function to do the check for us.
     */
    bool equal(double x, double y) {
        static const double kEpsilon = 0.00001;
        return fabs(x - y) < kEpsilon;
    }

    /* Converts a Vector to a Set. */
    Set<Line *> asSet(const Vector<Line *>& lines) {
        Set<Line *> result;
        for (auto line: lines) {
            result += line;
        }
        return result;
    }

    /* Simpler name for infinity. */
    const double kInfinity = numeric_limits<double>::infinity();
}

ADD_TEST("Correctly reports content height of a single line.") {
    /* Construct a single line. */
    Vector<Line *> lines = {
        new Line{ 0, 137 }
    };

    LineManager manager(lines);
    expect(equal(manager.contentHeight(), 137));
}

ADD_TEST("Correctly reports content height of a group of lines.") {
    /* Construct a collection of different lines with gaps in them. The only ones that should
     * matter are the very first and very last line.
     */
    Vector<Line *> lines = {
        new Line{ 0, 137 }, new Line{ 271, 314 }, new Line{ 867, 5309 }
    };

    LineManager manager(lines);

    /* We expect the height to be the difference between the highest highY and the
     * lowest lowY.
     */
    expect(equal(manager.contentHeight(), lines.back()->highY()));
}

ADD_TEST("Hit tests work on a single line.") {
    /* Make a list of a single line. */
    Vector<Line *> lines = {
        new Line{ 0, 137 }
    };

    /* Hit that line dead in the middle. */
    double probeY = (lines[0]->highY() + lines[0]->lowY()) / 2.0;

    LineManager manager(lines);

    /* Confirm we hit something at that position. */
    expect(manager.lineAt(probeY) == lines[0]);

    /* Now try hitting way above that line. */
    expect(manager.lineAt(-10000) == nullptr);

    /* Now try hitting way below that line. */
    expect(manager.lineAt(+10000) == nullptr);
}

ADD_TEST("Simple range queries work on a single line.") {
    /* Make a single-line list. */
    Vector<Line *> lines = {
        new Line{ 0, 137 }
    };

    LineManager manager(lines);

    /* Do a range search from -infinity to +infinity, which should return all the lines. */
    expect(manager.linesInRange(-kInfinity, +kInfinity) == lines);

    /* Do a range search far below the range, which should return nothing. */
    expect(manager.linesInRange(-10000, -8000).isEmpty());

    /* Do a range search far above the range, which should return nothing. */
    expect(manager.linesInRange(8000, 10000).isEmpty());
}

ADD_TEST("Simple range queries work on multiple lines.") {
    /* Make a single-line list. */
    Vector<Line *> lines = {
        new Line{ 0, 137 }, new Line{ 271, 314 }, new Line { 867, 5309 }
    };

    LineManager manager(lines);

    /* Do a range search from -infinity to +infinity, which should return all the lines. */
    auto matches = manager.linesInRange(-kInfinity, +kInfinity);
    expect(asSet(lines) == asSet(matches));

    /* Do a range search far below the range, which should return nothing. */
    expect(manager.linesInRange(-10000, -8000).isEmpty());

    /* Do a range search far above the range, which should return nothing. */
    expect(manager.linesInRange(8000, 10000).isEmpty());
}

ADD_TEST("Range queries preserve order.") {
    /* Make a single-line list. */
    Vector<Line *> lines = {
        new Line{ 0, 137 }, new Line{ 271, 314 }, new Line { 867, 5309 }
    };

    LineManager manager(lines);

    /* Do a range search from -infinity to +infinity, which should return all the lines. */
    expect(manager.linesInRange(-kInfinity, +kInfinity) == lines);
}

ADD_TEST("Range queries can isolate individual lines.") {
    /* Build a nice collection of evenly-spaced lines. */
    const int kNumRows = 5;
    const double kRowHeight = 50;
    const double kRowSpacing = 20;

    Vector<Line *> lines;
    for (int i = 0; i < kNumRows; i++) {
        lines += new Line { i * (kRowHeight + kRowSpacing),
                            i * (kRowHeight + kRowSpacing) + kRowHeight };
    }

    LineManager manager(lines);

    /* See if we can piece out each row. */
    const double kPadding = kRowSpacing / 2;
    for (int i = 0; i < kNumRows; i++) {
        double lowY  = i * (kRowHeight + kRowSpacing) - kPadding;
        double highY = i * (kRowHeight + kRowSpacing) + kRowHeight + kPadding;

        expect(manager.linesInRange(lowY, highY) == lines.subList(i, 1));
    }
}

ADD_TEST("Range queries can isolate groups of lines.") {
    /* Build a nice collection of evenly-spaced lines. */
    const int kNumRows = 5;
    const double kRowHeight = 50;
    const double kRowSpacing = 20;

    Vector<Line *> lines;
    for (int i = 0; i < kNumRows; i++) {
        lines += new Line { i * (kRowHeight + kRowSpacing),
                            i * (kRowHeight + kRowSpacing) + kRowHeight };
    }

    LineManager manager(lines);

    /* Grab the rows in groups of some size and make sure we find everything we need. */
    const double kPadding = kRowSpacing / 2;
    const int kNumToGrab  = 3;
    for (int i = 0; i + kNumToGrab <= kNumRows; i++) {
        double lowY  = i * (kRowHeight + kRowSpacing) - kPadding;
        double highY = (i + kNumToGrab - 1) * (kRowHeight + kRowSpacing) + kRowHeight + kPadding;

        expect(manager.linesInRange(lowY, highY) == lines.subList(i, kNumToGrab));
    }
}

ADD_TEST("Queries that overlap lines, but don't fully contain them, still find those lines.") {
    /* Build a nice collection of evenly-spaced lines. */
    const int kNumRows = 5;
    const double kRowHeight = 50;
    const double kRowSpacing = 20;

    Vector<Line *> lines;
    for (int i = 0; i < kNumRows; i++) {
        lines += new Line { i * (kRowHeight + kRowSpacing),
                            i * (kRowHeight + kRowSpacing) + kRowHeight };
    }

    LineManager manager(lines);

    /* Probe each row in a narrow band that runs through the row, not around it. */
    const double kPadding = kRowSpacing / 3;
    for (int i = 0; i < kNumRows; i++) {
        double lowY  = i * (kRowHeight + kRowSpacing) + kPadding;
        double highY = i * (kRowHeight + kRowSpacing) + kRowHeight - kPadding;

        expect(manager.linesInRange(lowY, highY) == lines.subList(i, 1));
    }
}

/* TODO: Add a bunch of your own custom tests here! Use this syntax:
 *
 *    ADD_TEST("Description of your test") {
 *        // code for your test
 *    }
 */

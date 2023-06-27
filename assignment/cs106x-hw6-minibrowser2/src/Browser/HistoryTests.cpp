#include "HistoryTests.h"
#include "History.h"
using namespace std;
ENABLE_TESTS();

ADD_TEST("Can navigate history forwards and backwards.") {
    History h;

    /* Add a bunch of strings to the history. */
    h.goTo("A");
    h.goTo("B");
    h.goTo("C");
    h.goTo("D");

    /* Go back to the start to replay those pages in reverse order. */
    expect(h.previous() == "C");
    expect(h.previous() == "B");
    expect(h.previous() == "A");

    /* Go all the way to the end to replay those pages in the same order. */
    expect(h.next() == "B");
    expect(h.next() == "C");
    expect(h.next() == "D");
}

ADD_TEST("Forward history changes in response to a deviation.") {
    History h;

    /* Add an initial history. */
    h.goTo("A");
    h.goTo("B");
    h.goTo("C");
    h.goTo("D");

    /* Back up two steps. We should now be at "B." */
    h.previous();
    expect(h.previous() == "B");

    /* Add in two new pages. */
    h.goTo("E");
    h.goTo("F");

    /* The history should now be A, B, E, F. */
    expect(h.previous() == "E");
    expect(h.previous() == "B");
    expect(h.previous() == "A");

    /* Go forwards. We should see B, E, and F. */
    expect(h.next() == "B");
    expect(h.next() == "E");
    expect(h.next() == "F");

    /* There should not be anything in front of us. */
    expect(!h.hasNext());
}

ADD_TEST("Browser history with a single page in it should not have next/previous.") {
    History h;

    h.goTo("A");

    expect(!h.hasNext());
    expect(!h.hasPrevious());

    expectError(h.next());
    expectError(h.previous());
}

/* TODO: Add a bunch of your own custom tests here! Use this syntax:
 *
 *    ADD_TEST("Description of your test") {
 *        // code for your test
 *    }
 */

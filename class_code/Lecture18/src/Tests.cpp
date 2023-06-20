#include "Tests.h"
#include "arraystack.h"

using namespace std;
ENABLE_TESTS();

// Initial stack should be empty
ADD_TEST("Create stack") {
    ArrayStack s;
    expect(s.isEmpty());
}

// Element pushed should be element popped
ADD_TEST("Create and add one element to stack") {
    ArrayStack s;
    s.push(1);
    expect(!s.isEmpty());
}

// Peek should return the topmost element as new elements are added
ADD_TEST("Peek should return topmost element") {
    ArrayStack s;
    s.push(1);
    expect(s.peek() == 1);

    s.push(2);
    expect(s.peek() == 2);
}

// An error should occur when peeking with no elements
ADD_TEST("Peek on empty stack") {
    ArrayStack s;
    expectError(s.peek());
}

// An error should occur when popping with no elements
ADD_TEST("Pop from empty stack") {
    ArrayStack s;
    expectError(s.pop());
}

// Should pop in reverse order of push
ADD_TEST("Push/pop multiple values") {
    ArrayStack s;
    for (int i = 0; i < 6; i++) {
        s.push(i);
    }

    for (int i = 5; i >= 0; i--) {
        expect(s.pop() == i);
    }

    expect(s.isEmpty());
}

// Make sure previous values are all properly overwritten
ADD_TEST("Push/pop and then push/pop with new values") {
    ArrayStack s;
    for (int i = 0; i < 6; i++) {
        s.push(i);
    }

    for (int i = 5; i >= 0; i--) {
        expect(s.pop() == i);
    }

    expect(s.isEmpty());

    for (int i = 0; i < 10; i++) {
        s.push(i);
    }

    for (int i = 9; i >= 0; i--) {
        expect(s.pop() == i);
    }

    expect(s.isEmpty());

    for (int i = 0; i < 3; i++) {
        s.push(i);
    }

    for (int i = 2; i >= 0; i--) {
        expect(s.pop() == i);
    }

    expect(s.isEmpty());
}

// Should just be curly braces
ADD_TEST("Output empty stack") {
    ArrayStack s;
    ostringstream stream;
    stream << s;
    expect(stream.str() == "{}");
}

// Should be curly braces containing one element with no commas
ADD_TEST("toString 1 element stack") {
    ArrayStack s;
    s.push(1);
    expect(s.toString() == "{1}");
}

// Should be comma-delimited elements contained in curly braces
ADD_TEST("toString multi-element stack") {
    ArrayStack s;
    for (int i = 0; i < 5; i++) {
        s.push(i);
    }

    expect(s.toString() == "{0, 1, 2, 3, 4}");
}

// Should be the same as the previous test, but in reverse order
ADD_TEST("toString multi-element stack reversed") {
    ArrayStack s;
    for (int i = 4; i >= 0; i--) {
        s.push(i);
    }

    expect(s.toString() == "{4, 3, 2, 1, 0}");
}

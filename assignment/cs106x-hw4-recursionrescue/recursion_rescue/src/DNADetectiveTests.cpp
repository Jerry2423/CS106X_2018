#include "DNADetectiveTests.h"
#include "RecursionToTheRescue.h"
#include <string>

using namespace std;
ENABLE_TESTS();

ADD_TEST("Converting a blank string to a non-blank one") {
    string first = "";
    string second = "GAGATACT";
    int distance = 8;
    expect(approximatelyMatch(first, second, distance));
}

ADD_TEST("Hard No") {
    string first = "ACTGTACTGACTGACTG";
    string second = "CATGCATGACTATGCATC";
    int distance = 8;
    expect(!approximatelyMatch(first, second, distance));
}

ADD_TEST("Hard Yes") {
    string first = "ACTGTACTGACTGACTG";
    string second = "CATGCATGACTATGCATC";
    int distance = 9;
    expect(approximatelyMatch(first, second, distance));
}

ADD_TEST("Medium No") {
    // Fastest is GATTACA -> GAGTTACA -> GAGATACA -> GAGATACT
    string first = "GATTACA";
    string second = "GAGATACT";
    int distance = 2;
    expect(!approximatelyMatch(first, second, distance));
}

ADD_TEST("Medium Yes") {
    // Fastest is GATTACA -> GAGTTACA -> GAGATACA -> GAGATACT
    string first = "GATTACA";
    string second = "GAGATACT";
    int distance = 3;
    expect(approximatelyMatch(first, second, distance));
}
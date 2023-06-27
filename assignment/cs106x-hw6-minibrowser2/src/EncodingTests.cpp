#include "EncodingTests.h"
#include "encoding.h"
#include "huffmanutil.h"
#include <sstream>
using namespace std;
ENABLE_TESTS();

/* A tree for a 1 letter file should have three nodes: root, letter, PSEUDO_EOF */
ADD_TEST("Encoding tree for one letter file") {
    istringstream input("c");
    HuffmanNode *root = buildEncodingTree(input);
    expect(root != nullptr);
    expect(root->character = NOT_A_CHAR);
    expect(root->count == 2);

    expect(root->zero != nullptr);
    expect(root->zero->character == 'c');
    expect(root->zero->count == 1);
    expect(root->zero->zero == nullptr);
    expect(root->zero->one == nullptr);

    expect(root->one != nullptr);
    expect(root->one->character == PSEUDO_EOF);
    expect(root->one->count == 1);
    expect(root->one->zero == nullptr);
    expect(root->one->one == nullptr);

    freeTree(root);
}

/* A one letter file should be two bytes, with the rest padded by the operating system. */
ADD_TEST("Encode data for one letter file") {
    istringstream treeInput("c");
    HuffmanNode *root = buildEncodingTree(treeInput);

    istringstream encodeInput("c");
    ostringbitstream out;
    encodeData(encodeInput, root, out);

    /* We can use bitsToBytes in huffmanutil.h to convert the compressed bits to actual 1 and 0 characters. */
    expect(bitsToBytes(out.str()) == "01000000");

    freeTree(root);
}

/* A one letter file should be properly decoded by reading the first two bits. */
ADD_TEST("Decode data for one letter file") {
    istringstream treeInput("c");
    HuffmanNode *root = buildEncodingTree(treeInput);

    /* We can use bytesToBits in huffmanutil.h to convert the actual 1 and 0 characters to bit 1s and 0s. */
    istringbitstream in(bytesToBits("01000000"));
    ostringstream out;
    decodeData(in, root, out);
    expect(out.str() == "c");

    freeTree(root);
}

/* Compressing and decompressing a one-letter file should yield the identical text. */
ADD_TEST("Compress/uncompress for one letter file") {
    istringstream input("c");
    ostringbitstream bitOutput;
    compress(input, bitOutput);
    istringbitstream bitInput(bitOutput.str());
    ostringstream output;
    uncompress(bitInput, output);
    expect(output.str() == "c");
}

/* After compressing and decompressing a one letter file, all HuffmanNodes should be gone. */
ADD_TEST("All memory should be freed for a one letter file") {
    HuffmanNode::resetCreatedDeletedCounts();
    istringstream input("c");
    ostringbitstream bitOutput;
    compress(input, bitOutput);
    istringbitstream bitInput(bitOutput.str());
    ostringstream output;
    uncompress(bitInput, output);

    /* We can use HuffmanNode's built in counting to track how many nodes are created and deleted.
     * Check out huffmannode.h for more information! */
    expect(!HuffmanNode::hasNodesStillCreated());
}



/* TODO: Add a bunch of your own custom tests here! Use this syntax:
 *
 *    ADD_TEST("Description of your test") {
 *        // code for your test
 *    }
 */

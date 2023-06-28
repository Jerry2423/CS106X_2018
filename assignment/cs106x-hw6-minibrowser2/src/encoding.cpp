// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "encoding.h"
#include "bitstream.h"
#include "filelib.h"
#include "hashmap.h"
#include "huffmannode.h"
#include "map.h"
#include "priorityqueue.h"
#include <istream>
using namespace std;
using char_t = int;

Map<char_t, int> freqTableGen(istream& input) {
    Map<char_t, int> dic;
    char ch;
    while (input.get(ch)) {
        if (dic.containsKey(ch)) {
            dic[ch] += 1;
        } else {
            dic[ch] = 1;
        }
    }
    rewindStream(input);
    return dic;
}

HuffmanNode* recEncodingTree(PriorityQueue<HuffmanNode*>& pq) {
    if (pq.size() == 1) {
        return pq.dequeue();
    } else {
        auto left = pq.dequeue();
        auto right = pq.dequeue();
        auto new_parent = new HuffmanNode(NOT_A_CHAR, left->count+right->count, left, right);
        pq.enqueue(new_parent, new_parent->count);
        return recEncodingTree(pq);
    }
}

HuffmanNode* buildEncodingTree(istream& input) {
    // TODO: remove the below lines and implement this function

    // count occurences
    Map<char_t, int> dic = freqTableGen(input);
    dic[PSEUDO_EOF] = 1;
    // cout << dic << endl;

    // store the counts into created nodes, and put the ptr into pq
    PriorityQueue<HuffmanNode*> pq;
    for (const auto& i : dic) {
        HuffmanNode* temp = new HuffmanNode(i, dic[i]);
        pq.enqueue(temp, temp->count);
    }
    // cout << "queue:" << endl;
    // for (auto i : pq) {
    //     cout << i->character << " " << i->count << endl;
    // }
    // // pq.enqueue(new HuffmanNode(PSEUDO_EOF, 1), 1);
    // 
    // // convert it into tree
    // while (pq.size() > 1) {
    //     // remove the front 2 node and store it
    //     HuffmanNode* first = pq.dequeue();
    //     HuffmanNode* second = pq.dequeue(); 
    //     // create a new parent whose left and right is the removed nodes
    //     HuffmanNode* new_parent = new HuffmanNode(NOT_A_CHAR, first->count+second->count, first, second);
    //     // put the new node into the pq
    //     pq.enqueue(new_parent, new_parent->count);
    // }

    return recEncodingTree(pq);
}

void encodeHelper(HuffmanNode* curr, string& record, Map<char_t, string>& dic) {
    if (curr) {
        if (curr->isLeaf()) {
            dic[curr->character] = record;
        }
        // for zero: choose explore unchoose
        record += '0';
        encodeHelper(curr->zero, record, dic);
        record.pop_back();

        // for onr: choose explore unchoose
        record += '1';
        encodeHelper(curr->one, record, dic);
        record.pop_back();
    }
}

void encodeData(istream& input, HuffmanNode* encodingTree, obitstream& output) {
    // TODO: remove the below lines and implement this function
    string record;
    Map<char_t, string> dic;
    encodeHelper(encodingTree, record, dic);
    
    char ch;
    int length = 0;
    while (input.get(ch)) {
        string bit_str = dic[ch];
        for (const auto& i : bit_str) {
            output.writeBit(i-'0');
            length += 1;
        }
    }
    rewindStream(input);
    for (const auto& i : dic[PSEUDO_EOF]) {
        output.writeBit(i-'0');
        length += 1;
    }
    if (length % 8 != 0) {
        for (int i = 0; i < (length/8+1)*8-length; i++) {
            output.writeBit(0);
        }
    }
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // TODO: remove the below lines and implement this function
    HuffmanNode* curr = encodingTree;
    while (curr && curr->character != PSEUDO_EOF && input) {
        // cout << "hi from decoding" << endl; 
        if (curr->isLeaf()) {
            output.put(curr->character);
            curr = encodingTree;
        } else {
            if (input.readBit() == 1) {
                curr = curr->one;
            } else {
                curr = curr->zero;
            }
        }
    }
}

void compress(istream& input, obitstream& output) {
    // TODO: remove the below lines and implement this function
    auto info = freqTableGen(input);
    output << info;
    auto root = buildEncodingTree(input);
    encodeData(input, root, output);
    freeTree(root);
    root = nullptr;
}

void uncompress(ibitstream& input, ostream& output) {
    // TODO: remove the below lines and implement this function
    Map<char_t, int> info;
    input >> info;
    // convert the info in the dic to a istream(string -> stream)
    string encode_info;
    for (const auto& i : info) {
        string temp(info[i], i);
        encode_info += temp;
    }
    // use the stream to build back the tree
    istringstream tree_info(encode_info);
    auto root = buildEncodingTree(tree_info);

    // decode data
    decodeData(input, root, output);
    // free memory
    freeTree(root);
}

void freeTree(HuffmanNode* node) {
    // TODO: remove the below lines and implement this function
    if (node) {
        freeTree(node->zero);
        freeTree(node->one);
        delete node;
    }
}

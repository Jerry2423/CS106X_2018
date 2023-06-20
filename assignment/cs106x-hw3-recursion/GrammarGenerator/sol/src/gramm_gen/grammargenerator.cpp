/*
 * File: grammargenerator.cpp
 * --------------------------
 * Name:
 * Section leader:
 * This file contains grammar generating code for CS106X HW3.
 */

#include "grammargenerator.h"
#include "collections/map.h"
#include "collections/vector.h"
#include "util/random.h"
#include "util/strlib.h"
#include <iostream>
#include <string>

using namespace std;
using token = string;
using rule = Vector<token>;
using symbol = string;
using grammar = Map<symbol,Vector<rule>>;

/**
 * Generates grammar for a given symbol a certain number of times given
 * a BNF input file.
 *
 * This will be called by grammarmain.cpp.
 *
 * @param input - Input stream of BNF file.
 * @param symbol - Symbol to generate
 * @param times - Number of times grammar is generated
 * @return Vector of strings of size times with random generations of symbol
 */


grammar getGrammar(istream& input) {
    string line;
    grammar dic;
    while (getline(input, line)) {
        Vector<rule> rules;
        // seperate line by ::=
        Vector<string> sp1 = stringSplit(line, "::=");
        //add the first part to the symbol key
        
        //seperate second part by |
        Vector<string> sp2 = stringSplit(sp1[1], "|");
        //go thourough the rules vector, for each, seperate by space, then push back to rules
        for (string s : sp2) {
            Vector<string> temp = stringSplit(s, " ");
            rules.add(temp);
        }
        //match the symbol with the key
        if (dic.containsKey(sp1[0])) {
            throw "repeated grammar rule for the same symbol";
        }
        dic[sp1[0]] = rules;
    }
    return dic;
}

rule selectRule(const grammar& guide, const symbol& flag) {
    return guide[flag][randomInteger(0, guide[flag].size()-1)];
}

void generateGrammarHelper(const symbol& flag, string& sentence, const grammar& guide) {
    if (!guide.containsKey(flag)) {
        sentence.append(flag);
        sentence.append(" ");
        return;
    } else {
        //select a rule based on symbol
        auto temp_rule = selectRule(guide, flag);
        //go through the rule
        for (const auto& i : temp_rule) {
            generateGrammarHelper(i, sentence, guide);
        }
        //call the function
    }
}

Vector<string> generateGrammar(istream& input, const string& symbol, int times) {
    // [TODO: delete the lines below this one and fill this function in. ]
    (void) input;
    (void) symbol;
    (void) times;
    auto info =getGrammar(input);
    cout << "grammar are shown below:" << endl;
    for (auto i : info) {
        cout << i << " " << info[i] << endl;
    }
    if (symbol.empty()) {
        throw "invalid symbol";
    }
    Vector<string> result;
    for (int i = 0; i < times; i++) {
        string sentence;
        generateGrammarHelper(symbol, sentence, info);
        result.add(trim(sentence));
    }

    return result;
}

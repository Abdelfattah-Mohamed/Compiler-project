#include <bits/stdc++.h>
#include "ProductionRule.cpp"
#include "../lexical analyzer generator/LexicalGeneratorBuilder.cpp"
using namespace std;
class CFG {
private:
    /// add helper functions
    string startSymbol;
    LexicalGeneratorBuilder *lexBuilder;
    unordered_set<string> terminals;
    unordered_map<string, vector<ProductionRule* > > nonTerminals;
    vector<ProductionRule* > productionRules;
    unordered_map<string, unordered_set<string>> firstSets;
    unordered_map<string, unordered_set<string>> FollowSets;
    unordered_map<string, unordered_map<string, ProductionRule>> ll1Table;
    // non terminal , <ternminal , production >
    vector<string> sententialLines; // result

public:
    CFG(LexicalGeneratorBuilder *_lex) {
    }
    // set  DS of terminals and nonterminals and production rules
    void parseGrammerFile(string grammerFile) {
    }
    void computeFirstSets() {
        unordered_set<string> vis;
        for (string term : terminals) {
            vis.insert(term);
            firstSets[term].insert(term);
        }
        for (pair<string, vector<ProductionRule *>> nonterminal : nonTerminals)
        {
            string str = nonterminal.first;
            unordered_set<string> st = recursivefirstSet(str,vis);
            firstSets[nonterminal.first] = st;
        }
    }
    unordered_set<string> recursivefirstSet(string nonTerm, unordered_set<string> &vis) {
        unordered_set<string> res;
        if (vis.count(nonTerm)) {
            return firstSets[nonTerm];
        }
        for (ProductionRule* pr : nonTerminals[nonTerm])  {
            vector<string > rhs = pr->getRhs();
            
        }
    }

    void computeFollowSets() {
    }
    void GenerateParseTable() {
    }
    void parseInput() {
    }
    void eliminateLeftRecursion() {
    }
    void eliminateLeftFactor() {
    }
};

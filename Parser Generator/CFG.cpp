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
    vector<ProductionRule> sententialLines; // result

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
        stack<string> non_term_st ;
        non_term_st.push("$");
        non_term_st.push(startSymbol);
        string next_token = lexBuilder->nextToken();
        while(true){
            string top_elem = non_term_st.top();

                if(top_elem.compare("$") == 0 && next_token.compare("$") == 0){
                    ///syso end of processing and accepted
                    break;
                }
                if(top_elem.compare("$") == 0 && next_token.compare("$") != 0){
                    ///syso end of processing not accepted part of the input
                    ///isnot matched(the stack is empty while the ip is not)
                    break;
                }
                //case top is terminal
                if(terminals.find(top_elem) != terminals.end()){
                        //case matches the i/p
                        if(top_elem.compare(next_token) == 0){
                            ///syso matched  next_token
                            next_token = lexBuilder->nextToken();
                            non_term_st.pop();

                        }else{ // if they dont match

                            ///syso "Warning" missing  top_elem and inserted
                            non_term_st.pop();
                        }

                }else{ //case top is non-terminal
                    unordered_map<string, ProductionRule> row = ll1Table[top_elem];
                    ///case entry found
                    if(row.find(next_token) != row.end()){
                            if(/*not sync production rule*/){
                            ProductionRule pr = row[next_token];
                            sententialLines.push_back(pr);
                            ///syso production rule nfso
                            next_token = lexBuilder->nextToken();
                            non_term_st.pop();
                            if(/*production rule is not epsilon*/){
                                vector<string> rhs= pr.getRhs();
                                for(int counter =rhs.size()-1; counter >=0 ;counter--){
                                    non_term_st.push(rhs[counter]);
                                }
                            }
                    }else{///sync
                        ///syso error illegal non terminal top_elem , top_elem discarded
                        non_term_st.pop();
                    }
                    }else{///entry is empty

                        if(next_token.compare("$") == 0){
                            ///syso not accepted ip ended while stack is not empty yet part of the ip is missing
                            break;
                        }
                        ///syso error illegal non terminal top_elem , next_token discarded
                        next_token = lexBuilder->nextToken();
                    }
                }


        }

    }
    void eliminateLeftRecursion() {
    }
    void eliminateLeftFactor() {
    }
};

#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include<bits/stdc++.h>

using namespace std;

class LexicalAnalyzer {
public:
    LexicalAnalyzer(vector<unordered_map<char, int> > _dfa, int _q0, unordered_map<int, string>, string _input);
    vector<string> getTokens();
    string tokenize(string ip);
    void tock_all(string input);

protected:

private:
    vector<unordered_map<char, int> > dfa;
    unordered_map<int, string> finalStates;
    vector<string> tokens;
    int q0;
    string input;
};

#endif 

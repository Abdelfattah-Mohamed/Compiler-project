#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include<bits/stdc++.h>

using namespace std;

class LexicalAnalyer {
public:
    LexicalAnalyer(vector<unordered_map<char, int> > _dfa, int _q0, unordered_map<int, string>, string _input);

    string tokenize(string ip);

    virtual ~LexicalAnalyer();

    void tock_all(string input);

protected:

private:
    vector<unordered_map<char, int> > dfa;
    unordered_map<int, string> finalStates;
    int q0;
    string input;
};

#endif 

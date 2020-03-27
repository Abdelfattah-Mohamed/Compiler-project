#ifndef LEXICALGENERATORBUILDER_H
#define LEXICALGENERATORBUILDER_H
#include <bits/stdc++.h>
#include "Dfa.cpp"
#include "lexicalAnalyzer.h"
#include "Regex_to_nfa.cpp"
using namespace std;

class LexicalGeneratorBuilder
{
public:
    LexicalGeneratorBuilder(string _inputPath, string _rulesPath);
    virtual ~LexicalGeneratorBuilder();
    void buildGenerator();
    string readInput();
private:
    string inputPath;
    string rulesPath;
};
#endif
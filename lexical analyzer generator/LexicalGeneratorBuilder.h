#ifndef LEXICALGENERATORBUILDER_H
#define LEXICALGENERATORBUILDER_H
#include <bits/stdc++.h>
#include "dfa.cpp"
#include "lexicalAnalyzer.h"
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
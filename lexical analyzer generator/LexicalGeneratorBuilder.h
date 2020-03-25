#ifndef LEXICALGENERATORBUILDER_H
#define LEXICALGENERATORBUILDER_H
#include<bits/stdc++.h>
using namespace std;

class LexicalGeneratorBuilder{
    public:
        LexicalGeneratorBuilder(string _inputPath,string _rulesPath);
        virtual ~LexicalGeneratorBuilder();
        void     LexicalGeneratorBuilder::buildGenerator();
    private:
    string inputPath;
    string rulesPath;
};
#endif
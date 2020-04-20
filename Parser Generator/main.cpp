#include <bits/stdc++.h>
#include "cfg.cpp"
using namespace std;

int main()
{

     lex = new LexicalGeneratorBuilder("input.txt", "lex_rules_ip.txt");
     lex->buildGenerator();
    CFG *cfg = new CFG(lex);
    cfg->computeFirstSets();    
    cfg->computeFollowSets();
    cfg->parseGrammerFile("inputt.txt");

    return 0;
}

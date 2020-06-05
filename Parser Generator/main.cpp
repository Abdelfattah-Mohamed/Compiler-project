#include <bits/stdc++.h>
#include "cfg.cpp"
using namespace std;

int main()
{

    LexicalGeneratorBuilder *lex = new LexicalGeneratorBuilder("test1.txt", "regularExpressions.txt");
    lex->buildGenerator();
    CFG *cfg = new CFG(lex, "grammar.txt");
    cfg->BuildParser();
    return 0;
}

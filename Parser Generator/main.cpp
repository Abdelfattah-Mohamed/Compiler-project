#include <bits/stdc++.h>
#include "cfg.cpp"
using namespace std;

int main()
{
    LexicalGeneratorBuilder *lex = new LexicalGeneratorBuilder("input.txt", "lex_rules_ip.txt");
    lex->buildGenerator();
    CFG *cfg = new CFG(lex);
    return 0;
}
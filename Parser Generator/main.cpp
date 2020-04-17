#include <bits/stdc++.h>
#include "cfg.cpp"
using namespace std;

int main()
{
    LexicalGeneratorBuilder *lex;
    // lex = new LexicalGeneratorBuilder("input.txt", "lex_rules_ip.txt");
    // lex->buildGenerator();
    CFG *cfg = new CFG(lex);
    cfg->computeFirstSets();
    cout << endl;
    cfg->computeFollowSets();
    return 0;
}

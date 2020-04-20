#include <bits/stdc++.h>
#include "cfg.cpp"
using namespace std;

int main()
{

    LexicalGeneratorBuilder *lex = new LexicalGeneratorBuilder("input.txt", "lex_rules_ip.txt");
    
    // vector<string> tokens = {"(", "id", "+", "(", "*", "id", ")"};
    // vector<string> tokens = {"int" ,"*" , "int" ,"$"};
    // vector<string> tokens = {"*", "+", "id", ")", "+", "(", "id" , "*"};
    lex->setTokens_dev(tokens);
    CFG *cfg = new CFG(lex, "grammer.txt");
    cfg->BuildParser();


   


return 0;
}

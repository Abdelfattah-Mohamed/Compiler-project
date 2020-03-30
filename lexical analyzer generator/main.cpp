#include <bits/stdc++.h>
#include "LexicalGeneratorBuilder.cpp"

using namespace std;


int main(){
    LexicalGeneratorBuilder *lex = new LexicalGeneratorBuilder("input.txt","lex_rules_ip.txt");
    lex->buildGenerator();
    return 0;
}   
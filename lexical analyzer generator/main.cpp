#include <bits/stdc++.h>
#include "LexicalGeneratorBuilder.cpp"

using namespace std;


int main(){
    LexicalGeneratorBuilder *lex = new LexicalGeneratorBuilder("D:\\University\\2nd year\\2nd Semester\\test\\input.txt","D:\\University\\2nd year\\2nd Semester\\test\\lex_rules_ip.txt");
    lex->buildGenerator();
    return 0;
}   
#include <bits/stdc++.h>
#include "lexicalAnalyzer.h"
#include "Dfa.cpp"
using namespace std;

void unitTest1(){
    vector<unordered_map<char, string>> nfa;
    unordered_map<char, string> mp;
    mp[' '] = "";
    mp['a'] = "1,";
    mp['b'] = "1,";
    mp['0'] = "";
    mp['1'] = "";
    mp['2'] = "";
    nfa.push_back(mp);
    mp.clear();

    mp[' '] = "0,3,";
    mp['a'] = "";
    mp['b'] = "";
    mp['0'] = "";
    mp['1'] = "";
    mp['2'] = "";
    nfa.push_back(mp);
    mp.clear();

    mp[' '] = "0,3,";
    mp['a'] = "";
    mp['b'] = "";
    mp['0'] = "";
    mp['1'] = "";
    mp['2'] = "";
    nfa.push_back(mp);
    mp.clear();

    mp[' '] = "";
    mp['a'] = "";
    mp['b'] = "";
    mp['0'] = "";
    mp['1'] = "";
    mp['2'] = "";
    nfa.push_back(mp);
    mp.clear();

    mp[' '] = "2,8,";
    mp['a'] = "";
    mp['b'] = "";
    mp['0'] = "";
    mp['1'] = "";
    mp['2'] = "";
    nfa.push_back(mp);
    mp.clear();

    mp[' '] = "";
    mp['a'] = "";
    mp['b'] = "";
    mp['0'] = "6,";
    mp['1'] = "6,";
    mp['2'] = "6,";
    nfa.push_back(mp);
    mp.clear();

    mp[' '] = "5,7,";
    mp['a'] = "";
    mp['b'] = "";
    mp['0'] = "";
    mp['1'] = "";
    mp['2'] = "";
    nfa.push_back(mp);
    mp.clear();

    mp[' '] = "";
    mp['a'] = "";
    mp['b'] = "";
    mp['0'] = "";
    mp['1'] = "";
    mp['2'] = "";
    nfa.push_back(mp);
    mp.clear();

    mp[' '] = "5,7,";
    mp['a'] = "";
    mp['b'] = "";
    mp['0'] = "";
    mp['1'] = "";
    mp['2'] = "";
    nfa.push_back(mp);
    mp.clear();

    unordered_map<int, string> accepted;
    accepted[3] = "id";
    accepted[7] = "num";
    // accepted[4] = "s";

    unordered_map<int, int> priority;
    priority[3] = 1;
    priority[7] = 2;
    // priority[4] = 3;
    DFA *dfa = new DFA(nfa, 4, accepted, priority);
    unordered_map<int,string> acc = dfa->get_accept_states();
    vector<unordered_map<char, int>> dfa_vec =dfa->get_dfa();
    string input = "c12";
    LexicalAnalyer *lex = new LexicalAnalyer(dfa_vec,0,acc,input);
    lex->tokenize();
    
}
int main(){
    unitTest1();
    // vector<unordered_map <char,int> > dfa(8);
    //     dfa = {
    //     {{'a',1},{'d',7}},
    //     {{'b',2}},
    //     {{'c',3}},
    //     {{'a',4},{'d',7}},
    //     {{'b',5}},
    //     {{'c',6}},
    //     {{'d',7},{'a',4}},   
    //     {}
    // }; 
    // string s = "abcabcabcabc";
    // int q0 = 0;
    // unordered_map<int,string>  finalStates ={{3,"abc"},{7,"(abc)*d"}};
    // LexicalAnalyer *lex = new LexicalAnalyer(dfa,q0,finalStates,s);
    // lex->tokenize();
    return 0;
}   
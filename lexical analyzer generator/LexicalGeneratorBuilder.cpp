#include "LexicalGeneratorBuilder.h"

LexicalGeneratorBuilder::LexicalGeneratorBuilder(string _inputPath, string _rulesPath)
{
    inputPath = _inputPath;
    rulesPath = _rulesPath;
}
string LexicalGeneratorBuilder::readInput(){
    string line;
    string input  = "";
    ifstream myfile(inputPath);
    if (myfile)
    {
        while (getline(myfile, line))
        {
            input += line;   
        }
        myfile.close();
    }
    return input;
}
void LexicalGeneratorBuilder::buildGenerator()
{
    regex_to_nfa *regToNfa = new regex_to_nfa(rulesPath);
    DFA *dfa =   new DFA(regToNfa->get_nfa(), 0, regToNfa->get_priority_map());
    unordered_map<int, string> acc = dfa->get_accept_states();
    vector<unordered_map<char, int>> dfa_vec = dfa->get_dfa();
    string input = readInput();
    LexicalAnalyer *lex = new LexicalAnalyer(dfa_vec, 0, acc, input);
}
#include <bits/stdc++.h>
#include "Regex_to_nfa.cpp"
#include "Dfa.cpp"
#include "lexicalAnalyzer.cpp"

using namespace std;

class LexicalGeneratorBuilder
{
public:
    LexicalGeneratorBuilder(string _inputPath, string _rulesPath)
    {
        inputPath = _inputPath;
        rulesPath = _rulesPath;
    }

    string readInput()
    {
        string line;
        string input = "";
        ifstream myfile(inputPath);
        if (myfile)
        {
            while (getline(myfile, line))
            {
                input += (line + " ");
            }
            myfile.close();
        }
        // cout << endl << input << endl;
        return input;
    }

    void buildGenerator()
    {
        regex_to_nfa *regToNfa = new regex_to_nfa(rulesPath);
        // cout << endl << regToNfa->get_priority_map().size() << endl;
        DFA *dfa = new DFA(regToNfa->get_nfa(), 0, regToNfa->get_priority_map());

        unordered_map<int, string> acc = dfa->get_accept_states();

        // cout << endl << dfa->get_accept_states().size() << " " << dfa->get_dfa().size() << endl;
        vector<unordered_map<char, int>> dfa_vec = dfa->get_dfa();
        string input = readInput();
        LexicalAnalyzer *lex = new LexicalAnalyzer(dfa_vec, 0, acc, input);
        lex->tock_all(input);
        tokens = lex->getTokens();
    }
    string nextToken()
    {
        if (token_ptr < tokens.size())
        {
            string str = tokens[token_ptr];
            token_ptr++;
            return str;
        }
        return "";
    }

private:
    string inputPath;
    string rulesPath;
    vector<string> tokens;
    int token_ptr = 0;
};

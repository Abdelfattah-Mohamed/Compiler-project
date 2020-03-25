#include "lexicalAnalyzer.h"

LexicalAnalyer::LexicalAnalyer(vector<unordered_map<char, int>> _dfa, int _q0, unordered_map<int,string> _finalStates, string _input)
{
    dfa = _dfa;
    input = _input;
    finalStates = _finalStates;
    q0 = _q0;
}
LexicalAnalyer::~LexicalAnalyer()
{
}
string LexicalAnalyer::tokenize()
{
    int i = 0;
    vector<vector<bool>> prevFailed(dfa.size(), vector<bool>(input.size(), false));
   
    int bottom = -1;
    while (true)
    {
        int q = q0;
        stack<pair<int, int>> st;
        st.push({bottom, i});
        while (i < input.size() && dfa[q].count(input[i]))
        {
            if (prevFailed[q][i])
                break;
            if(finalStates.count(q)){
                stack<pair<int,int>> emptySt;
                st = emptySt;
            }
            st.push({q,i});
            q = dfa[q][input[i]];
            i++;
        }
        while(!finalStates.count(q)){
            prevFailed[q][i] = true;
            q = st.top().first;
            i = st.top().second;
            st.pop();
            if(q == bottom)
                return "failure";
        }
        cout<<i-1<<" "<<q<<endl;
        if(i >= input.size()){
            return "success";
        }
    }
}

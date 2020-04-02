#include "lexicalAnalyzer.h"


string LexicalAnalyzer::tokenize(string ip) {
    int i = 0;
    vector<vector<bool>> prevFailed(dfa.size(), vector<bool>(ip.size(), false));
    finalStates[0] = "error";
    int bottom = -1;
    while (true) {
        int q = q0;
        stack<pair<int, int>> st;
        st.push({bottom, i});
        while (i < ip.size() && dfa[q].count(ip[i])) {
            if (prevFailed[q][i])
                break;
            if (finalStates.count(q)) {
                stack<pair<int, int>> emptySt;
                st = emptySt;
            }
            st.push({q, i});
            q = dfa[q][ip[i]];
            i++;
        }
        int dead_index = -2;
        if (q == 1) {//dead state
            dead_index = i;
            q = st.top().first;
            i = st.top().second;
            st.pop();
        }
        while (!finalStates.count(q)) {
            prevFailed[q][i] = true;
            q = st.top().first;
            i = st.top().second;
            st.pop();
            if (q == bottom)
                return "failure";
        }
        if (q == q0 && dead_index != -2) {
            i = dead_index;
            q = 1;
        }
        cout<< finalStates[q] << endl;
        if (i >= ip.size()) {
            return "success";
        }
    }
}

LexicalAnalyzer::LexicalAnalyzer(vector<unordered_map<char, int>> _dfa, int _q0, unordered_map<int, string> _finalStates,
                               string _input) {
    dfa = _dfa;
    input = _input;
    finalStates = _finalStates;
    q0 = _q0;
}

void LexicalAnalyzer::tock_all(string input) {
    freopen("output.txt","w",stdout);
    string ret = "";
    for (char c : input) {
        if (c != ' ') ret += c;
        else {
            if(!ret.empty())
                tokenize(ret);
            ret = "";
        }
    }
    if(!ret.empty()) tokenize(ret);

}

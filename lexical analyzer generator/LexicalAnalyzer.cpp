#include <bits/stdc++.h>
using namespace std;
class LexicalAnalyzer
{

private:
    vector<unordered_map<char, int>> dfa;
    unordered_map<int, string> finalStates;
    vector<string> tokens;
    int q0;
    string input;

public:
    LexicalAnalyzer(vector<unordered_map<char, int>> _dfa, int _q0, unordered_map<int, string> _finalStates,
                    string _input)
    {
        dfa = _dfa;
        input = _input;
        finalStates = _finalStates;
        q0 = _q0;
    }

    string tokenize(string ip)
    {
        int i = 0;
        vector<vector<bool>> prevFailed(dfa.size(), vector<bool>(ip.size(), false));
        finalStates[0] = "error";
        int bottom = -1;
        while (true)
        {
            int q = q0;
            stack<pair<int, int>> st;
            st.push({bottom, i});
            while (i < ip.size() && dfa[q].count(ip[i]))
            {
                if (prevFailed[q][i])
                    break;
                if (finalStates.count(q))
                {
                    stack<pair<int, int>> emptySt;
                    st = emptySt;
                }
                st.push({q, i});
                q = dfa[q][ip[i]];
                i++;
            }
            int dead_index = -2;
            if (q == 1)
            { //dead state
                dead_index = i;
                q = st.top().first;
                i = st.top().second;
                st.pop();
            }
            while (!finalStates.count(q))
            {
                prevFailed[q][i] = true;
                q = st.top().first;
                i = st.top().second;
                st.pop();
                if (q == bottom)
                    return "failure";
            }
            if (q == q0 && dead_index != -2)
            {
                i = dead_index;
                q = 1;
            }
            tokens.emplace_back(finalStates[q]);
            cout << finalStates[q] << endl;
            if (i >= ip.size())
            {
                return "success";
            }
        }
    }
    vector<string> getTokens()
    {
        return tokens;
    }

    void tock_all(string input)
    {
        fstream file;
        file.open("output.txt", ios::out);
        streambuf *stream_buffer_cout = cout.rdbuf();
        streambuf *stream_buffer_cin = cin.rdbuf();
        streambuf *stream_buffer_file = file.rdbuf();
        cout.rdbuf(stream_buffer_file);
        string ret = "";
        for (char c : input)
        {
            if (c != ' ')
                ret += c;
            else
            {
                if (!ret.empty())
                    tokenize(ret);
                ret = "";
            }
        }
        if (!ret.empty())
            tokenize(ret);
        cout.rdbuf(stream_buffer_cout);
        file.close();
    }
};
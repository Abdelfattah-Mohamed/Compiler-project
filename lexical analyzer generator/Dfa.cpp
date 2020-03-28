#include <bits/stdc++.h>
using namespace std;
class DFA
{
private:
    // nfa
    vector<vector<vector<int>>>
        nfa;
    int nfa_start_state;
    unordered_map<int, string> accept_state_nfa;
    unordered_map<int, int> accept_priority;
    unordered_map<char, int> input_col;

    // dfa
    vector<vector<int>> dfa;
    vector<int> dfa_start_state;
    unordered_map<int, string> accept_state_dfa;
    unordered_map<int, int> accept_priority_dfa;

    // dfa mini
    vector<vector<int>> dfa_mini;
    unordered_map<int, string> accept_state_dfa_mini;
    unordered_map<int, int> accept_priority_dfa_mini;

    vector<unordered_map<char, int>> final_dfa;

    // private usage
    unordered_map<string, int> mp;

    vector<vector<vector<int>>> convert_nfa(vector<unordered_map<char, string>> &temp_nfa)
    {
        int n = temp_nfa.size();
        vector<vector<vector<int>>> temp(n, vector<vector<int>>(130));
        for (int i = 0; i < n; i++)
        {
            for (auto y : temp_nfa[i])
            {
                if (y.first != ' ')
                    temp[i][(int)y.first] = conv_string_to_vector(y.second);
                else
                    temp[i][0] = conv_string_to_vector(y.second);
            }
        }
        return temp;
    }

    vector<int> conv_string_to_vector(string s)
    {
        vector<string> result;
        string temp = "";
        for (char c : s)
        {
            if (c == ',' && !temp.empty())
                result.push_back(temp), temp = "";
            else
                temp += c;
        }
        if (!temp.empty()) result.push_back(temp);
        vector<int> ret;
        for (string x : result)
            ret.push_back(stoi(x));
        return ret;
    }

    /**
     * description: getting vector of starting state for dfa (set of state that's can reach by eps).
     * @return vector<int> starting state.
     */
    vector<int> get_starting_state()
    {
        vector<int> temp;
        temp.push_back(this->nfa_start_state);
        return get_epsClosure(temp);
    }

    /**
     * Description: get eps Closure of current state (vector of nfa states thats is new dfa state.)
     * @param state
     * @return vector<int> eps
     */
    vector<int> get_epsClosure(vector<int> &state)
    {
        int n = nfa.size();
        vector<bool> visited(n, false);
        vector<int> eps;
        queue<int> que;
        for (int x : state)
        {
            eps.push_back(x);
            visited[x] = true;
            que.push(x);
        }
        while (!que.empty())
        {
            int curr = que.front();
            que.pop();
            // assumption : eps trans. at col. 0;
            vector<int> temp = nfa[curr][0];
            for (int x : temp)
            {
                if (!visited[x])
                {
                    visited[x] = true;
                    eps.push_back(x);
                    que.push(x);
                }
            }
        }
        sort(eps.begin(), eps.end());
        for(int x : eps) {
            if(x == 56 || x == 14) {
                cout << -1;
            }
        }
        return eps;
    }

    /**
     * fill dfa matrix for transitions.
     * @param start
     */
    void build_DFA(vector<int> &start)
    {
        int curr_state = 0;
        string state = conv_vec_to_str(start);
        mp[state] = curr_state;
        curr_state++;
        queue<vector<int>> que;
        que.push(start);
        int row = 0;
        while (!que.empty())
        {
            vector<int> curr = que.front();
            add_if_accept(curr, row);
            que.pop();
            vector<int> dfa_row;
            dfa_row.push_back(-1);
            for (int i = 1; i < nfa[0].size(); i++)
            {
                vector<int> first = get_all_to(curr, i);
                vector<int> second = get_epsClosure(first);
                sort(second.begin(), second.end());
                state = conv_vec_to_str(second);
                if (mp.count(state))
                    dfa_row.push_back(mp[state]);
                else
                {
                    dfa_row.push_back(curr_state);
                    mp[state] = curr_state;
                    curr_state++;
                    que.push(second);
                }
            }
            if (accept_state_dfa.count(row))
            {
                accept_priority_dfa[row] = get_max_priority(curr);
            }
            dfa.push_back(dfa_row);
            row++;
        }
    }

    /**
     * Description: convert vector of states to string separated by #.
     * @param vec
     * @return string ret
     */
    string conv_vec_to_str(vector<int> &vec)
    {
        string ret = "#";
        for (int x : vec)
            ret += (to_string(x) + "#");
        return ret;
    }

    /**
     * Description: get all target states from source with col. transition.
     * @param vec
     * @param col
     * @return vector ret
     */
    vector<int> get_all_to(vector<int> &vec, int col)
    {
        unordered_set<int> st;
        for (int x : vec)
        {
            for (int y : nfa[x][col])
            {
                st.emplace(y);
            }
        }
        return vector<int>(st.begin(), st.end());
    }

    /**
     * Description: add current state to accept_state_dfa if it acceptance state.
     * @param vec
     * @param curr
     */
    void add_if_accept(vector<int> &vec, int curr)
    {
        int state = -1, priority = INT_MAX;
        for (int x : vec)
        {
            if (accept_state_nfa.count(x))
            {
                if (accept_priority[x] < priority && accept_priority[x] != -1)
                    state = x, priority = accept_priority[x];
            }
        }
        if (state != -1)
            accept_state_dfa[curr] = accept_state_nfa[state];
    }

    int get_max_priority(vector<int> &vec)
    {
        int ret = INT_MAX;
        for (int x : vec)
        {
            if (this->accept_priority.count(x))
                if(this->accept_priority[x] != -1) ret = min(ret, this->accept_priority[x]);
        }
        return ret;
    }

    /**
     * Description: minimize dfa to dfa_mini.
     */
    void minimization()
    {
        int n = this->dfa.size();
        vector<vector<bool>> memo = set_init(n);
        bool flag = false;
        while (!flag)
        {
            flag = true;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < i; j++)
                {
                    if (!memo[i][j])
                    {
                        if (!test(i, j, memo))
                        {
                            memo[i][j] = true;
                            flag = false;
                        }
                    }
                }
            }
        }
        unordered_map<int, int> old_new;
        unordered_map<int, vector<int>> new_old;
        int current = 0;
        old_new[0] = current;
        new_old[current].push_back(0);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (!memo[i][j])
                {
                    old_new[i] = old_new[j];
                    new_old[old_new[j]].push_back(i);
                    break;
                }
            }
            if (!old_new.count(i))
            {
                current++;
                old_new[i] = current;
                new_old[current].push_back(i);
            }
        }
        for (int i = 0; i <= current; i++)
        {
            vector<int> temp;
            int old = new_old[i][0];
            int n = dfa[old].size();
            temp.push_back(-1);
            for (int j = 1; j < n; j++)
            {
                temp.push_back(old_new[dfa[old][j]]);
            }
            dfa_mini.push_back(temp);
            if (accept_state_dfa.count(old))
            {
                accept_state_dfa_mini[i] = accept_state_dfa[old];
                accept_priority_dfa_mini[i] = get_max_priority_dfa(new_old[i]);
            }
        }
    }

    /**
     * Description: initialization of Myhill Nerode matrix.
     * @param n
     * @return Myhill Nerode matrix.
     */
    vector<vector<bool>> set_init(int n)
    {
        // not equivalent => true, equivalent => false.
        vector<vector<bool>> ret(n, vector<bool>(n, false));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                ret[i][j] = test_final_not_final(i, j);
            }
        }

        return ret;
    }

    /**
     * Description: test two state are final or not-final.
     * @param x
     * @param y
     * @return bool
     */
    bool test_final_not_final(int x, int y)
    {
        if (!accept_state_dfa.count(x) && !accept_state_dfa.count(y))
            return false;
        else if (accept_state_dfa.count(x) && accept_state_dfa.count(y))
        {
            return !(accept_state_dfa[x] == accept_state_dfa[y]);
        }
        else
            return true;
    }

    /**
     * Description: test equevilant state from previous state of Myhill Nerode matrix.
     * @param x
     * @param y
     * @param memo
     * @return bool
     */
    bool test(int x, int y, vector<vector<bool>> &memo)
    {
        int n = this->dfa[x].size();
        for (int i = 1; i < n; i++)
        {
            int xx = this->dfa[x][i];
            int yy = this->dfa[y][i];
            if (memo[max(xx, yy)][min(xx, yy)])
                return false;
        }
        return true;
    }

    int get_max_priority_dfa(vector<int> &vec)
    {
        int ret = INT_MAX;
        for (int x : vec)
        {
            if (this->accept_priority_dfa.count(x))
                if(this->accept_priority_dfa[x] != -1) ret = min(ret, this->accept_priority_dfa[x]);
        }
        return ret;
    }

    vector<unordered_map<char, int>> convert_dfa()
    {
        int n = dfa_mini.size();
        vector<unordered_map<char, int>>
            ret(n);
        for (int i = 0; i < n; i++)
        {
            if (i == 1)
                continue;
            unordered_map<char, int> mp;
            for (int j = 1; j < 128; j++)
            {
                mp[(char)j] = dfa_mini[i][j];
            }
            ret[i] = mp;
        }
        return ret;
    }
    unordered_map<int, string> conv_acc_pri_to_acc(unordered_map<string, pair<int, int>> par)
    {
        unordered_map<int, string> ret;
        for (auto x : par)
            ret[x.second.second] = x.first;
        return ret;
    }

    unordered_map<int, int> conv_acc_pri_to_pri(unordered_map<string, pair<int, int>> par)
    {
        unordered_map<int, int> ret;
        for (auto x : par)
            ret[x.second.second] = x.second.first;
        return ret;
    }

public:
    /**
     * DFA constructor.
     * @param nfa
     * @param start_state
     */
    DFA(vector<unordered_map<char, string>> nfa, int start_state, unordered_map<string, pair<int, int>> acc_pri)
    {
        this->nfa = convert_nfa(nfa);
        this->nfa_start_state = start_state;
        this->accept_state_nfa = conv_acc_pri_to_acc(acc_pri);
        this->accept_priority = conv_acc_pri_to_pri(acc_pri);
        this->dfa_start_state = get_starting_state();

        build_DFA(this->dfa_start_state);

        minimization();

        this->final_dfa = convert_dfa();
        this->accept_state_dfa_mini[1] = "(Error)";
    }

    vector<unordered_map<char, int>> get_dfa() { return this->final_dfa; }
    unordered_map<int, string> get_accept_states() { return accept_state_dfa_mini; }
};
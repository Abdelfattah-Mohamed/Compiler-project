#include <bits/stdc++.h>
#include <map>
#include <utility>
#include <string.h>
#include <vector>

using namespace std;
class Nfa
{
private:
 vector<unordered_map<char, string>> &all_states ;
public:
    Nfa(vector<unordered_map<char, string>> &vec) :all_states(vec)
    {
    }
//2 Nfas are ored (|)
std::pair<int, int> reg_nfa_op1(pair<int, int> nfa1, pair<int, int> nfa2)
{

    int size1 = all_states.size();

    unordered_map<char, string> temp;
    string s = to_string(nfa1.first) + "," + to_string(nfa2.first);
    temp.insert(pair<char, string>(' ', s));
    all_states.push_back(temp);
    temp.clear();
    unordered_map<char, string> &state1 = all_states[nfa1.second];
    unordered_map<char, string> &state2 = all_states[nfa2.second];

    if (state1.count(' ') > 0)
    {
        string s1 = state1[' '] + "," + to_string(all_states.size());
        state1[' ']= s1;
    }
    else
    {
        state1.insert(pair<char, string>(' ', to_string(all_states.size())));
    }
    if (state2.count(' ') > 0)
    {
        string s2 = state2[' '] + "," + to_string(all_states.size());
        state2[' ']= s2;
    }
    else
    {
        state2.insert(pair<char, string>(' ', to_string(all_states.size())));
    }
    unordered_map<char, string> Accept_s;
    all_states.push_back(Accept_s);
    return std::make_pair(size1, all_states.size() - 1);
}

std::pair<int, int> reg_nfa_op2(pair<int, int> nfa1, pair<int, int> nfa2)
{

    int size1 = all_states.size();

    unordered_map<char, string> temp;
    temp.insert(pair<char, string>(' ', to_string(nfa1.first)));
    all_states.push_back(temp);
    temp.clear();
    unordered_map<char, string> &state1 = all_states[nfa1.second];
    if (state1.count(' ') > 0)
    {
        string s1 = state1[' '] + "," + to_string(nfa2.first);
        state1[' '] =s1;
    }
    else
    {
        state1.insert(pair<char, string>(' ', to_string(nfa2.first)));
    }
    unordered_map<char, string> &state2 = all_states[nfa2.second];
    if (state2.count(' ') > 0)
    {
        string s2 = state2[' '] + "," + to_string(all_states.size());
        state2[' ']= s2;
    }
    else
    {
        state2.insert(pair<char, string>(' ', to_string(all_states.size())));
    }

    unordered_map<char, string> Accept_s;
    all_states.push_back(Accept_s);

    return std::make_pair(size1, all_states.size() - 1);
}

std::pair<int, int> reg_nfa_op3(pair<int, int> nfa1)
{

    int size1 = all_states.size();

    unordered_map<char, string> temp;
    string s1 = to_string(nfa1.first) + "," + to_string(all_states.size() + 1);
    temp.insert(pair<char, string>(' ', s1));
    all_states.push_back(temp);
    unordered_map<char, string> &state1 = all_states[nfa1.second];

    if (state1.count(' ') > 0)
    {
        string s2 = state1[' '] + "," + to_string(all_states.size()) + "," + to_string(nfa1.first);
        state1[' ']= s2;
    }
    else
    {
        string s2 = to_string(all_states.size()) + "," + to_string(nfa1.first);
        state1.insert(pair<char, string>(' ', s2));
    }

    unordered_map<char, string> Accept_s;
    all_states.push_back(Accept_s);

    return std::make_pair(size1, all_states.size() - 1);
}

std::pair<int, int> reg_nfa_op4(pair<int, int> nfa1)
{

    int size1 = all_states.size();

    unordered_map<char, string> temp;
    temp.insert(pair<char, string>(' ', to_string(nfa1.first)));
    all_states.push_back(temp);
    unordered_map<char, string> &state1 = all_states[nfa1.second];

    if (state1.count(' ') > 0)
    {
        string s = state1[' '] + "," + to_string(all_states.size()) + "," + to_string(nfa1.first);
        state1[' ']= s;
    }
    else
    {
        string s = to_string(all_states.size()) + "," + to_string(nfa1.first);
        state1.insert(pair<char, string>(' ', s));
    }

    unordered_map<char, string> Accept_s;
    all_states.push_back(Accept_s);

    return std::make_pair(size1, all_states.size() - 1);
}

std::pair<int, int> reg_nfa_op5(char range1, char range2)
{

    int size1 = all_states.size();

    unordered_map<char, string> temp;

    int r = (int(range2) - int(range1));

    for (int i = 0; i <= r ; i++)
    {

        temp.insert(pair<char, string>(range1, to_string(size1 + 1)));
        range1 += 1;
    }
    all_states.push_back(temp);
    unordered_map<char, string> Accept_s;
    all_states.push_back(Accept_s);

    return std::make_pair(size1, all_states.size() - 1);
}
};
/*
int main()
{

    unordered_map<char, string> temp;
    temp.insert(pair<char, string>('a', "1"));
    all_states.push_back(temp);
    all_states.push_back(unordered_map<char, string>());
    temp.clear();
    temp.insert(pair<char, string>('b', "3"));
    all_states.push_back(temp);
    all_states.push_back(unordered_map<char, string>());

    pair<int, int> t1(0, 1);
    pair<int, int> t2(2, 3);

    pair<int, int> t3 = reg_nfa_op5('0','3');

    cout << all_states[0][' '] << " " << all_states[0]['0'] << " " << all_states[0]['1'] << " " <<all_states[0]['2'] << " " << all_states[0]['3'] << endl;
    cout << t3.first << t3.second << endl;

    return 0;
}
*/

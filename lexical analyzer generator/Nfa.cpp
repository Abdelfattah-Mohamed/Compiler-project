#include <bits/stdc++.h>
#include <map>
#include <utility>
#include <string.h>
#include <vector>
using namespace std;

int main()
{

    map<char, string> state;
    vector<map<char, string>> dfaa;

    /*dfaa.insert(std::pair<string, string>("sss", "Jon"));

    for (map<string, string>::iterator iter = dfaa.begin(); iter != dfaa.end(); ++iter)
    { q
        cout << (*iter).first << ": " << (*iter).second << endl;
    }*/
    char a = 'a';
    a += 1;
    cout << a;

    return 0;
}

std::pair<int, int> reg_nfa_op1(string str, vector<map<char, string>> nfa1, vector<map<char, string>> nfa2)
{
    vector<map<char, string>> nfaa;
    map<char, string> temp;
    temp.insert(pair<char, string>(' ', "13"));
    nfaa.push_back(temp);
    temp.clear();
    temp.insert(pair<char, string>('a', "2"));
    nfaa.push_back(temp);
    temp.clear();
    temp.insert(pair<char, string>(' ', "5"));
    nfaa.push_back(temp);
    temp.clear();
    temp.insert(pair<char, string>('b', "4"));
    nfaa.push_back(temp);
    temp.clear();
    temp.insert(pair<char, string>(' ', "5"));
    nfaa.push_back(temp);
    temp.clear();
    nfaa.push_back(temp);

    return std::make_pair(0, nfaa.size());
}

std::pair<int, int> reg_nfa_op2(string str, vector<map<char, string>> nfa1, vector<map<char, string>> nfa2)
{
    vector<map<char, string>> nfaa1;
    map<char, string> temp1;
    temp1.insert(pair<char, string>('a', "1"));
    nfaa1.push_back(temp1);
    temp1.clear();
    temp1.insert(pair<char, string>('b', "2"));
    nfaa1.push_back(temp1);
    temp1.clear();
    nfaa1.push_back(temp1);

    return std::make_pair(0, nfaa1.size());
}

std::pair<int, int> reg_nfa_op3(string str, vector<map<char, string>> nfa1, vector<map<char, string>> nfa2)
{
    vector<map<char, string>> nfaa2;
    map<char, string> temp2;
    temp2.insert(pair<char, string>(' ', "13"));
    nfaa2.push_back(temp2);
    temp2.clear();
    temp2.insert(pair<char, string>('a', "2"));
    nfaa2.push_back(temp2);
    temp2.clear();
    temp2.insert(pair<char, string>(' ', "31"));
    nfaa2.push_back(temp2);
    temp2.clear();
    nfaa2.push_back(temp2);

    return std::make_pair(0, nfaa2.size());
}

std::pair<int, int> reg_nfa_op4(string str, vector<map<char, string>> nfa1, vector<map<char, string>> nfa2)
{
    vector<map<char, string>> nfaa3;
    map<char, string> temp3;
    temp3.insert(pair<char, string>(' ', "1"));
    nfaa3.push_back(temp3);
    temp3.clear();
    temp3.insert(pair<char, string>('a', "2"));
    nfaa3.push_back(temp3);
    temp3.clear();
    temp3.insert(pair<char, string>(' ', "31"));
    nfaa3.push_back(temp3);
    temp3.clear();
    nfaa3.push_back(temp3);

    return std::make_pair(0, nfaa3.size());
}

std::pair<int, int> reg_nfa_op5(string str, vector<map<char, string>> nfa1, vector<map<char, string>> nfa2)
{
    char range1 = '0';
    char range2 = '9';
    vector<map<char, string>> nfaa4;
    map<char, string> temp4;
    for (int i = 0; i < int(range2) - int(range1); i++)
    {

        temp4.insert(pair<char, string>(range1, to_string(i + 1)));
        nfaa4.push_back(temp4);
        temp4.clear();
        range1 += 1;
    }

    return std::make_pair(0, nfaa4.size());
}

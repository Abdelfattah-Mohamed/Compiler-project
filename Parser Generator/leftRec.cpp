#include <bits/stdc++.h>
#include "ProductionRule.cpp"

using namespace std;

class leftRec
{

private:
    unordered_map<string, vector<ProductionRule *>> nonTerminals;
    vector<ProductionRule *> productionRules;
    unordered_map<string, int> nonTermSorted;
    unordered_map<int, string> SortednonTerm;

    unordered_map<string, vector<vector<string>>> productions;

    vector<string> convSRTtoVEC(string s)
    {
        vector<string> ret;
        string temp = "";
        for (char c : s)
        {
            if (c == ' ')
                ret.push_back(temp), temp = "";
            else
                temp += c;
        }
        if (!temp.empty())
            ret.push_back(temp);
        return ret;
    }

    void sortnonTerminal()
    {
        int x = 1;
        for (auto f : productionRules)
        {
            string temp = f->getLhs();
            if (!nonTermSorted.count(temp))
                nonTermSorted[temp] = x, SortednonTerm[x] = temp, x++;
            productions[temp].push_back(f->getRhs());
        }
    }

    void elimination()
    {
        sortnonTerminal();
        int n = productions.size();
        for (int i = 1; i <= n; i++)
        {
            vector<vector<string>> temp = productions[SortednonTerm[i]];
            for (int j = 1; j < i; j++)
            {
                for (int k = 0; k < temp.size(); k++)
                {
                    if (nonTermSorted[temp[k][0]] == j)
                    {
                        vector<string> f = temp[k];
                        vector<vector<string>> ff = productions[SortednonTerm[j]];
                        for (int p = 0; p < ff.size(); p++)
                        {
                            for (int q = 1; q < f.size(); q++)
                            {
                                ff[p].push_back(f[q]);
                            }
                        }
                        temp[k] = ff[0];
                        for (int p = 1; p < ff.size(); p++)
                            temp.push_back(ff[p]);
                    }
                }
            }

            for (int p = 0; p < temp.size(); p++)
            {
                vector<string> x;
                for (int q = 0; q < temp[p].size(); q++)
                {
                    if (temp[p][q] != "Epsilon")
                        x.push_back(temp[p][q]);
                }
                if (x.empty())
                    x.push_back("Epsilon");
                temp[p] = x;
            }

            productions[SortednonTerm[i]] = temp;
            string s = SortednonTerm[i];
            string newS = s;
            newS += '!';
            vector<vector<string>> right, left;
            for (int p = 0; p < temp.size(); p++)
            {
                if (temp[p][0] == s)
                    temp[p].push_back(newS), temp[p].erase(temp[p].begin()), left.push_back(temp[p]);
                else
                {
                    if (temp[p][0] == "Epsilon")
                        temp[p][0] = newS;
                    else
                        temp[p].push_back(newS);
                    right.push_back(temp[p]);
                }
            }
            if (left.empty())
                for (auto &y : right)
                    y.pop_back();
            else
                left.push_back({"Epsilon"}), productions[newS] = left;
            productions[s] = right;
        }
        convpass();
        leftFact();
        convpass();
    }

    void convpass()
    {
        nonTerminals.clear();
        productionRules.clear();
        for (auto x : productions)
        {
            for (auto y : x.second)
            {
                ProductionRule *z = new ProductionRule(x.first, y);
                productionRules.push_back(z);
                nonTerminals[x.first].push_back(z);
            }
        }
    }

    void leftFact()
    {
        vector<pair<string, vector<vector<string>>>> prods;
        for (auto x : productions)
            prods.push_back({x.first, x.second});
        productions.clear();
        int i = -1;
        while (++i < (int)prods.size())
        {
            auto pd = prods[i];
            string lhs = pd.first;
            vector<vector<string>> rhs = pd.second;
            unordered_map<string, vector<int>> mp;
            for (int j = 0; j < rhs.size(); j++)
                mp[rhs[j][0]].push_back(j);
            int f = -1;
            productions[lhs].clear();
            for (auto x : mp)
            {
                vector<int> idx = x.second;
                if (idx.size() == 1)
                {
                    productions[lhs].push_back(rhs[idx[0]]);
                }
                else
                {
                    string ll = (lhs + to_string(++f));
                    productions[lhs].push_back({x.first, ll});
                    set<vector<string>> st;
                    for (int k : idx)
                    {
                        vector<string> rf;
                        for (int q = 1; q < rhs[k].size(); q++)
                            rf.push_back(rhs[k][q]);
                        if (rf.empty())
                            rf.emplace_back("Epsilon");
                        st.emplace(rf);
                    }
                    vector<vector<string>> tr(st.begin(), st.end());
                    productions[ll] = tr;
                    prods.emplace_back(ll, tr);
                }
            }
        }
    }
    void removeDuplicates()
    {
    }

public:
    leftRec(vector<ProductionRule *> __productionRules)
    {
        this->productionRules = __productionRules;
        this->elimination();
        this->removeDuplicates();
    }

    vector<ProductionRule *> get_Rules()
    {
        return this->productionRules;
    }
    unordered_map<string, vector<ProductionRule *>> getNonTerminals()
    {
        return nonTerminals;
    }
};

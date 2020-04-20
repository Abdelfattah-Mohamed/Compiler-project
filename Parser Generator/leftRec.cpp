#include <bits/stdc++.h>
#include "ProductionRule.cpp"

using namespace std;

class leftRec {

    class leftRec {

    private:
        unordered_map<string, vector<ProductionRule *>> nonTerminals;
        vector<ProductionRule *> productionRules;
        unordered_map<string, int> nonTermSorted;
        unordered_map<int, string> SortednonTerm;

        unordered_map<string, vector<vector<string>>> productions;

        vector<string> convSRTtoVEC(string s) {
            vector<string> ret;
            string temp = "";
            for (char c : s) {
                if (c == ' ') ret.push_back(temp), temp = "";
                else temp += c;
            }
            if (!temp.empty()) ret.push_back(temp);
            return ret;
        }

        void sortnonTerminal() {
            int x = 1;
            for (auto f : productionRules) {
                string temp = f->getLhs();
                if (!nonTermSorted.count(temp)) nonTermSorted[temp] = x, SortednonTerm[x] = temp, x++;
                productions[temp].push_back(f->getRhs());
            }
        }


        void elimination() {
            sortnonTerminal();
            int n = productions.size();
            for (int i = 1; i <= n; i++) {
                vector<vector<string>> temp = productions[SortednonTerm[i]];
                for (int j = 1; j < i; j++) {
                    for (int k = 0; k < temp.size(); k++) {
                        if (nonTermSorted[temp[k][0]] == j) {
                            vector<string> f = temp[k];
                            vector<vector<string>> ff = productions[SortednonTerm[j]];
                            for (int p = 0; p < ff.size(); p++) {
                                for (int q = 1; q < f.size(); q++) {
                                    ff[p].push_back(f[q]);
                                }
                            }
                            temp[k] = ff[0];
                            for (int p = 1; p < ff.size(); p++) temp.push_back(ff[p]);
                        }
                    }
                }

                for (int p = 0; p < temp.size(); p++) {
                    vector<string> x;
                    for (int q = 0; q < temp[p].size(); q++) {
                        if (temp[p][q] != "epsilon") x.push_back(temp[p][q]);
                    }
                    if (x.empty()) x.push_back("epsilon");
                    temp[p] = x;
                }

                productions[SortednonTerm[i]] = temp;
                string s = SortednonTerm[i];
                string newS = s;
                newS += '!';
                vector<vector<string>> right, left;
                for (int p = 0; p < temp.size(); p++) {
                    if (temp[p][0] == s)
                        temp[p].push_back(newS), temp[p].erase(temp[p].begin()), left.push_back(temp[p]);
                    else {
                        if (temp[p][0] == "epsilon") temp[p][0] = newS;
                        else temp[p].push_back(newS);
                        right.push_back(temp[p]);
                    }
                }
                if (left.empty()) for (auto &y : right) y.pop_back();
                else left.push_back({"epsilon"}), productions[newS] = left;
                productions[s] = right;
            }
            convpass();
        }


        void convpass() {
            productionRules.clear();
            for (auto x : productions) {
                for (auto y : x.second) {
                    ProductionRule *z = new ProductionRule(x.first, y);
                    productionRules.push_back(z);
                    nonTerminals[x.first].push_back(z);
                }
            }
        }


    public:
        leftRec(vector<ProductionRule *> __productionRules) {
            this->productionRules = __productionRules;
            this->elimination();
        }

        vector<ProductionRule *> get_Rules() {
            return this->productionRules;
        }

    };

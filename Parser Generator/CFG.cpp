#include <bits/stdc++.h>
#include "ProductionRule.cpp"
#include "../lexical analyzer generator/LexicalGeneratorBuilder.cpp"

using namespace std;
class CFG
{
private:
    /// add helper functions
    string startSymbol;
    LexicalGeneratorBuilder *lexBuilder;
    unordered_set<string> terminals;
    unordered_map<string, vector<ProductionRule *>> nonTerminals;
    vector<ProductionRule *> productionRules;
    unordered_map<string, unordered_set<string>> firstSets;
    unordered_map<string, unordered_set<string>> FollowSets;
    unordered_map<string, unordered_map<string, ProductionRule>> ll1Table;
    // non terminal , <ternminal , production >
    vector<string> sententialLines; // result

public:
    CFG(LexicalGeneratorBuilder *_lex)
    {
    }
    // set  DS of terminals and nonterminals and production rules
    void parseGrammerFile(string grammerFile)
    {
        string line;
        string input = "";

        ifstream myfile(grammerFile);

        if (myfile)
        {
            while (getline(myfile, line))
            {
                input += (line + " ");
            }
            myfile.close();
        }
        input = input + " #";

        std::string delimiter1 = "#";
        std::string delimiter2 = " ";
        size_t pos1 = 0;
        size_t pos2 = 0;
        std::string token;
        std::string prule;
        while ((pos1 = input.find(delimiter1)) != std::string::npos)
        {
            token = input.substr(0, pos1);
            std::cout << token << std::endl;
            int flag = 0;
            int flag1 = 0; //New Production Rule Flag
            int flag2 = 0;
            ProductionRule *pr = new ProductionRule();
            vector<string> rhs;

            while ((pos2 = token.find(delimiter2)) != std::string::npos)
            {

                prule = token.substr(0, pos2);

                if (prule != "" && prule != "=")
                {
                    if (flag == 0)
                    {
                        pr->setLhs(prule);
                        std::cout << prule << std::endl;
                        flag = 1;
                    }
                    else
                    {
                        if (flag1 == 0)
                        {
                            if (prule.at(0) == '\'')
                            {
                                prule.erase(0, 1);
                                prule.erase(prule.size() - 1);
                            }
                            rhs.push_back(prule);
                            pr->setRhs(rhs);
                            terminals.insert(prule);
                            std::cout << prule << std::endl;
                            flag1 = 1;
                        }
                        else
                        {
                            if (prule == "|")
                            {
                                //New Production Rule
                                //save current Production rule
                                productionRules.push_back(pr);

                                rhs.clear();
                                string lh = pr->getLhs();
                                pr->setLhs(lh);
                                flag2 = 1;
                                std::cout << lh << std::endl;
                                std::cout << productionRules.size() << std::endl;
                            }
                            else

                            {
                                if (flag2 == 0)
                                {
                                    if (prule.at(0) == '\'')
                                    {
                                        prule.erase(0, 1);
                                        prule.erase(prule.size() - 1);
                                    }
                                    rhs.push_back(prule);
                                    pr->setRhs(rhs);
                                    terminals.insert(prule);
                                    std::cout << prule << std::endl;
                                }
                                else
                                {
                                    if (prule.at(0) == '\'')
                                    {
                                        prule.erase(0, 1);
                                        prule.erase(prule.size() - 1);
                                    }
                                    rhs.push_back(prule);
                                    pr->setRhs(rhs);
                                    terminals.insert(prule);
                                    std::cout << prule << std::endl;
                                }
                            }
                        }
                    }
                }

                token = token.substr(pos2 + delimiter2.length());
            }
            if (pr->getLhs() != "")
            {
                productionRules.push_back(pr);
            }
            rhs.clear();
            std::cout << productionRules.size() << std::endl;
            std::cout << token << std::endl;
            input.erase(0, pos1 + delimiter1.length());
        }
        for (ProductionRule *pr : productionRules)
        {
            if ( nonTerminals.count(pr->getLhs()) > 0)
            {   vector<ProductionRule *> temp = nonTerminals[pr->getLhs()];
                temp.push_back(pr);
                nonTerminals[pr->getLhs()] = temp ;
            }
            else
            {   
                nonTerminals[pr->getLhs()].push_back(pr);

            }
        }

    }
    void computeFirstSets()
    {
        unordered_set<string> vis;
        for (string term : terminals)
        {
            vis.insert(term);
            firstSets[term].insert(term);
        }
        for (pair<string, vector<ProductionRule *>> nonterminal : nonTerminals)
        {
            string str = nonterminal.first;
            unordered_set<string> st = recursivefirstSet(str, vis);
            firstSets[nonterminal.first] = st;
        }
    }
    unordered_set<string> recursivefirstSet(string nonTerm, unordered_set<string> &vis)
    {
        /*unordered_set<string> res;
        if (vis.count(nonTerm)) {
            return firstSets[nonTerm];
        }
        for (ProductionRule* pr : nonTerminals[nonTerm])  {
            vector<string > rhs = pr->getRhs();
            
        }*/
    }

    void computeFollowSets()
    {
    }
    void GenerateParseTable()
    {
    }
    void parseInput()
    {
    }
    void eliminateLeftRecursion()
    {
    }
    void eliminateLeftFactor()
    {
    }
};

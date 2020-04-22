#include <bits/stdc++.h>
#include "../lexical analyzer generator/LexicalGeneratorBuilder.cpp"
#include "leftRec.cpp"
using namespace std;
class CFG
{
private:
    // add helper functions
    string eps;
    string startSymbol;
    string grammerFile;
    LexicalGeneratorBuilder *lexBuilder;
    unordered_set<string> terminals;
    unordered_map<string, vector<ProductionRule *>> nonTerminals;
    vector<ProductionRule *> productionRules;
    unordered_map<string, unordered_set<string>> firstSets;
    unordered_map<string, unordered_set<string>> FollowSets;
    unordered_map<string, unordered_map<string, ProductionRule>> ll1Table;
    // non terminal , <ternminal , production >
    vector<ProductionRule> sententialLines; // result

public:
    CFG(LexicalGeneratorBuilder *_lex, string _grammerFile)
    {

        eps = "Epsilon";
        grammerFile = _grammerFile;
        lexBuilder = _lex;
    }
    void BuildParser()
    {
        parseGrammerFile(grammerFile);

        eliminateLeftRecursionAndFactor();
        terminals.insert(eps);
        computeFirstSets();

        computeFollowSets();
        terminals.erase(eps);
        GenerateParseTable();

        parseInput();
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
        bool startSymbolSet = false;
        while ((pos1 = input.find(delimiter1)) != std::string::npos)
        {
            token = input.substr(0, pos1);
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
                        if (!startSymbolSet)
                        {
                            startSymbolSet = true;
                            startSymbol = prule;
                        }
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
                                terminals.insert(prule);
                            }
                            if (prule.compare("Epsilon") == 0)
                            {
                                terminals.insert(prule);
                            }
                            rhs.push_back(prule);
                            pr->setRhs(rhs);

                            flag1 = 1;
                        }
                        else
                        {
                            if (prule == "|")
                            {
                                //New Production Rule
                                //save current Production rule
                                /*cout << productionRules.size() << endl;
                                cout << pr->getLhs() << endl;
                                for (std::size_t j = 0; j < pr->getRhs().size(); ++j)
                                {
                                    std::cout << pr->getRhs()[j] << "ri"
                                              << "\n";
                                }*/
                                ProductionRule *tempo = new ProductionRule();
                                tempo;
                                productionRules.push_back(tempo);
                                productionRules[productionRules.size() - 1]->setLhs(pr->getLhs());
                                productionRules[productionRules.size() - 1]->setRhs(pr->getRhs());

                                rhs.clear();
                                string lh = pr->getLhs();
                                pr->setLhs(lh);
                                flag2 = 1;
                            }
                            else

                            {
                                if (flag2 == 0)
                                {
                                    if (prule.at(0) == '\'')
                                    {
                                        prule.erase(0, 1);
                                        prule.erase(prule.size() - 1);
                                        terminals.insert(prule);
                                    }
                                    if (prule.compare("Epsilon") == 0)
                                    {
                                        terminals.insert(prule);
                                    }
                                    rhs.push_back(prule);
                                    pr->setRhs(rhs);
                                }
                                else
                                {
                                    if (prule.at(0) == '\'')
                                    {
                                        prule.erase(0, 1);
                                        prule.erase(prule.size() - 1);
                                        terminals.insert(prule);
                                    }
                                    if (prule.compare("Epsilon") == 0)
                                    {
                                        terminals.insert(prule);
                                    }
                                    rhs.push_back(prule);
                                    pr->setRhs(rhs);
                                }
                            }
                        }
                    }
                }

                token = token.substr(pos2 + delimiter2.length());
            }
            if (pr->getLhs() != "")
            {
                cout << "here" << endl;
                productionRules.push_back(pr);
            }
            rhs.clear();

            input.erase(0, pos1 + delimiter1.length());
        }
        for (ProductionRule *pr : productionRules)
        {
            if (nonTerminals.count(pr->getLhs()) > 0)
            {
                vector<ProductionRule *> temp = nonTerminals[pr->getLhs()];
                temp.push_back(pr);
                nonTerminals[pr->getLhs()] = temp;
            }
            else
            {
                nonTerminals[pr->getLhs()].push_back(pr);
            }
        }
        // cout << "Terminals : ";
        // for (const auto &elem : terminals)
        // {
        //     cout << elem << " ";
        // }
        // cout << endl;
        // cout << endl;
        // cout << "nonterminals" << endl;
        // for (std::size_t i = 0; i < productionRules.size(); ++i)
        // {
        //     std::cout << productionRules[i]->getLhs() << ": ";
        //     for (std::size_t j = 0; j < productionRules[i]->getRhs().size(); ++j)
        //     {
        //         std::cout << productionRules[i]->getRhs()[j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
    }
    void computeFirstSets()
    {
        /***
         * directed graph based algorithm for computing the first sets :
         * an edge(A,B) is included to the graph if first (B) is subset of first(A)
         * so by doing a depth first search for every unvisited node we can construct all
         * the first sets of the grammar
         * conclusions: from the properties of LL1 is that it is not left recursive so
         * there would not be any cycle in the graph  (path of A to A not exist)so the graph is
         * DAG so no strongly connected components is of size > 1 proving that the algorithm
         * would not reach a case of  INFIINITE LOOP
         * complextixity is O(V+E)
         * */
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
            firstSets[str] = st;
        }
        firstSets.erase(eps);
        // cout << "first sets: " << endl;
        // for (pair<string, unordered_set<string>> ff : firstSets)
        // {
        //     cout << ff.first << " : ";
        //     for (string sss : ff.second)
        //     {
        //         cout << sss << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
    }
    unordered_set<string> recursivefirstSet(string nonTerm, unordered_set<string> &vis)
    {
        if (vis.count(nonTerm))
        {
            return firstSets[nonTerm];
        }
        vis.insert(nonTerm);
        for (ProductionRule *pr : nonTerminals[nonTerm])
        {
            vector<string> rhs = pr->getRhs();
            int i = 0;
            for (string s : rhs)
            {
                unordered_set<string> st = recursivefirstSet(s, vis);
                firstSets[nonTerm].insert(st.begin(), st.end());
                if (!st.count(eps))
                    break;
                i++;
            }
            if (i == rhs.size())
                firstSets[nonTerm].insert(eps);
        }

        return firstSets[nonTerm];
    }

    void computeFollowSets()
    {
        /**
         * compute follow from first sets
         * for each production rule if a nonterminal X followed by sequence beta then
         * all first set of beta is included in the follow set of X
        */
        FollowSets[startSymbol].insert("$");
        for (ProductionRule *rule : productionRules)
        {
            vector<string> rhs = rule->getRhs();
            unordered_set<string> first_next;
            int n = rhs.size();
            first_next = firstSets[rhs[n - 1]];

            for (int i = n - 2; i >= 0; i--)
            {
                string prev = rhs[i];
                FollowSets[prev].insert(first_next.begin(), first_next.end());
                FollowSets[prev].erase(eps);
                if (firstSets[prev].count(eps))
                {
                    first_next = FollowSets[prev];
                }
                else
                {
                    first_next = firstSets[prev];
                }
            }
        }

        /**
         *
         * construcing directed graph where edge (A,B) exists if followset(A) includes followset(B) or
         * follow(B) is subset of follow(A) , there could exist a cycle in this graph producing
         * Strongly connected components where the follow(members) of this SCC equal to each other
         * Tarjan's algorithm make the way through this graph and finding all the included follow sets
         * in each non terminal by combining the follow sets of all the members of a SCC
         * into a set which would be the followset of each member in SCC
         */
        unordered_map<string, unordered_set<string>> adjList;
        for (ProductionRule *pr : productionRules)
        {
            string lhs = pr->getLhs();
            vector<string> rhs = pr->getRhs();
            int n = rhs.size();
            for (int i = n - 1; i >= 0; i--)
            {
                string str = rhs[i];
                adjList[str].insert(lhs);
                if (!firstSets[str].count(eps))
                    break;
            }
        }
        adjList.erase(eps);
        unordered_set<string> onStack;
        unordered_map<string, int> ids;
        unordered_map<string, int> lowLink;
        stack<string> stack;
        int id = 0;
        for (pair<string, unordered_set<string>> p : adjList)
        {
            string node = p.first;
            if (!ids.count(node))
                dfs(node, id, adjList, onStack, ids, lowLink, stack);
            FollowSets[node].erase(eps);
        }
        // cout << "follow sets" << endl;
        // for (pair<string, unordered_set<string>> ff : FollowSets)
        // {
        //     cout << ff.first << " : ";
        //     for (string sss : ff.second)
        //     {
        //         cout << sss << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
    }

    void dfs(string at, int &id, unordered_map<string, unordered_set<string>> &adjList,
             unordered_set<string> &onStack, unordered_map<string, int> &ids,
             unordered_map<string, int> &lowLink, stack<string> &stack)
    {
        stack.push(at);
        onStack.insert(at);
        ids[at] = id;
        lowLink[at] = id;
        id++;
        for (string to : adjList[at])
        {
            if (!ids.count(to))
            {
                dfs(to, id, adjList, onStack, ids, lowLink, stack);
            }
            if (onStack.count(to))
            {
                lowLink[at] = min(lowLink[at], lowLink[to]);
            }
            FollowSets[at].insert(FollowSets[to].begin(), FollowSets[to].end());
        }
        if (ids[at] == lowLink[at])
        {
            unordered_set<string> combined;
            vector<string> vec;
            while (!stack.empty())
            {
                string top = stack.top();
                stack.pop();
                vec.push_back(top);
                onStack.erase(top);
                lowLink[top] = ids[at];
                combined.insert(FollowSets[top].begin(), FollowSets[top].end());
                if (top == at)
                    break;
            }
            for (string v : vec)
            {
                FollowSets[v].insert(combined.begin(), combined.end());
            }
        }
    }
    void GenerateParseTable()
    {
        /**/
        terminals.insert("$");
        for (auto NT : nonTerminals)
        {
            string lhs = NT.first;
            vector<ProductionRule *> rhss = NT.second;
            unordered_set<string> first = firstSets[lhs];
            unordered_set<string> follow = FollowSets[lhs];
            unordered_map<string, ProductionRule> entry;
            for (auto itr : terminals)
            {
                string T = itr;
                ProductionRule pr;
                pr.setLhs(lhs);
                if (first.find(T) != first.end())
                { //case in first set

                    for (int counter = 0; counter < rhss.size(); counter++)
                    {
                        ProductionRule *pr_ptr = rhss[counter];
                        if (find_pr(T, pr_ptr))
                        {

                            pr.setRhs(pr_ptr->getRhs());
                            entry[T] = pr;
                            break;
                        }
                    }
                }
                else if (follow.find(T) != follow.end())
                { // case in follow set
                    vector<string> vec;

                    if (first.find("Epsilon") != first.end())
                    { // epsilon case
                        vec.push_back("Epsilon");
                        pr.setRhs(vec);
                        entry[T] = pr;
                    }
                    else
                    { // sync case
                        vec.push_back("Sync");
                        pr.setRhs(vec);
                        entry[T] = pr;
                    }
                }
                //case entry is empty nothing happens
            }
            ll1Table[lhs] = entry;
        }
        cout << endl
             << "parse table" << endl;
        cout << "-----------------------------" << endl;
        int cnt0 = 1;
        for (auto curr : ll1Table)

        {
            string row = curr.first;
            cout << cnt0 << ". " << row << endl;
            unordered_map<string, ProductionRule> cols = curr.second;
            char cnt1 = 'a';
            for (auto entry : cols)
            {
                ProductionRule pr = entry.second;
                vector<string> vct = pr.getRhs();
                string s = ". " + entry.first + " : ";
                s = cnt1 + s;
                for (int counter = 0; counter < vct.size(); counter++)
                {
                    s += vct[counter] + " ";
                }
                cout << s << endl;
                cnt1++;
            }
            cnt0++;
            cout << endl;
        }
    }
    bool find_pr(string T, ProductionRule *pr_ptr)
    {
        string NT = pr_ptr->getLhs();
        vector<string> rhs = pr_ptr->getRhs();
        for (int counter = 0; counter < rhs.size(); counter++)
        {
            string curr = rhs[counter];
            unordered_set<string> curr_first = firstSets[curr];
            if (curr_first.find(T) != curr_first.end())
            {
                return true;
            }
            if (curr_first.find("Epsilon") == curr_first.end())
            {
                break;
            }
        }
        return false;
    }

    void parseInput()
    {
        stack<string> non_term_st;
        non_term_st.push("$");
        non_term_st.push(startSymbol);
        string next_token = lexBuilder->nextToken();
        while (true)
        {
            string top_elem = non_term_st.top();

            if (top_elem.compare("$") == 0 && next_token.compare("$") == 0)
            {
                cout << "end of procesing and ACCEPTED" << endl;
                break;
            }
            if (top_elem.compare("$") == 0 && next_token.compare("$") != 0)
            {

                cout << "end of processing and NOT ACCEPTED part of the input "
                     << "isnot matched(the stack is empty while the ip is not)" << endl;
                break;
            }
            //case top is terminal
            if (terminals.find(top_elem) != terminals.end())
            {
                //case matches the i/p
                if (top_elem.compare(next_token) == 0)
                {
                    cout << next_token << " matched" << endl;
                    next_token = lexBuilder->nextToken();
                    non_term_st.pop();
                }
                else
                { // if they dont match

                    cout << "ERROR : missing " << top_elem << " and inserted in input" << endl;
                    non_term_st.pop();
                }
            }
            else
            { //case top is non-terminal
                unordered_map<string, ProductionRule> row = ll1Table[top_elem];
                ///case entry found
                if (row.find(next_token) != row.end())
                {

                    ProductionRule pr = row[next_token];
                    sententialLines.push_back(pr);
                    vector<string> rhs = pr.getRhs();

                    /*next_token = lexBuilder->nextToken();*/
                    non_term_st.pop();
                    if (rhs[0] != "Sync")
                    {
                        if (rhs[0] != "Epsilon")
                        {

                            for (int counter = rhs.size() - 1; counter >= 0; counter--)
                            {
                                non_term_st.push(rhs[counter]);
                            }
                            string s = pr.getLhs() + " --> ";
                            for (int counter = 0; counter < rhs.size(); counter++)
                            {
                                s += (rhs[counter] + " ");
                            }
                            cout << s << endl;
                        }
                        else
                        {
                            cout << top_elem << " --> Epsilon" << endl;
                        }
                    }
                    else
                    {
                        cout << "ERROR sync entry: " << top_elem << " missing and discarded from stack" << endl;
                    }
                }
                else
                { ///entry is empty

                    if (next_token.compare("$") == 0)
                    {
                        cout << "process end and NOT ACCEPTED part of the input is missing"
                             << "stack is not empty while the i/p finished" << endl;

                        break;
                    }
                    cout << "ERROR empty entry: illegal input " << next_token << " discarded from i/p" << endl;
                    next_token = lexBuilder->nextToken();
                }
            }
        }
    }
    void eliminateLeftRecursionAndFactor()
    {
        leftRec *rec = new leftRec(productionRules);
        productionRules = rec->get_Rules();
        nonTerminals = rec->getNonTerminals();
        // cout << "nonterminals after left factoring" << endl;
        // for (pair<string, vector<ProductionRule *>> p : nonTerminals)
        // {
        //     for (ProductionRule *pr : p.second)
        //     {
        //         cout << pr->getLhs() << " -> ";
        //         for (string s : pr->getRhs())
        //         {
        //             cout << s << " ";
        //         }
        //         cout << endl;
        //     }
        // }
        // cout << endl;
        // cout << endl;
        // cout << "nonterminals" << endl;
        // for (std::size_t i = 0; i < productionRules.size(); ++i)
        // {
        //     std::cout << productionRules[i]->getLhs() << ": ";
        //     for (std::size_t j = 0; j < productionRules[i]->getRhs().size(); ++j)
        //     {
        //         std::cout << productionRules[i]->getRhs()[j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
    }
};

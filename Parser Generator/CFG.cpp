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
        startSymbol = "E";
        terminals = {"*", "+", "(", ")", "int", "epsilon"};
        ProductionRule *p1 = new ProductionRule("E", {"T", "X"});
        ProductionRule *p2 = new ProductionRule("T", {"(", "E", ")"});
        ProductionRule *p3 = new ProductionRule("T", {"int", "Y"});
        ProductionRule *p4 = new ProductionRule("X", {"+", "E"});
        ProductionRule *p5 = new ProductionRule("X", {"epsilon"});
        ProductionRule *p6 = new ProductionRule("Y", {"epsilon"});
        ProductionRule *p7 = new ProductionRule("Y", {"*", "T"});
        productionRules = {p1, p2, p3, p4, p5, p6, p7};
        nonTerminals["T"] = {p2, p3};
        nonTerminals["E"] = {p1};
        nonTerminals["X"] = {p4, p5};
        nonTerminals["Y"] = {p6, p7};
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
        std::cout << input << std::endl;

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
                        if (flag1 = 0)
                        {
                            rhs.push_back(prule);
                            pr->setRhs(rhs);
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
                                    rhs.push_back(prule);
                                    pr->setRhs(rhs);
                                    std::cout << prule << std::endl;
                                }
                                else
                                {
                                    rhs.push_back(prule);
                                    pr->setRhs(rhs);
                                    std::cout << prule << std::endl;
                                }
                            }
                        }
                    }
                }
                token = token.substr(pos2 + delimiter2.length());
            }
            std::cout << token << std::endl;

            input.erase(0, pos1 + delimiter1.length());
        }

        std::cout << input << std::endl;
        while ((pos2 = input.find(delimiter2)) != std::string::npos)
        {
            prule = input.substr(0, pos2);
            std::cout << prule << std::endl;
            input = input.substr(pos2 + delimiter2.length());
        }
        std::cout << input << std::endl;
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
        firstSets.erase("epsilon");
        cout<<" first sets: " <<endl;
        for (pair<string, unordered_set<string>> ff : firstSets)
        {
            cout << ff.first << " : ";
            for (string sss : ff.second)
            {
                cout << sss << " ";
            }
            cout << endl;
        }
        cout<<endl;
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
                if (!st.count("epsilon"))
                    break;
                i++;
            }
            if (i == rhs.size())
                firstSets[nonTerm].insert("epsilon");
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
                FollowSets[prev].erase("epsilon");
                if (firstSets[prev].count("epsilon"))
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
                if (!firstSets[str].count("epsilon"))
                    break;
            }
        }
        adjList.erase("epsilon");
        unordered_set<string> onStack;
        unordered_map<string, int> ids;
        unordered_map<string, int> lowLink;
        stack<string> stack;
        int id = 0;
        for (pair<string, unordered_set<string>> p : adjList)
        {
            string node = p.first;
            if (!ids.count(node))
                dfs(node,id,adjList,onStack,ids,lowLink,stack);
            FollowSets[node].erase("epsilon");
        }
        cout<<"follow sets"<<endl;
        for (pair<string, unordered_set<string>> ff : FollowSets)
        {
            cout << ff.first << " : ";
            for (string sss : ff.second)
            {
                cout << sss << " ";
            }
            cout << endl;
        }
    }

    void dfs(string at,int &id ,unordered_map<string, unordered_set<string>> &adjList, 
            unordered_set<string> &onStack,unordered_map<string, int> &ids,
             unordered_map<string, int> &lowLink, stack<string> &stack)
    {
        stack.push(at);
        onStack.insert(at);
        ids[at] = id;
        lowLink[at] = id;
        id++;
        for(string to :  adjList[at]){
            if(!ids.count(to)){
                dfs(to,id,adjList,onStack,ids,lowLink,stack);
            }
            if(onStack.count(to)){
                lowLink[at] = min(lowLink[at] , lowLink[to]);
            }
            FollowSets[at].insert(FollowSets[to].begin(), FollowSets[to].end());
        }
        if(ids[at] == lowLink[at]){
            unordered_set<string> combined;
            vector<string> vec;
            while(!stack.empty()){
                string top =  stack.top();
                stack.pop();
                vec.push_back(top);
                onStack.erase(top);
                lowLink[top] = ids[at];
                combined.insert(FollowSets[top].begin(),FollowSets[top].end()); 
                if(top == at)
                    break;
            }
            for(string v : vec){
                FollowSets[v].insert(combined.begin(), combined.end()); 
            }
        }
    }
    void GenerateParseTable()
    {
    }
    void parseInput(){
        stack<string> non_term_st;
        non_term_st.push("$");
        non_term_st.push(startSymbol);
        string next_token = lexBuilder->nextToken();
        while (true)
        {
            string top_elem = non_term_st.top();

            if (top_elem.compare("$") == 0 && next_token.compare("$") == 0)
            {
                ///syso end of processing and accepted
                break;
            }
            if (top_elem.compare("$") == 0 && next_token.compare("$") != 0)
            {
                ///syso end of processing not accepted part of the input
                ///isnot matched(the stack is empty while the ip is not)
                break;
            }
            //case top is terminal
            if (terminals.find(top_elem) != terminals.end())
            {
                //case matches the i/p
                if (top_elem.compare(next_token) == 0)
                {
                    ///syso matched  next_token
                    next_token = lexBuilder->nextToken();
                    non_term_st.pop();
                }
                else
                { // if they dont match

                    ///syso "Warning" missing  top_elem and inserted
                    non_term_st.pop();
                }
            }
            else
            { //case top is non-terminal
                unordered_map<string, ProductionRule> row = ll1Table[top_elem];
                ///case entry found
                if (row.find(next_token) != row.end())
                {
                    if (/*not sync production rule*/)
                    {
                        ProductionRule pr = row[next_token];
                        sententialLines.push_back(pr);
                        ///syso production rule nfso
                        next_token = lexBuilder->nextToken();
                        non_term_st.pop();
                        if (/*production rule is not epsilon*/)
                        {
                            vector<string> rhs = pr.getRhs();
                            for (int counter = rhs.size() - 1; counter >= 0; counter--)
                            {
                                non_term_st.push(rhs[counter]);
                            }
                        }
                    }
                    else
                    { ///sync
                        ///syso error illegal non terminal top_elem , top_elem discarded
                        non_term_st.pop();
                    }
                }
                else
                { ///entry is empty

                    if (next_token.compare("$") == 0)
                    {
                        ///syso not accepted ip ended while stack is not empty yet part of the ip is missing
                        break;
                    }
                    ///syso error illegal non terminal top_elem , next_token discarded
                    next_token = lexBuilder->nextToken();
                }
            }
        }
    }
    void eliminateLeftRecursion()
    {
    }
    void eliminateLeftFactor()
    {
    }
};

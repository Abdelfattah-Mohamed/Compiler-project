#ifndef PRODUCTIONRULE_H
#define PRODUCTIONRULE_H

#include<bits/stdc++.h>
using namespace std;

class ProductionRule
{
public:
    ProductionRule();
    ProductionRule(string _rhs, vector<string> _lhs);
    string getRhs();
    vector<string>  getLhs();
    void setLhs(string _rhs);
    void setRhs(vector<string> _lhs);
private:
    string rhs;
    vector<string> lhs; 
};
#endif
#include <bits/stdc++.h>
using namespace std;

class ProductionRule
{
public:
    ProductionRule()
    {
    }
    ProductionRule(string _lhs, vector<string> _rhs)
    {
        lhs = _lhs;
        rhs = _rhs;
    }
    string getLhs()
    {
        return lhs;
    }
    vector<string> getRhs()
    {
        return rhs;
    }
    void setLhs(string _lhs)
    {
        lhs = _lhs;
    }
    void setRhs(vector<string> _rhs)
    {
        rhs = _rhs;
    }

private:
    string lhs;
    vector<string> rhs;
};
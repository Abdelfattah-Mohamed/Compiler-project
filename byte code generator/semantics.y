%{
#define INTEGER 0
#define FLOAT 1

#include<bits/stdc++.h>

using namespace std;


map<string,string> arith_op = {
    {"+", "add"}, 
    {"*", "mul"}, 
    {"-", "sub"},
    {"/", "div"}
}

map<string,string> i_cond = {
    {">", "if_icmple"},
    {"<", "if_icmpge"},
    {"==", "if_icmpne"},
    {"!=", "if_icmpeq"},
    {"<=", "if_icmpgt"},
    {">=", "if_icmplt"}
}

map<string,string> f_cond = {
    {">", "ifle"},
    {"<", "ifge"},
    {"==", "ifne"},
    {"!=", "ifeq"},
    {"<=", "ifgt"},
    {">=", "iflt"}
}

}%

%union{
    int intVal;
    float flaotVal;
    int boolVal;
    char* id;
    char* op;
    int exType;
    struct {
		vector<int> *trueList, *falseList;
	} boolEx;
	struct {
		vector<int> *nextList;
	} stmt;
    int primType;
}
%token int_word
%token bool_word
%token float_word
%token if_word
%token else_word
%token while_word   
%token <intVal> INT
%token <flaotVal> REAL
%token <id> ID
%token <op> ARTHOP
%token <op> RELOP
%token ASSIGN
%token RELOP
%token ARTHOP
%token  SEMICOLON
%token  LEFTBRACKET
%token RIGHTBRACKET
%token LEFTCURLY
%token RIGHTCURLY
%type <extype> expression
%type <boolEx> boolExpression
%type <primType> primitave_type
%type <stmt>  statement
%type <stmt>  statement_list
%type <stmt> if
%type <stmt> while
%type <ival> marker
%type <ival> goto


%%


%%




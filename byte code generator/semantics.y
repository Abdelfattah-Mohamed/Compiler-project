%{
#define INTEGER 0
#define FLOAT 1
#define BOOL 2

#include<bits/stdc++.h>

using namespace std;

 /* arithmetic operations */
map<string,string> arith_op = {
   
    {"+", "add"},
    {"*", "mul"},
    {"-", "sub"},
    {"/", "div"}
};
/* rel operations for int*/
map<string,string> i_cond = {
    
    {"<=", "if_icmple"},
    {">=", "if_icmpge"},
    {"!=", "if_icmpne"},
    {"==", "if_icmpeq"},
    {">", "if_icmpgt"},
    {"<", "if_icmplt"}
};
 /* rel operations for float*/
map<string,string> f_cond = {
   
    {"<=", "ifle"},
    {">=", "ifge"},
    {"!=", "ifne"},
    {"+=", "ifeq"},
    {">", "ifgt"},
    {"<", "iflt"}
};

/*the symbol table maps a string key represents the id /var name 
 to a pair of integers first is the index of that variable in the memory 
 it will be used in the rules and the second represents the type of that variable 
 int or float to be tested before generating the rules */
map<string,pair<int,int>> symbol_table;
/*holds the current program counter to print it next to instructions and to specify jumps*/
int PC=0;
/*represents the index (place) of the var in the memory , will also be used in the instructions*/
int var_index=0;
/*holds the string of each line of code */
vector<string> code_lines;

////TODO put all the functions declarations here

}%

%start METHOD_BODY

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

////TODO i removed some of the things from the original code here revise them
%%
/*starting with the start symbol*/
METHOD_BODY : statement_list ;
/*we changed the order to remove the left recr*/
statement_list : statement |
	statement
	statement_list ;

statement: 
	declaration {vector<int> * v = new vector<int>(); $$.nextList =v;}
	|if {$$.nextList = $1.nextList;}
	|while 	{$$.nextList = $1.nextList;}
	|for {$$.nextList = $1.nextList;}
	| assignment {vector<int> * v = new vector<int>(); $$.nextList =v;}
	;
/*multivariable declaration is not allowed*/
declaration: 
	primitive_type IDENTIFIER SEMI_COLON
    ////TODO
    {
        string str($2);
        create_new_var(str,$1)
        }
    ;
/*sets the primitive data type to its corresponding int*/
primitive_type: 
	int_word {$$ = INTEGER;}
	| float_word {$$ = FLOAT;}
	| bool_word {$$ = BOOL;}
	;


%%



void create_new_var(string id, int type){
    //if the var name is taken then err
    if((symbol_table.find(id) != symbol_table.end())){
        ////TODO make the error msg 
    }else{

        // make the default value = 0 and store it in the place of the index of that varibale in memory
        if(type == INTEGER)
		{
            addLineCode(to_string(PC)+": iconst_0\n");
            PC+=1;
			addLineCode(to_string(PC)+": istore " + to_string(var_index)+"\n");
            PC+=2;
		}
		else if ( type == FLOAT)
		{
            addLineCode(to_string(PC)+": fconst_0\n");
            PC+=1;
			addLineCode(to_string(PC)+": fstore " + to_string(var_index)+"\n");
            PC+=2;
		}
		symbTab[name] = make_pair(var_index,(type_enum)type);
        var_index++;

    }
}

void addLineCode(string x)
{
	code_lines.push_back(x);
}


%{
#include <bits/stdc++.h>
#include <unistd.h>

#define INTEGER 0
#define FLOAT 1
#define BOOLEAN 2

using namespace std;

extern  int yylex();
extern  FILE *yyin;
void yyerror(const char * s);

void addLineCode(string x);
void create_new_var(string id, int type);
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

%}


%code requires {
	#include <vector>
	using namespace std;
}

%start METHOD_BODY

%union{
    int intVal;
    float floatVal;
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
%token<id> IDENTIFIER   
%token <intVal> INT
%token <floatVal> REAL
%token <boolVal> BOOL
%token <op> ARTHOP
%token <op> RELOP
%token <op> BOOLOP
%token ASSIGN
%token  SEMICOLON
%token  LEFTBRACKET
%token RIGHTBRACKET
%token LEFTCURLY
%token RIGHTCURLY
%type <extype> expression
%type <boolEx> boolExpression

%type <primType> primitive_type
%type <stmt>  statement
%type <stmt>  statement_list
%type <stmt> if
%type <stmt> while
%type <ival> marker
%type <ival> goto


////TODO i removed some of the things from the original code here revise them
%%
METHOD_BODY: statement_list 
            marker
            {
                backpatch($1.nextList,$2);
            };
marker:{
    $$ = PC;
};
statement_list: statement |
	statement
    marker
	statement_list
    {
        backpatch($1.nextList,$2);
        $$.nextList = $3.nextList;
    } ;

statement: 
	declaration {vector<int> * v = new vector<int>(); $$.nextList =v;}
	|if {$$.nextList = $1.nextList;}
	|while 	{$$.nextList = $1.nextList;}
	| assignment {vector<int> * v = new vector<int>(); $$.nextList =v;}
	;
declaration: 
	primitive_type IDENTIFIER SEMICOLON
    ////TODO
    {
        string str($2);
        create_new_var(str,$1);
    }
    ;
/*sets the primitive data type to its corresponding int*/
primitive_type: 
	int_word {$$ = INTEGER;}
	| float_word {$$ = FLOAT;}
	| bool_word {$$ = BOOLEAN;}
	;
boolExpression: 
BOOL{
    $$.trueList = new vector<int>();
    $$.falseList = new vector<int>();
    if($1){
       $$.trueList->push_back(PC);
       addLineCode("goto ");
    }else{
       $$.falseList->push_back(PC);
       addLineCode("goto ");
    }
    PC +=3;
}|
boolExpression
BOOLOP
marker
boolExpression
{
    if(!strcmp($2,"||")){
        backpatch($1.falseList, $3);
        $$.trueList = merge($1.trueList, $4.trueList);
        $$.falseList = $4.falseList;
    }else {
        backpatch($1.trueList, $3);
        $$.trueList = $3.trueList;
        $$.falseList = merge($1.falseList, $3.falseList);
    }
}
%%



void create_new_var(string id, int type){
    //if the var name is taken then err
    if(symbol_table.count(id)){
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
		}else{
            return;
        }
		symbol_table[id] = make_pair(var_index,type);
        var_index++;

    }
}

void addLineCode(string x)
{
	code_lines.push_back(x);
}
void yyerror(char const *s)
{
  fprintf (stderr, "%s\n", s);
}
void backpatch(vector<int> * list ,int pc){
    if(list == nullptr)
        return;
    for(int i =0 ; i < list->size();i++){
        code_lines[(*list)[i]] +=(" " +to_string( pc)); 
    }
}
vector<int> * merge(vector<int> * list1 , vector<int> * list2){
    
    vector<int> *newlist =  new vector<int> ();
    if(list1 != nullptr && list2 != nullptr){
        newlist->insert(newlist->end(),list1->begin() , list1->end());
        newlist->insert(newlist->end(),list2->begin() , list2->end());
    }else if(list1 != nullptr){
        newlist->insert(newlist->end(),list1->begin() , list1->end());
    }else  if(list2 != nullptr){
        newlist->insert(newlist->end(),list2->begin() , list2->end());
    }
    return newlist;
}

main(int argv , char *argc[]){
    
	FILE *myfile;
	if(argv == 1){
        printf("error");
        return -1;
    }
    myfile = fopen(argc[1], "r");
	
	if (!myfile) {
		return -1;
	}
	yyin = myfile;
    yyparse();
    for(string s : code_lines){
        cout<<s<<endl;
    }
}


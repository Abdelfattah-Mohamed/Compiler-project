%{
int numErrors = 0;
char* arg;
typedef struct node {
	char* lexeme;
	char* token;
	struct node* next;
} node_t;
node_t head;
node_t* current = &head;
int yywrap(void);
void store(char* lexeme);
void error(void);
void printStored(void);
%}
if_t			"if"
while_t			"while"
else_t			"else"
boolean			"boolean"
int 			"int"
float			"float"
letter 			[a-zA-Z]
digit			[0-9]
num				{digits}|({digits}"."{digits}(""|"E"{digits}))
id				{letter}({letter}|{digit})*
digits			{digit}+
addop			("+"|"-")
mulop			("*"|"/")
delim			(";"|","|"("|")"|"{"|"}")
assign			=
relop			("=="|"!="|">"|">="|"<"|"<=")	
whitespace		(\t|" "|\r)
newline			\n
%%
{int}					{ECHO; arg = "int"; store("");}
{boolean}				{ECHO; arg = "boolean"; store("");}
{float}					{ECHO; arg = "float"; store("");}
{if_t}					{ECHO; arg = "if"; store("");}
{else_t}					{ECHO; arg = "else"; store("");}
{while_t}					{ECHO; arg = "while"; store("");}
{whitespace}			{ECHO;}
{newline}				{ECHO;}
{num}					{ECHO; arg = "num"; store(""); }
{id}					{ECHO; arg = "id"; store("");}
{delim}					{ECHO; arg = ""; store(yytext);}
{relop}					{ECHO; arg = "relop"; store("");}
{addop}					{ECHO; arg = "addop"; store("");}
{mulop}					{ECHO; arg = "mulop"; store("");}
{assign}				{ECHO; arg = "assign"; store("");}
.						{ECHO; numErrors++; error();}
%%
int yywrap(void) {
	return 1;
}
void store(char* lexeme) {
	current->lexeme = malloc(sizeof(strlen(lexeme)+1));
	strcpy(current->lexeme,lexeme);
	current->token = malloc(sizeof(strlen(arg)+1));
	strcpy(current->token,arg);
	node_t* temp;
	temp = malloc(sizeof(node_t));
	current->next = temp;
	current = current->next;
}
void error(void) {
	printf("[e]");
}
void printStored(void) {
	node_t* c = &head;
	FILE* f = fopen("Tokens.txt","w");

	while (c->next) {
		fprintf(f,"%s\t%s\n",c->lexeme,c->token);
		c = c->next;
	}
	fclose(f);
	printf("Tokens.txt written.\n");
}
int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Please enter one filename as an argument.\n");
		return -1;
	}
	yyin = fopen(argv[1],"r");
	yylex();
	fclose(yyin);
	printf("\nLexicalErrors %d\n",numErrors);
	printStored();
	return 0;
}
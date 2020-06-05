%{
	#include "y.tab.h"
	#include <bits/stdc++.h>
%}
if_t			"if"
while_t			"while"
else_t			"else"
boolean			"boolean"
int 			"int"
float			"float"
BOOL            ("true"|"false")
letter 			[a-zA-Z]
digit			[0-9]
digits			{digit}+
INTEGER		    ("+"|"-")?{digits}
REAL            ("+"|"-")?{digits}.{digits}("E"{digits}+)?
id				{letter}({letter}|{digit})*
arthop			("+"|"-"|"*"|"/")
boolop			("||"|"&&")
assign			"="
relop			("=="|"!="|">"|">="|"<"|"<=")	
whitespace		(\t|" "|\r)
newline			\n
%%
{int}					{return int_word;}
{boolean}				{return bool_word;}
{float}					{return float_word;}
{if_t}					{return  if_word;}
{else_t}				{return else_word;}
{while_t}				{return while_word;}
{whitespace}			{}
{newline}				{}
{INTEGER}				{yylval.intVal =  atoi(yytext);  return INT;}
{REAL}                  {yylval.floatVal = atof(yytext); return REAL;}
{BOOL}                  {yylval.boolVal = (strcmp(strdup(yytext),"true") ? 1 : 0); return BOOL;}
{id}					{yylval.id = strdup(yytext); return IDENTIFIER;}
";"                     {return SEMICOLON;}
"("				        {return LEFTBRACKET;}
")"				        {return RIGHTBRACKET;}
"{"                     {return LEFTCURLY;}
"}"                     {return RIGHTCURLY;}
{arthop}			    {yylval.op = strdup(yytext); return ARTHOP;}
{assign}				{return ASSIGN;}
{relop}                 {yylval.op = strdup(yytext); return RELOP;}
{boolop}				{yylval.op = strdup(yytext); return BOOLOP;}
. 						{}
%%
int yywrap(void) {
	return -1;
}

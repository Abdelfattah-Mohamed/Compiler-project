all: 
	flex lex.l
	bison -y -d syntax.y
	g++ -std=c++11 lex.yy.c y.tab.c
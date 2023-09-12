#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#pragma once
extern int sym;
extern int line_length;
extern char line[1024];
extern char token[100];
enum symbol {
	CONSY, INTSY, CHARSY, VOIDSY, MAINSY, IFSY, WHILESY, SWITCHSY, CASESY, DEFAULTSY, SCANFSY, PRINTFSY, RETURNSY,
	IDENSY, CHAR2SY, INT2SY, STRINGSY,
	PLUSSY, MINUSSY, MULTSY, DIVSY, ASSIGNSY, COMMASY, COLONSY, SEMISY, LPARSY, RPARSY, LBRASY, RBRASY, LBPARSY, RBPARSY, LESY, LEEQSY, MOSY, MOEQSY, EQSY, NEQSY, APOSY, DQUOSY
};//所有类型符
extern const char *KEYWORD[13];
extern bool ischar(int c);
extern bool isinasc(int c);
extern bool iszero(int c);
extern bool isplus(int c);
extern bool isminus(int c);
extern bool ismult(int c);
extern bool isdiv(int c);
extern bool isassign(int c);
extern bool iscomma(int c);
extern bool iscolon(int c);
extern bool issemi(int c);
extern bool islpar(int c);
extern bool isrpar(int c);
extern bool islbra(int c);
extern bool isrbra(int c);
extern bool islbpar(int c);
extern bool isrbpar(int c);
extern bool isless(int c);
extern bool ismore(int c);
extern bool isexc(int c);
extern bool isdquot(int c);
extern bool isapo(int c);
extern int iskey();
extern void get_char();
extern int stringtonum();
extern int getsym();

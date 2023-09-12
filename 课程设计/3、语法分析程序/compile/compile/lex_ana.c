#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>
#include"lex_ana.h"
#include"error.h"
extern FILE * compile_file;
extern FILE * lexana_file;	
char line[1024];
int xh = 1;
int dquo_flag = 0;
int sym = 0;
int cal_num;
int ch1;
int line_num = 0;    //µ±Ç°¶ÁÈëµÄÐÐÊý
int line_length;     //µ±Ç°ÐÐµÄ³¤¶È 
int line_loc = 0;         //µ±Ç°¶Á×Ö·ûµÄÎ»ÖÃ
int ch;	  //¶ÁÈëµÄµ±Ç°×Ö·û
const int nke = 13;//¹Ø¼ü×ÖÊýÁ¿
char token[100];
int tok_loc = 0;
const char *KEYWORD[13] = { "const","int","char","void","main","if","while","switch","case","default","scanf","printf","return" };
bool ischar(int c) {    //ÅÐ¶ÏÊÇ·ñÎª×ÖÄ¸
	if (isalpha(c) || (c == '_'))
		return 1;
	return 0;
}
bool isinasc(int c) {    //ÅÐ¶ÏÊÇ·ñ·ûºÏ×Ö·û´®ÔÚascii±íµÄ×Ö·û
	if (c == 32 || c == 33 || (c >= 35 && c <= 126))
		return 1;
	return 0;
}
bool iszero(int c) {    //ÅÐ¶ÏÊÇ·ñÊÇ0
	if (c == '0')
		return 1;
	return 0;
}
bool isplus(int c) {    //ÅÐ¶ÏÊÇ·ñÊÇ¼ÓºÅ
	if (c == '+')
		return 1;
	return 0;
}
bool isminus(int c) {		//ÅÐ¶ÏÊÇ·ñÊÇ¼õºÅ
	if (c == '-')
		return 1;
	return 0;
}
bool ismult(int c) {		//ÅÐ¶ÏÊÇ·ñÊÇ³ËºÅ
	if (c == '*')
		return 1;
	return 0;
}
bool isdiv(int c) {		//ÅÐ¶ÏÊÇ·ñÊÇ³ýºÅ
	if (c == '/')
		return 1;
	return 0;
}
bool isassign(int c) {		//ÅÐ¶ÏÊÇ·ñÊÇ'='
	if (c == '=')
		return 1;
	return 0;
}
bool iscomma(int c) {		//ÅÐ¶Ï','
	if (c == ',')
		return 1;
	return 0;
}
bool iscolon(int c) {		//ÅÐ¶Ï':'
	if (c == ':')
		return 1;
	return 0;
}
bool issemi(int c) {		//ÅÐ¶Ï';'
	if (c == ';')
		return 1;
	return 0;
}
bool islpar(int c) {		//ÅÐ¶Ï'('
	if (c == '(')
		return 1;
	return 0;
}
bool isrpar(int c) {		//ÅÐ¶Ï')'
	if (c == ')')
		return 1;
	return 0;
}
bool islbra(int c) {		//ÅÐ¶Ï'['
	if (c == '[')
		return 1;
	return 0;
}
bool isrbra(int c) {		//ÅÐ¶Ï']'
	if (c == ']')
		return 1;
	return 0;
}
bool islbpar(int c) {		//ÅÐ¶Ï'{'
	if (c == '{')
		return 1;
	return 0;
}
bool isrbpar(int c) {		//ÅÐ¶Ï'}'
	if (c == '}')
		return 1;
	return 0;
}
bool isless(int c) {		//ÅÐ¶Ï'<'
	if (c == '<')
		return 1;
	return 0;
}
bool ismore(int c) {		//ÅÐ¶Ï'>'
	if (c == '>')
		return 1;
	return 0;
}
bool isexc(int c) {		//ÅÐ¶Ï'!'
	if (c == '!')
		return 1;
	return 0;
}
bool isdquot(int c) {		//ÅÐ¶Ï'"'
	if (c == '\"')
		return 1;
	return 0;
}
bool isapo(int c) {		//ÅÐ¶Ï'''
	if (c == '\'')
		return 1;
	return 0;
}
int iskey() {   //ÅÐ¶ÏÊÇ·ñÎª±£Áô×Ö
	if (strcmp(token, KEYWORD[0]) == 0)
		return CONSY;
	else if (strcmp(token, KEYWORD[1]) == 0)
		return INTSY;
	else if (strcmp(token, KEYWORD[2]) == 0)
		return CHARSY;
	else if (strcmp(token, KEYWORD[3]) == 0)
		return VOIDSY;
	else if (strcmp(token, KEYWORD[4]) == 0)
		return MAINSY;
	else if (strcmp(token, KEYWORD[5]) == 0)
		return IFSY;
	else if (strcmp(token, KEYWORD[6]) == 0)
		return WHILESY;
	else if (strcmp(token, KEYWORD[7]) == 0)
		return SWITCHSY;
	else if (strcmp(token, KEYWORD[8]) == 0)
		return CASESY;
	else if (strcmp(token, KEYWORD[9]) == 0)
		return DEFAULTSY;
	else if (strcmp(token, KEYWORD[10]) == 0)
		return SCANFSY;
	else if (strcmp(token, KEYWORD[11]) == 0)
		return PRINTFSY;
	else if (strcmp(token, KEYWORD[12]) == 0)
		return RETURNSY;
	else
		return 13;
}
void get_char() {
	if (line_length == line_loc) {
		line_num++;
		if (fgets(line, 1024, compile_file) != NULL) {
			line_length = strlen(line);
			line_loc = 0;
			ch = '\n';
		}  
		else
			ch = -1;
	}
	else {
		ch = line[line_loc];
		line_loc++;
	}
}
int stringtonum() {
	int result = 0,i;
	for (i = 0; i < tok_loc; i++) {
		result = result * 10 + token[i] - '0';
	}
	return result;
}
int getsym() {
	int zero_iden = 0;   //ÅÐ¶ÏÊý×ÖÊ×Î»ÊÇ²»ÊÇ0
	memset(token, 0, sizeof(token));
	tok_loc = 0;
	while (ch == ' ' || ch == '\t' || ch == '\n') {
		get_char();
		if (ch == -1) {
			printf("lexical analysis completed!\n");
			fprintf(lexana_file, "lexical analysis completed!\n");
			return -2;
		}
	}
	if (ch == -1) {
		printf("lexical analysis completed!\n");
		fprintf(lexana_file, "lexical analysis completed!\n");
		return -2;
	}
	if (ischar(ch)) {
		while (ischar(ch)||isdigit(ch)) {
			token[tok_loc] = ch;
			tok_loc++;
			get_char();
		}
		sym = iskey();
		fprintf(lexana_file, "%d ", xh++);
		switch (sym) {
			case 0:fprintf(lexana_file, "CONSY %s\n", KEYWORD[sym]);break;
			case 1:fprintf(lexana_file, "INTSY %s\n", KEYWORD[sym]);break;
			case 2:fprintf(lexana_file, "CHARSY %s\n", KEYWORD[sym]); break;
			case 3:fprintf(lexana_file, "VOIDSY %s\n", KEYWORD[sym]); break;
			case 4:fprintf(lexana_file, "MAINSY %s\n", KEYWORD[sym]); break;
			case 5:fprintf(lexana_file, "IFSY %s\n", KEYWORD[sym]); break;
			case 6:fprintf(lexana_file, "WHILESY %s\n", KEYWORD[sym]); break;
			case 7:fprintf(lexana_file, "SWITCHSY %s\n", KEYWORD[sym]); break;
			case 8:fprintf(lexana_file, "CASESY %s\n", KEYWORD[sym]); break;
			case 9:fprintf(lexana_file, "DEFAULTSY %s\n", KEYWORD[sym]); break;
			case 10:fprintf(lexana_file, "SCANFSY %s\n", KEYWORD[sym]); break;
			case 11:fprintf(lexana_file, "PRINTFSY %s\n", KEYWORD[sym]); break;
			case 12:fprintf(lexana_file, "RETURNSY %s\n", KEYWORD[sym]); break;
			case 13:fprintf(lexana_file, "IDENSY %s\n", token); break;
		}
	}
	else if (isdigit(ch)) {
		if (iszero(ch)) {
			zero_iden = 1;
		}
		while (isdigit(ch)) {
			token[tok_loc] = ch;
			tok_loc++;
			get_char();
		}
		int result = stringtonum();
		if (zero_iden&&result) {
			error(ZERO_FIRST,line_num);
		}
		else {
			fprintf(lexana_file, "%d ", xh++);
			fprintf(lexana_file, "INT2SY %s\n", token);
		}
		sym = INT2SY;
	}
	else if (isplus(ch)) {
		fprintf(lexana_file, "%d PLUSSY +\n", xh++);
		get_char();
		sym = PLUSSY;
	}
	else if (isminus(ch)) {
		fprintf(lexana_file, "%d MINUSSY -\n", xh++);
		get_char();
		sym = MINUSSY;
	}
	else if (ismult(ch)) {
		fprintf(lexana_file, "%d MULTSY *\n", xh++);
		get_char();
		sym = MULTSY;
	}
	else if (isdiv(ch)) {
		fprintf(lexana_file, "%d DIVSY /\n", xh++);
		get_char();
		sym = DIVSY;
	}
	else if (isassign(ch)) {
		get_char();
		if (isassign(ch)) {
			fprintf(lexana_file, "%d EQSY ==\n", xh++);
			get_char();
			sym = EQSY;
		}
		else {
			fprintf(lexana_file, "%d ASSIGNSY =\n", xh++);
			sym = ASSIGNSY;
		}
	}
	else if (iscomma(ch)) {
		fprintf(lexana_file, "%d COMMASY ,\n", xh++);
		get_char();
		sym = COMMASY;
	}
	else if (iscolon(ch)) {
		fprintf(lexana_file, "%d COLONSY :\n", xh++);
		get_char();
		sym = COLONSY;
	}
	else if (issemi(ch)) {
		fprintf(lexana_file, "%d SEMISY ;\n", xh++);
		get_char();
		sym = SEMISY;
	}
	else if (islpar(ch)) {
		fprintf(lexana_file, "%d LPARSY (\n", xh++);
		get_char();
		sym = LPARSY;
	}
	else if (isrpar(ch)) {
		fprintf(lexana_file, "%d RPARSY )\n", xh++);
		get_char();
		sym = RPARSY;
	}
	else if (islbra(ch)) {
		fprintf(lexana_file, "%d LBRASY [\n", xh++);
		get_char();
		sym = LBRASY;
	}
	else if (isrbra(ch)) {
		fprintf(lexana_file, "%d RBRASY ]\n", xh++);
		get_char();
		sym = RBRASY;
	}
	else if (islbpar(ch)) {
		fprintf(lexana_file, "%d LBPARSY {\n", xh++);
		get_char();
		sym = LBPARSY;
	}
	else if (isrbpar(ch)) {
		fprintf(lexana_file, "%d RBPARSY }\n", xh++);
		get_char();
		sym = RBPARSY;
	}
	else if (isless(ch)) {
		get_char();
		if (isassign(ch)) {
			fprintf(lexana_file, "%d LEEQSY <=\n", xh++);
			get_char();
			sym = LEEQSY;
		}
		else {
			fprintf(lexana_file, "%d LESY <\n", xh++);
			sym = LESY;
		}
	}
	else if (ismore(ch)) {
		get_char();
		if (isassign(ch)) {
			fprintf(lexana_file, "%d MOEQSY >=\n", xh++);
			get_char();
			sym = MOEQSY;
		}
		else {
			fprintf(lexana_file, "%d MOSY >\n", xh++);
			sym = MOSY;
		}
	}
	else if (isexc(ch)) {
		get_char();
		if (isassign(ch)) {
			fprintf(lexana_file, "%d NEQSY !=\n", xh++);
			get_char();
			sym = NEQSY;
		}
		else {
			error(INVALID_CHAR,line_num);
			sym = -1;
		}
	}
	else if (isapo(ch)) {
		fprintf(lexana_file, "%d APOSY '\n", xh++);
		get_char();
		if (isplus(ch) || isminus(ch) || ismult(ch) || isdiv(ch) || isdigit(ch) || ischar(ch)) {
			ch1 = ch;
			fprintf(lexana_file, "%d CHAR2SY %c\n", xh++,ch);
			get_char();
		}
		else {
			get_char();
			error(INVALID_CHAR,line_num);
			sym = -1;
		}
		if (isapo(ch)) {
			fprintf(lexana_file, "%d APOSY \'\n", xh++);
			get_char();
			sym = CHAR2SY;
		}
		else {
			error(LESS_APO,line_num);
			sym = -1;
		}
	}
	else if (isdquot(ch)) {
		fprintf(lexana_file, "%d DQUOSY \"\n", xh++);
		get_char();
		while (isinasc(ch)) {
			token[tok_loc++] = ch;
			get_char();
		}
		if (isdquot(ch)) {
			get_char();
			fprintf(lexana_file, "%d CHAR2SY %s\n", xh++, token);
			fprintf(lexana_file, "%d DQUOSY \"\n", xh++, token);
			sym = STRINGSY;
		}
		else {
			error(LESS_DQUO,line_num);
			sym = -1;
		}
	}
	else {
		get_char();
		error(INVALID_CHAR_IN_FILE,line_num);
		sym = -1;
	}
	return sym;
}
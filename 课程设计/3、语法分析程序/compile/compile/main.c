#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lex_ana.h"
#include"gra_ana.h"
#include"error.h"
FILE *compile_file;   //源代码文档
FILE *lexana_file;		//词法分析输出文档
FILE *graana_file;		//语法分析输出文档
FILE *error_file;		//错误输出文档
int main() {
	char filename[100];
	printf("Please input the filename:");
	gets(filename);
	if ((compile_file = fopen(filename, "r")) == NULL) {
		error(CAN_NOT_OPEN_FILE,0);
		return 0;
	}
	lexana_file = fopen("lexical_analysis.txt", "w");
	graana_file = fopen("grammer_analysis.txt", "w");
	error_file = fopen("error.txt", "w");
	fgets(line, 1024, lexana_file);
	line_length = strlen(line);
	get_char();
	sym = getsym();
	program();
	fclose(compile_file);
	fclose(lexana_file);
	system("pause");
	return 0;
}
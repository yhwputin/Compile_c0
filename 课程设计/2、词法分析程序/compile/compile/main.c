#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lex_ana.h"
#include"error.h"
FILE *compile_file;   //源代码文档
FILE *lexana_file;		//词法分析输出文档
int main() {
	char filename[100];
	printf("Please input the filename:");
	gets(filename);
	if ((compile_file = fopen(filename, "r")) == NULL) {
		error(CAN_NOT_OPEN_FILE,0);
		return 0;
	}
	lexana_file = fopen("lexical_analysis.txt", "w");
	fgets(line, 1024, lexana_file);
	line_length = strlen(line);
	get_char();
	while (sym != -2) {   //-2表示读程序结束
		sym = getsym();
	}
	fclose(compile_file);
	fclose(lexana_file);
	system("pause");
	return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lex_ana.h"
#include"gra_ana.h"
#include"sym_tab.h"
#include"error.h"
#include"mid_code.h"
#include"mips.h"
FILE *compile_file;   //源代码文档
FILE *lexana_file;		//词法分析输出文档
FILE *graana_file;		//语法分析输出文档
FILE *error_file;		//错误输出文档
FILE *mid_code_file;		//四元式输出文件
FILE *mips_file;
int main() {
	char filename[100];
	printf("Please input the filename:");
	gets(filename);
	if ((compile_file = fopen(filename, "r")) == NULL) {
		error(CAN_NOT_OPEN_FILE,0);
		exit(-1);
		return 0;
	}
	else {
		lexana_file = fopen("lexical_analysis.txt", "w");
		graana_file = fopen("grammer_analysis.txt", "w");
		error_file = fopen("error.txt", "w");
		mid_code_file = fopen("mid_code_file.txt", "w");
		mips_file = fopen("mips_code.asm", "w");
		fgets(line, 1024, lexana_file);
		line_length = strlen(line);
		get_char();
		sym = getsym();
		init();
		program();
		print_mid_code();
		append_mips_code();
		print_stable();
		fclose(compile_file);
		fclose(lexana_file);
		fclose(graana_file);
		fclose(error_file);
		fclose(mid_code_file);
	}
	system("pause");
	return 0;
}
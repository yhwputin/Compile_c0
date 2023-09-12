#include<stdio.h>
#include<stdlib.h>
#include"mid_code.h"
#include"error.h"
#include"lex_ana.h"
#include"gra_ana.h"
int label_num;
int var_num;
int new_var_num;
extern FILE *mid_code_file;
void append_mid_code(int op, char src1[], char src2[], char result[]) {
	if (m_table.mid_num >= MAX_MID_CODE) {
		error(FULL_MID_TABLE,line_num);
		exit(0);
		return;
	}
	m_table.mid_list[m_table.mid_num].op = op;
	strcpy(m_table.mid_list[m_table.mid_num].src1, src1);
	strcpy(m_table.mid_list[m_table.mid_num].src2, src2);
	strcpy(m_table.mid_list[m_table.mid_num].result, result);
	m_table.mid_num++;
}
void print_mid_code() {
	int i;
	for (i = 0; i <m_table.mid_num; i++) {
		print_one_mid_code(i);
	}
	fclose(mid_code_file);
}
void print_one_mid_code(int number) {
	int i;
	i = m_table.mid_list[number].op;
	switch (i) {
		case 1: {
			fprintf( mid_code_file,  "const int %s = %s\n", m_table.mid_list[number].result, m_table.mid_list[number].src1);
			break;
		}
		case 2: {
			fprintf( mid_code_file,  "const char %s = %s\n", m_table.mid_list[number].result, m_table.mid_list[number].src1);
			break;
		}
		case 3: {
			fprintf( mid_code_file,  "var int %s\n", m_table.mid_list[number].result);
			break;
		}
		case 4: {
			fprintf( mid_code_file,  "var char %s\n", m_table.mid_list[number].result);
			break;
		}
		case 5: {
			fprintf( mid_code_file,  "array int %s[%s]\n", m_table.mid_list[number].result, m_table.mid_list[number].src1);
			break;
		}
		case 6: {
			fprintf( mid_code_file,  "array char %s[%s]\n", m_table.mid_list[number].result, m_table.mid_list[number].src1);
			break;
		}
		case 7: {
			fprintf( mid_code_file,  "func int %s\n", m_table.mid_list[number].result);
			break;
		}
		case 8: {
			fprintf( mid_code_file,  "func char %s\n", m_table.mid_list[number].result);
			break;
		}
		case 9: {
			fprintf( mid_code_file,  "func void %s\n", m_table.mid_list[number].result);
			break;
		}
		case 10: {
			fprintf( mid_code_file,  "para int %s\n", m_table.mid_list[number].result);
			break;
		}
		case 11: {
			fprintf( mid_code_file,  "para char %s\n", m_table.mid_list[number].result);
			break;
		}
		case 12: {
			fprintf( mid_code_file,  "%s = %s + %s\n", m_table.mid_list[number].result,m_table.mid_list[number].src1, m_table.mid_list[number].src2);
			break;
		}
		case 13: {
			fprintf( mid_code_file,  "%s = %s - %s\n", m_table.mid_list[number].result,m_table.mid_list[number].src1, m_table.mid_list[number].src2);
			break;
		}
		case 14: {
			fprintf( mid_code_file,  "%s = %s * %s\n", m_table.mid_list[number].result,m_table.mid_list[number].src1, m_table.mid_list[number].src2);
			break;
		}
		case 15: {
			fprintf( mid_code_file,  "%s = %s / %s\n", m_table.mid_list[number].result,m_table.mid_list[number].src1, m_table.mid_list[number].src2);
			break;
		}
		case 16: {
			fprintf( mid_code_file,  "%s = %s\n", m_table.mid_list[number].result, m_table.mid_list[number].src1);
			break;
		}
		case 17: {
			fprintf( mid_code_file,  "%s = %s[%s]\n", m_table.mid_list[number].result,m_table.mid_list[number].src1, m_table.mid_list[number].src2);
			break;
		}
		case 18: {
			fprintf( mid_code_file,  "%s[%s] = %s\n", m_table.mid_list[number].result,m_table.mid_list[number].src2, m_table.mid_list[number].src1);
			break;
		}
		case 19: {
			fprintf( mid_code_file,  "%s == %s\n", m_table.mid_list[number].src1, m_table.mid_list[number].src2);
			break;
		}
		case 20: {
			fprintf( mid_code_file,  "%s <= %s\n", m_table.mid_list[number].src1, m_table.mid_list[number].src2);
			break;
		}
		case 21: {
			fprintf( mid_code_file,  "%s >= %s\n", m_table.mid_list[number].src1, m_table.mid_list[number].src2);
			break;
		}
		case 22: {
			fprintf( mid_code_file,  "%s != %s\n", m_table.mid_list[number].src1, m_table.mid_list[number].src2);
			break;
		}
		case 23: {
			fprintf( mid_code_file,  "%s < %s\n", m_table.mid_list[number].src1, m_table.mid_list[number].src2);
			break;
		}
		case 24: {
			fprintf( mid_code_file,  "%s > %s\n", m_table.mid_list[number].src1, m_table.mid_list[number].src2);
			break;
		}
		case 25: {
			fprintf( mid_code_file,  "goto %s\n", m_table.mid_list[number].result);
			break;
		}
		case 26: {
			fprintf( mid_code_file,  "bnz %s\n", m_table.mid_list[number].result);
			break;
		}
		case 27: {
			fprintf( mid_code_file,  "bz %s\n", m_table.mid_list[number].result);
			break;
		}
		case 28: {
			fprintf( mid_code_file,  "push %s\n", m_table.mid_list[number].result);
			break;
		}
		case 29: {
			if (strcmp(m_table.mid_list[number].result, mid_empty) == 0) {
				fprintf( mid_code_file,  "call %s\n", m_table.mid_list[number].src1);
			}
			else {
				fprintf( mid_code_file,  "%s = call %s\n",  m_table.mid_list[number].result, m_table.mid_list[number].src1);
			}
			break;
		}
		case 30: {
			fprintf( mid_code_file,  "ret %s\n", m_table.mid_list[number].result);
			break;
		}
		case 31: {
			fprintf( mid_code_file,  "scan %s\n", m_table.mid_list[number].result);
			break;
		}
		case 32: {
			fprintf( mid_code_file,  "print %s\n", m_table.mid_list[number].result);
			break;
		}
		case 33: {
			fprintf( mid_code_file,  "%s:\n", m_table.mid_list[number].result);
			break;
		}
		case 34: {
			fprintf( mid_code_file,  "end func\n");
			break;
		}
		case 35: {
			fprintf( mid_code_file,  "end\n");
			break;
		}
	}
}
void append_label(char s[]) {
	sprintf(s, "LABEL%d", label_num);
	label_num++;
	return;
}

void append_var(char s[]) {
	sprintf(s, "$VAR%d", var_num);
	var_num++;

	return;
}

void append_string(char s[]) {
	sprintf(s, "STRING%d", new_var_num);
	new_var_num++;
	return;
}
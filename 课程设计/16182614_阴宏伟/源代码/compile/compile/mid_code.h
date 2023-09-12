#include<stdio.h>
#include<stdlib.h>
#define MAX_MID_CODE 2048
extern int label_num;
extern int var_num;
extern int new_var_num;
struct mid_code {
	int op;
	char src1[100];
	char src2[100];
	char result[100];
	int use;
};
struct mid_code_list {
	struct mid_code mid_list[MAX_MID_CODE];
	int mid_num;
};
struct mid_code_list m_table;
extern void append_mid_code(int op, char src1[], char src2[], char result[]);
extern void print_mid_code(FILE *mid_code_file);
extern void print_one_mid_code(int number, FILE * mid_code_file);
extern void append_label(char s[]);
extern void append_var(char s[]);
extern void append_string(char s[]);

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"gra_ana.h"
#include"lex_ana.h"
#include"error.h"
#include"sym_tab.h"
#include"mid_code.h"
#include"mips.h"
#include"optimizer.h"
extern FILE *mid_code_file;
void init() {
	array_flag = 0;               //标识符是不是数组
	var_flag = 0;
	const_flag = 0;
	para_flag = 0;
	addr = -1;
	stable.func_num = 0;
	stable.list_index = 0;
	memset(mid_empty, 0, sizeof(mid_empty));
	memset(mid_array, 0, sizeof(mid_array));
	memset(src1, 0, sizeof(src1));
	memset(src2, 0, sizeof(src2));
	memset(result, 0, sizeof(result));
	memset(f_token, 0, sizeof(f_token));
	memset(tep_result, 0, sizeof(tep_result));
	memset(mid_zero, 0, sizeof(mid_zero));
	memset(switch_label,0,sizeof(switch_label));
	memset(tep_func, 0, sizeof(tep_func));
	mid_zero[0] = '0';
	label_num = 0;
	var_num = 0;
	new_var_num = 0;
	init_opt();
}
void append_stable(char name[], int kind, int type, int value,int size, int address) {
	int i,func_i;
	if (stable.list_index >= TABLE_MAX-1) {
		error(FULL_TABLE, line_num);
		exit(0);
		return;
	}
	if (kind == 2) {
		for (i = 0; i < stable.func_num; i++) {
			func_i = stable.func_list[i];
			if (strcmp(stable.list[func_i].name, name) == 0) {
				error(DUP_FUNC_NAME, line_num);
				return;
			}
		}
		stable.func_list[stable.func_num] = stable.list_index;
		stable.func_num++;
	}
	else {
		if (stable.func_num == 0) {
			func_i = 0;
		}
		else {
			func_i = stable.func_list[stable.func_num - 1];
		}
		for (i = func_i; i < stable.list_index; i++) {
			if (strcmp(stable.list[i].name, name) == 0) {
				error(DUP_VAR_CONST_NAME, line_num);
				return;
			}
		}
	}
	strcpy(stable.list[stable.list_index].name, name);
	stable.list[stable.list_index].kind = kind;
	stable.list[stable.list_index].address = address;
	stable.list[stable.list_index].value = value;
	stable.list[stable.list_index].type = type;
	stable.list[stable.list_index].size = size;
	stable.list_index++;
}
int index_stable(char name[],int kind) {
	int i, func_i;
	array_flag = 0;
	var_flag = 0;
	const_flag = 0;
	para_flag = 0;
	if (kind == 2) {
		for (i = 0; i < stable.func_num; i++) {
			func_i = stable.func_list[i];
			if (strcmp(stable.list[func_i].name, name) == 0) {
				return stable.list[func_i].type;
			}
		}
		error(FUNC_NO_DEF, line_num);
		return -1;
	}
	else {
		for (func_i = stable.func_list[stable.func_num - 1]; func_i < stable.list_index; func_i++) {
			if (strcmp(stable.list[func_i].name, name) == 0) {                    
				break;
			}
		}
		if (func_i >= stable.list_index) {
			for (func_i = 0; func_i < stable.func_list[0]; func_i++) {
				if (strcmp(stable.list[func_i].name, name) == 0) {
					break;
				}
			}
			if (func_i == stable.func_list[0]) {
				error(ID_NO_DEF, line_num);
				return -1;
			}
			if (stable.list[func_i].kind == 0) {
				const_flag = 1;
				return stable.list[func_i].type;
			}
			else if (stable.list[func_i].kind == 1) {
				var_flag = 1;
				return stable.list[func_i].type;
			}
			else if (stable.list[func_i].kind == 4) {
				array_flag = 1;
				return stable.list[func_i].type;
			}
			else if (stable.list[func_i].kind == 3) {
				para_flag = 1;
				return stable.list[func_i].type;
			}
		}
		else {
			if (stable.list[func_i].kind == 0) {
				const_flag = 1;
				return stable.list[func_i].type;
			}
			else if (stable.list[func_i].kind == 1) {
				var_flag = 1;
				return stable.list[func_i].type;
			}
			else if (stable.list[func_i].kind == 4) {
				array_flag = 1;
				return stable.list[func_i].type;
			}
			else if (stable.list[func_i].kind == 3) {
				para_flag = 1;
				return stable.list[func_i].type;
			}
		}
	}
	return 0;
}
int get_const_value(char name[]) {
	int i,func_i;
	for (i = stable.func_list[stable.func_num - 1]; i < stable.list_index; i++) {
		if (strcmp(stable.list[i].name, name) == 0) {
			break;
		}
	}
	if (i >= stable.list_index) {
		func_i = stable.func_list[0];
		for (i = 0; i < func_i; i++) {
			if (strcmp(stable.list[i].name, name) == 0) {
				break;
			}
		}
		if (i == func_i) {
			error(ID_NO_DEF, line_num);
			return -1;
		}
		else {
			return stable.list[i].value;
		}
	}
	else {
		return stable.list[i].value;
	}
}
int get_func_para_num(char name[]) {
	int func_i;
	for (func_i = 0; func_i < stable.func_num; func_i++) {
		if (strcmp(stable.list[stable.func_list[func_i]].name, name) == 0) {
			return stable.list[stable.func_list[func_i]].size;
		}
	}
	if (func_i == stable.func_num) {
		error(FUNC_NO_DEF, line_num);
		return -1;
	}
	return 0;
}
int get_func_type(char name[]) {
	int func_i;
	for (func_i = 0; func_i < stable.func_num; func_i++) {
		if (strcmp(stable.list[stable.func_list[func_i]].name, name) == 0) {
			return stable.list[stable.func_list[func_i]].type;
		}
	}
	if (func_i == stable.func_num) {
		error(FUNC_NO_DEF, line_num);
		return -1;
	}
	return 0;
}
int get_array_size(char name[]) {
	int i, func_i;
	for (i = stable.func_list[stable.func_num - 1]; i < stable.list_index; i++) {
		if (strcmp(stable.list[i].name, name) == 0) {
			break;
		}
	}
	if (i >= stable.list_index) {
		func_i = stable.func_list[0];
		for (i = 0; i < func_i; i++) {
			if (strcmp(stable.list[i].name, name) == 0) {
				break;
			}
		}
		if (i == func_i) {
			error(ID_NO_DEF, line_num);
			return -1;
		}
		else {
			return stable.list[i].size;
		}
	}
	else {
		return stable.list[i].size;
	}
}
void print_stable() {
	int i;
	for (i = 0; i < stable2.list_index; i++) {
		printf("%20s ", stable2.list[i].name);
		printf("%3d ", stable2.list[i].kind);
		printf("%3d ", stable2.list[i].type);
		printf("%3d ", stable2.list[i].value);
		printf("%3d ", stable2.list[i].size);
		printf("%3d \n", stable2.list[i].address);
		
	}
}
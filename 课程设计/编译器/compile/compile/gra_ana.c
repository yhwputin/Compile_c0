#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"gra_ana.h"
#include"lex_ana.h"
#include"error.h"
#include"sym_tab.h"
#include"mid_code.h"
int func_size;
int main_flag = 0;
int max_var_num = 0;
int cond_flag = 0;
int array_flag;
int var_flag;
int const_flag;
int para_flag;
int global_flag;
int addr = -1;
char mid_int[100] = "INT";
char mid_char[100] = "CHAR";
char mid_str[100] = "STRING";
char mid_flag1[100] = "FLAG1";
char mid_flag2[100] = "FLAG2";
char mid_array[100];
char mid_empty[100];
char mid_zero[100];
char switch_label[100];
char result[100],tep_result[100];
char src1[100], src2[100];
extern FILE *graana_file;
char f_token[100];
int factor_type = 0;
int f_sym;
int f_ch;
int func_type;
int sign;
int type_flag;
int return_flag = 0;
char name_id[100];
int f_line_loc;
void program();
void con_dec();
void con_def();
void statement();
void def_head();
void var_dec();
void var_def();
void val_fun_def();
void void_fun_def();
void com_sta();
void sta_list();
void para_list();
void para();
void main_func();
void expr();
void term();
void factor();
void assign_sta();
void if_sta();
void condition();
void while_sta();
void switch_sta();
void case_list(char name[], char name2[]);
void case_sub_sta(char name[], char name2[]);
void default_sta(char name[]);
void val_fun_call(int val_flag);
void void_fun_call();
void val_para_list(char name[]);
void scanf_sta();
void printf_sta();
void return_sta();
int int_judge();
void return_sta() {
	int type;
	type = stable.list[stable.func_list[stable.func_num - 1]].type;
	sym = getsym();
	if (sym == LPARSY) {
		if (type == 0) {
			error(VOID_RT_ERROR, line_num);
			do{
				sym = getsym();
			} while (sym != SEMISY);
		}
		sym = getsym();
		expr();
		if (factor_type != func_type) {
			error(RETURN_ERROR, line_num);
			do {
				sym = getsym();
			} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
			return;
		}
		if (sym == RPARSY) {
			sym = getsym();
			return_flag = 1;
			append_mid_code(30, mid_empty, mid_empty, tep_result);
			fprintf(graana_file,"This is a return statement!\n");
			return;
		}
		else {
			error(LESS_RPARSY, line_num);
			 do{
				 sym = getsym();
			 } while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
			return;
		}
	}
	else{
		if (type != 0) {
			error(VAL_RT_ERROR, line_num);
			do {
				sym = getsym();
			} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
		}
		if(main_flag==1)
			append_mid_code(35, mid_empty, mid_empty, mid_empty);
		else
			append_mid_code(30, mid_empty, mid_empty, mid_empty);
		fprintf(graana_file,"This is a return statement!\n");
		return;
	}
	fprintf(graana_file,"This is a return statement!\n");
}
void printf_sta() {
	sym = getsym();
	if (sym == LPARSY) {
		sym = getsym();
		if (sym == STRINGSY) {
			append_mid_code(32, mid_str, mid_empty, token);
			sym = getsym();
			if (sym == COMMASY) {
				sym = getsym();
				expr();
				if(factor_type==1)
					append_mid_code(32, mid_int, mid_empty, tep_result);
				else if (factor_type == 2)
					append_mid_code(32, mid_char, mid_empty, tep_result);
			}
		}
		else {
			expr(); 
			if (factor_type == 1)
				append_mid_code(32, mid_int, mid_empty, tep_result);
			else if (factor_type == 2)
				append_mid_code(32, mid_char, mid_empty, tep_result);
		}
		if (sym == RPARSY) {
			sym = getsym();
			fprintf(graana_file,"This is a print statement!\n");
			return;
		}
		else {
			error(LESS_RPARSY, line_num);
			  do{
				  sym = getsym();
			  } while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
			  return;
		}
	}
	else {
		error(LESS_LPARSY, line_num);
		  do{
			  sym = getsym();
		  } while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
		return;
	}
	fprintf(graana_file,"This is a print statement!\n");
}
void scanf_sta() {
	int index;
	char name[100];
	sym = getsym();
	if (sym == LPARSY) {
		sym = getsym();
		 do{
			if(sym == COMMASY) {
				sym = getsym();
			}
			if (sym == IDENSY) {
				strcpy(name, token);
				sym = getsym();
				index = index_stable(name, 0);
				if (var_flag == 0) {
					error(READ_ERROR, line_num);
					do{
						sym = getsym();
					} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
					return;
				}
				if (index == 1)
					append_mid_code(31, mid_int, mid_empty, name);
				else if (index == 2)
					append_mid_code(31, mid_char, mid_empty, name);
			}
			else {
				 error(LESS_IDEN, line_num);
				 do{
					 sym = getsym();
				 } while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
				return;
			}
		} while (sym==COMMASY);
		if (sym == RPARSY) {
			sym = getsym();
			fprintf(graana_file,"This is a scan statement!\n");
			return;
		}
		else {
			 error(LESS_RPARSY, line_num);
			 do{
				 sym = getsym();
			 } while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
			return;
		}
	}
	else {
		error(LESS_LPARSY, line_num);
		 do{
			 sym = getsym();
		 } while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
		return;
	}
	fprintf(graana_file,"This is a scan statement!\n");
}
void val_para_list(char name[]) {
	 int para_num = 0;
	 int i,j;
	 int f_size;
	 f_size = func_size;
	 for (i = 0; i < stable.func_num; i++) {
		 if (strcmp(stable.list[stable.func_list[i]].name, name) == 0)
			 break;
	 }
	 j = stable.func_list[i];
	 do{
		 j++;
		 if (sym == RPARSY) {
			break;
		 }
		 if (sym == COMMASY) {
			sym = getsym();
		 }
		 if (sym == IDENSY || sym == CHAR2SY || sym==PLUSSY ||sym==MINUSSY ||sym==INT2SY || sym == LPARSY) {
			expr();
			if (factor_type != stable.list[j].type) {
				error(PARA_TYPE_ERROR, line_num);
				do {
					sym = getsym();
				} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
				return;
			}
			append_mid_code(28, mid_empty, mid_empty, tep_result);
			para_num++;
		 }
		 else {
			error(VAL_FUNC_LIST_ERROR, line_num);
			do{
				sym = getsym();
			} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
			return;
		 }
	 } while (sym == COMMASY);
	 if (para_num != f_size) {
		error(PARA_NUM_INVALID, line_num);
		return;
	 }
}
void void_fun_call() {
	char func_name[100];
	if (sym == IDENSY) {
		strcpy(func_name, token);
		func_size = get_func_para_num(token);
		sym = getsym();
		if (sym == LPARSY) {
			sym = getsym();
			val_para_list(func_name);
			if (sym == RPARSY) {
				append_mid_code(29, func_name, mid_empty, mid_empty);
				sym = getsym();
				fprintf(graana_file,"This is a void function call!\n");
				return;
			}
			else {
				  error(LESS_RPARSY, line_num);
				  do{
					  sym = getsym();
				  } while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
			     return;
			}
		}
		else {
			error(LESS_LPARSY, line_num);
			 do{
				 sym = getsym();
			 }while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
			return;
		}
	}
	else {
		error(LESS_IDEN, line_num);
		do{
			sym = getsym();
		}while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
		return;
	}
	fprintf(graana_file,"This is a void function call!\n");
}
void val_fun_call(int val_flag) {
	char func_name[100];
	int type;
	int t_type = factor_type;
	if (sym == IDENSY) {
		strcpy(func_name, token);
		func_size = get_func_para_num(token);
		type = get_func_type(token);
		sym = getsym();
		if (sym == LPARSY) {
			sym = getsym();
			val_para_list(func_name);
			factor_type = t_type;
			if (sym == RPARSY) {
				if (val_flag == 1) {
					append_var(tep_result);
					append_mid_code(29, func_name, mid_empty, tep_result);
					if (factor_type == 0) {
						factor_type = type;
					}
				}
				else {
					append_mid_code(29, func_name, mid_empty, mid_empty);
				}
				sym = getsym();
				fprintf(graana_file,"This is a value function call!\n");
				return;
			}
			else {
				error(LESS_RPARSY, line_num);
				do{
					sym = getsym();
				}while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
				return;
			}
		}
		else {
			error(LESS_LPARSY, line_num);
			do{
				sym = getsym();
			}while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
			return;
		}
	}
	else {
		error(LESS_IDEN, line_num);
		do {
			sym = getsym();
		} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
		return;
	}
	fprintf(graana_file,"This is a value function call!\n");
}
void default_sta(char name[]) {
	if (sym == DEFAULTSY) {
		sym = getsym();
		if (sym == COLONSY) {
			sym = getsym();
			if (sym == RBPARSY) {
				fprintf(graana_file,"This is a default!\n");
				return;
			}
			else {
				statement();
				append_mid_code(25, mid_empty, mid_empty, name);
			}
		}
		else {
			error(LESS_COLON, line_num);
			do {
				sym = getsym();
			} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
			return;
		}
	}
	else {
		return;
	}
	fprintf(graana_file,"This is a default!\n");
}
void case_sub_sta(char name[],char name2[]) {
	char label_n[100];
	append_label(label_n);
	if (sym == CASESY) {
		sym = getsym();
		if (sym == CHAR2SY) {
			sprintf(src2, "%d", ch1);
			append_mid_code(19, name, src2, mid_empty);
			append_mid_code(27, mid_empty, mid_empty, label_n);
		}
		else if (sym == PLUSSY || sym == MINUSSY) {
			if (sym == PLUSSY) {
				sign = 1;
			}
			else {
				sign = -1;
			}
			sym = getsym();
			if (sym == INT2SY) {
				cal_num *= sign;
				sprintf(src2, "%d", cal_num);
				append_mid_code(19, name, src2, mid_empty);
				append_mid_code(27, mid_empty, mid_empty, label_n);
			}
			else {
				error(INVALID_INT, line_num);
				do {
					sym = getsym();
				} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
				return;
			}
		}
		else if (sym == INT2SY) {
			sprintf(src2, "%d", cal_num);
			append_mid_code(19, name, src2, mid_empty);
			append_mid_code(27, mid_empty, mid_empty, label_n);
		}
		else {
			error(CONST_DEF_VALUE_ERROR, line_num);
			do {
				sym = getsym();
			} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
			return;
		}
		sym = getsym();
		if (sym == COLONSY) {
			sym = getsym();
			statement();
			append_mid_code(25, mid_empty, mid_empty, name2);
			append_mid_code(33, mid_empty, mid_empty, label_n);
		}
		else {
			error(LESS_COLON, line_num);
			do {
				sym = getsym();
			} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
			return;
		}
	}
	else {
		error(CASE_ERROR, line_num);
		do {
			sym = getsym();
		} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
		return;
	}
}
void case_list(char name[],char name2[]) {
	 do{
		case_sub_sta(name,name2);
	} while (sym == CASESY);
}
void switch_sta() {
	char s_label[100];
	char switch_src[100];
	append_label(switch_label);
	strcpy(s_label, switch_label);
	sym = getsym();
	if (sym == LPARSY) {
		sym = getsym();
		expr();
		strcpy(switch_src, tep_result);
		if (sym == RPARSY) {
			sym = getsym();
			if (sym == LBPARSY) {
				sym = getsym();
				case_list(switch_src,s_label);
				default_sta(s_label);
				if (sym == RBPARSY) {
					sym = getsym();
					append_mid_code(33, mid_empty, mid_empty, s_label);
					fprintf(graana_file,"This is a switch statement!\n");
					return;
				}
				else {
					error(LESS_RBRASY, line_num);
					do {
						sym = getsym();
					} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
					return;
				}
			}
			else {
				error(LESS_LPARSY, line_num);
				do {
					sym = getsym();
				} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
				return;
			}
		}
		else {
			error(LESS_RPARSY, line_num);
			do {
				sym = getsym();
			} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
			return;
		}
	}
	else {
		error(LESS_LPARSY, line_num);
		do {
			sym = getsym();
		} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
		return;
	}
	fprintf(graana_file,"This is a switch statement!\n");
}
void while_sta() {
	char label_1[100], label_2[100];
	append_label(label_1);
	append_mid_code(33, mid_empty, mid_empty, label_1);
	sym = getsym();
	if (sym == LPARSY) {
		sym = getsym();
		condition();
		append_label(label_2);
		append_mid_code(27, mid_empty, mid_empty, label_2);
		if (sym == RPARSY) {
			sym = getsym();
			statement();
			append_mid_code(25, mid_empty, mid_empty, label_1);
			append_mid_code(33, mid_empty, mid_empty, label_2);
		}
		else {
			error(LESS_RPARSY, line_num);
			do {
				sym = getsym();
			} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
			return;
		}
	}
	else {
		error(LESS_LPARSY, line_num);
		do {
			sym = getsym();
		} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
		return;
	}
	fprintf(graana_file,"This is a loop statement!\n");
}
void condition() {
	int t_sym;
	int l_type, r_type;
	cond_flag = 1;
	expr();
	l_type = factor_type;
	strcpy(src1, tep_result);
	if (sym == EQSY || sym == NEQSY || sym == LEEQSY || sym == LESY || sym == MOEQSY || sym == MOSY) {
		t_sym = sym;
		sym = getsym();
		cond_flag = 2;
		expr();
		cond_flag = 0;
		r_type = factor_type;
		if (!((l_type == r_type)&&l_type==1)) {
			error(EXP_TYPE_NOT_EQU, line_num);
			return;
		}
		strcpy(src2, tep_result);
		if (t_sym == EQSY) {
			append_mid_code(19, src1, src2, mid_empty);
		}
		else if (t_sym == LEEQSY) {
			append_mid_code(20, src1, src2, mid_empty);
		}
		else if (t_sym == MOEQSY) {
			append_mid_code(21, src1, src2, mid_empty);
		}
		else if (t_sym == NEQSY) {
			append_mid_code(22, src1, src2, mid_empty);
		}
		else if (t_sym == LESY) {
			append_mid_code(23, src1, src2, mid_empty);
		}
		else {
			append_mid_code(24, src1, src2, mid_empty);
		}
	}
	else if(sym==RPARSY){
		if (l_type != 1) {
			error(EXP_TYPE_NOT_EQU, line_num);
			return;
		}
		append_mid_code(22, src1, mid_zero, mid_empty);
	}
	else {
		error(INVALID_RELA, line_num);
		do {
			sym = getsym();
		} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
		return;
	}
	fprintf(graana_file,"This is a condition!\n");
}
void if_sta() {
	char label[100];
	append_label(label);
	sym = getsym();
	if (sym == LPARSY) {
		sym = getsym();
		condition();
		append_mid_code(27, mid_empty, mid_empty, label);
		if (sym == RPARSY) {
			sym = getsym();
			statement();
			append_mid_code(33, mid_empty, mid_empty, label);
		}
		else {
			error(LESS_RPARSY,line_num);
			do {
				sym = getsym();
			} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
			return;
		}
	}
	else {
		error(LESS_LPARSY,line_num);
		do {
			sym = getsym();
		} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
		return;
	}
	fprintf(graana_file,"This is a condition statement!\n");
}
void assign_sta() {
	int assign_type;
	char result_1[100];
	strcpy(result_1, token);
	sym = getsym();
	if (sym == ASSIGNSY) {
		sym = getsym();
		expr();
		assign_type = index_stable(result_1, 0);
		if (array_flag == 1) {
			error(ARRAY_ASSIGN, line_num);
			do {
				sym = getsym();
			} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
			return;
		}
		if (const_flag == 1) {
			error(CONST_ASSIGN, line_num);
			do {
				sym = getsym();
			} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
			return;
		}
		if (assign_type == 2 && factor_type == 1) {
			error(CHAR_ASSIGN, line_num);
			do {
				sym = getsym();
			} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
			return;
		}
		strcpy(src1, tep_result);
		append_mid_code(16, src1, mid_empty, result_1);
	}
	else if (sym == LBRASY) {
		assign_type = index_stable(result_1, 0);
		if (array_flag == 0) {
			error(ID_NO_DEF, line_num);
			do {
				sym = getsym();
			} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
			return;
		}
		sym = getsym();
		expr();
		if (sym == RBRASY) {
			strcpy(src2, tep_result);
			sym = getsym();
			if (sym = ASSIGNSY) {
				sym = getsym();
				expr();
				strcpy(src1, tep_result);
				append_mid_code(18, src1, src2, result_1);
			}
			else {
				error(LESS_ASSIGN, line_num);
				do {
					sym = getsym();
				} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
				return;
			}
		}
		else {
			error(LESS_RBRASY, line_num);
			do {
				sym = getsym();
			} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
			return;
		}
	}
	else {
		error(ASSIGN_ERROR, line_num);
		do {
			sym = getsym();
		} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
		return;
	}
	fprintf(graana_file,"This is an assign statement!\n");
}
void factor() {
	int type;
	int t_i;
	int t_t = 0;
	int tep_type;
	int c_flag = 0;
	char tep_token[100];
	if (sym == PLUSSY || sym == MINUSSY) {
		if (sym == PLUSSY) {
			sign = 1;
		}
		else {
			sign = -1;
		}
		sym = getsym();
		if (sym == INT2SY) {
			cal_num *= sign;
			sprintf(tep_result, "%d", cal_num);
			factor_type = 1;
			sym = getsym();
			fprintf(graana_file,"This is a factor!\n");
			return;
		}
		else {
			error(INVALID_INT, line_num);
			do {
				sym = getsym();
			} while (sym != SEMISY && sym != ASSIGNSY && sym != PLUSSY && sym != MINUSSY && sym != MULTSY && sym != DIVSY && sym != RPARSY && sym != COMMASY && sym != LEEQSY && sym != LESY && sym != MOSY && sym != MOEQSY && sym != EQSY && sym != NEQSY);
			return;
		}
	}
	else if (sym == INT2SY) {
		sprintf(tep_result, "%d", cal_num);
		factor_type = 1;
		sym = getsym();
		fprintf(graana_file,"This is a factor!\n");
		return;
	}
	else if (sym == CHAR2SY) {
		if(factor_type==0)
			factor_type = 2;
		sprintf(tep_result, "%d", ch1);
		sym = getsym();
		fprintf(graana_file,"This is a factor!\n");
		return;
	}
	else if (sym == LPARSY) {
		sym = getsym();
		expr();
		if (sym == RPARSY) {
			sym = getsym();
			factor_type = 1;
			fprintf(graana_file,"This is a factor!\n");
			return;
		}
		else {
			error(LESS_RPARSY, line_num);
			do {
				sym = getsym();
			} while (sym != SEMISY && sym != ASSIGNSY && sym != PLUSSY && sym != MINUSSY && sym != MULTSY && sym != DIVSY && sym != RPARSY && sym != COMMASY && sym != LEEQSY && sym != LESY && sym != MOSY && sym != MOEQSY && sym != EQSY && sym != NEQSY);
			return;
		}
	}
	else if (sym == IDENSY) {
		f_sym = sym;
		f_line_loc = line_loc;
		f_ch = ch;
		strcpy(f_token, token);
		sym = getsym();
		if (sym == LBRASY) {
			strcpy(tep_token, f_token);
			sym = getsym();
			tep_type = factor_type;
			if (sym == INT2SY) {
				f_sym = sym;
				f_line_loc = line_loc;
				f_ch = ch;
				strcpy(f_token, token);
				sym = getsym();
				if (sym == RBRASY) {
					t_i = cal_num;
					t_t = 1;
					sprintf(tep_result, "%d", cal_num);
				}
				else {
					sym = f_sym;
					line_loc = f_line_loc;
					ch = f_ch;
					strcpy(token, f_token);
					expr();
				}
			}
			else if (sym == IDENSY) {
				f_sym = sym;
				f_line_loc = line_loc;
				f_ch = ch;
				strcpy(f_token, token);
				type = index_stable(token, 0);
				c_flag = const_flag;
				if (c_flag != 0) {
					sym = f_sym;
					line_loc = f_line_loc;
					ch = f_ch;
					strcpy(token, f_token);
					expr();
				}
				if (index_stable(token, 0) != 1) {
					error(CONST_DEF_ERROR, line_num);
					do {
						sym = getsym();
					} while (sym != SEMISY && sym != ASSIGNSY && sym != PLUSSY && sym != MINUSSY && sym != MULTSY && sym != DIVSY && sym != RPARSY && sym != COMMASY && sym != LEEQSY && sym != LESY && sym != MOSY && sym != MOEQSY && sym != EQSY && sym != NEQSY);
					return;
				}
				sym = getsym();
				if (sym == RBRASY&&c_flag) {
					t_i = get_const_value(f_token);
					t_t = 1;
					sprintf(tep_result, "%d", t_i);
				}
				else {
					sym = f_sym;
					line_loc = f_line_loc;
					ch = f_ch;
					strcpy(token, f_token);
					expr();
				}
			}
			else 
				expr();
			if (sym == RBRASY) {
				type = index_stable(tep_token, 0);
				if (array_flag == 0) {
					error(ID_NO_DEF, line_num);
					do {
						sym = getsym();
					} while (sym != SEMISY && sym != ASSIGNSY && sym != PLUSSY && sym != MINUSSY && sym != MULTSY && sym != DIVSY && sym != RPARSY && sym != COMMASY && sym != LEEQSY && sym != LESY && sym != MOSY && sym != MOEQSY && sym != EQSY && sym != NEQSY);
					return;
				}
				if (t_t == 1) {
					if (get_array_size(tep_token) <= t_i || t_i < 0) {
						error(INVALID_INT, line_num);
						do {
							sym = getsym();
						} while (sym != SEMISY && sym != ASSIGNSY && sym != PLUSSY && sym != MINUSSY && sym != MULTSY && sym != DIVSY && sym != RPARSY && sym != COMMASY && sym != LEEQSY && sym != LESY && sym != MOSY && sym != MOEQSY && sym != EQSY && sym != NEQSY);
						return;
					}
				}
				factor_type = tep_type;
				if (factor_type == 0) {
					factor_type = type;
				}
				strcpy(result, tep_result);
				append_var(tep_result);
				append_mid_code(17,tep_token ,result , tep_result);
				sym = getsym();
				fprintf(graana_file,"This is a factor!\n");
				return;
			}
			else {
				error(LESS_RBRA, line_num);
				do {
					sym = getsym();
				} while (sym != SEMISY && sym != ASSIGNSY && sym != PLUSSY && sym != MINUSSY && sym != MULTSY && sym != DIVSY && sym != RPARSY && sym != COMMASY && sym != LEEQSY && sym != LESY && sym != MOSY && sym != MOEQSY && sym != EQSY && sym != NEQSY);
				return;
			}
		}
		else if (sym == LPARSY) {
			sym = f_sym;
			line_loc = f_line_loc;
			ch = f_ch;
			strcpy(token, f_token);
			val_fun_call(1);
			fprintf(graana_file,"This is a factor!\n");
			return;
		}
		else
		{
			type = index_stable(f_token, 0);
			if (array_flag == 1) {
				error(INVALID_EXPRESSION, line_num);
				do {
					sym = getsym();
				} while (sym != SEMISY && sym != ASSIGNSY && sym != PLUSSY && sym != MINUSSY && sym != MULTSY && sym != DIVSY && sym != RPARSY && sym != COMMASY && sym != LEEQSY && sym != LESY && sym != MOSY && sym != MOEQSY && sym != EQSY && sym != NEQSY);
				return;
			}
			if (factor_type == 0) {
				factor_type = type;
			}
			if (const_flag == 1) {
				type = get_const_value(f_token);
				sprintf(tep_result, "%d", type);
				const_flag = 0;
			}
			else {
				append_var(tep_result);
				append_mid_code(16, f_token, mid_empty, tep_result);
			}
			fprintf(graana_file,"This is a factor!\n");
			return;
		}
	}
	else {
		error(FACTOR_ERROR, line_num);
		do {
			sym = getsym();
		} while (sym != SEMISY && sym != ASSIGNSY && sym != PLUSSY && sym != MINUSSY && sym != MULTSY && sym != DIVSY && sym != RPARSY && sym != COMMASY && sym != LEEQSY && sym != LESY && sym != MOSY && sym != MOEQSY && sym != EQSY && sym != NEQSY);
		return;
	}
}
void term() {
	char result_1[100];
	char result_2[100];
	char result_l[100];
	factor();
	strcpy(result_l, tep_result);
	while (sym == MULTSY || sym == DIVSY) {
		strcpy(result_1, result_l);
		if (sym == MULTSY) {
			sym = getsym();
			factor();
			strcpy(result_2, tep_result);
			append_var(result_l);
			append_mid_code(14, result_1, result_2, result_l);
		}
		else {
			sym = getsym();
			factor();
			strcpy(result_2, tep_result);
			if (strcmp(result_2, mid_zero) == 0) {
				error(DIV_ZERO, line_num);
			}
			append_var(result_l);
			append_mid_code(15, result_1, result_2, result_l);
		}
	}
	strcpy(tep_result, result_l);
}
void expr() {
	char result_1[100];
	char result_2[100];
	char result_l[100];
	int sign_l;
	factor_type = 0;
	if (sym == PLUSSY || sym == MINUSSY) {
		factor_type = 1;
		if (sym == PLUSSY) {
			sign_l = 1;
		}
		else {
			sign_l = -1;
		}
		sym = getsym();
		term();
		if (sign_l == 1) {
			strcpy(result_l, tep_result);
		}
		else {
			append_var(result_l);
			append_mid_code(13, mid_zero, tep_result, result_l);
		}

	}
	else {
		term();
		strcpy(result_l, tep_result);
	}
	while (sym == PLUSSY || sym == MINUSSY) {
		factor_type = 1;
		if (sym == PLUSSY) {
			sign_l = 1;
		}
		else {
			sign_l = -1;
		}
		strcpy(result_1, result_l);
		sym = getsym();
		term();
		append_var(result_l);
		strcpy(result_2, tep_result);
		if (sign_l == 1) {
			append_mid_code(12, result_1, result_2, result_l);
		}
		else {
			append_mid_code(13, result_1, result_2, result_l);
		}
	}
	strcpy(tep_result, result_l);
	fprintf(graana_file, "This is an expression!\n");
}
void main_func() {
	sym = getsym();
	if (sym == MAINSY) {
		addr = -1;
		addr++;
		main_flag = 1;
		append_stable(token, 2, 0, 0, 0, addr);
		append_mid_code(9, mid_empty, mid_empty, token);
		sym = getsym();
		if (sym == LPARSY) {
			sym = getsym();
			if (sym == RPARSY) {
				sym = getsym();
				if (sym == LBPARSY) {
					sym = getsym();
					com_sta();
					if (sym != RBPARSY) {
						error(LESS_RBRASY,line_num);
						return;
					}
					else {
						append_mid_code(35, mid_empty, mid_empty, mid_empty);
					}
				}
				else {
					error(LESS_LBRASY, line_num);
					return;
				}
			}
			else {
				error(LESS_RPARSY, line_num);
				return;
			}
		}
		else {
			error(LESS_LPARSY, line_num);
			return;
		}
	}
	else {
		error(MAIN_ERROR,line_num);
		return;
	}
	fprintf(graana_file,"This is a main function!\n");
}
void para() {
	sym = getsym();
	if (sym != IDENSY) {
		error(LESS_IDEN, line_num);
		do{
			sym = getsym();
		} while (sym != RPARSY);
		return;
	}
	else {
		addr++;
		append_stable(token, 3,sign,0,-1,addr);
		append_mid_code(9 + sign, mid_empty, mid_empty, token);
		sym = getsym();
	}
}
void para_list() {
	 do{
		if (sym == COMMASY) {
			sym = getsym();
		}
		if (sym == INTSY || sym == CHARSY) {
			if (sym == INTSY) {
				sign = 1;
			}
			else {
				sign = 2;
			}
			para();
		}
		else if(sym==RPARSY){
			return;
		}
		else {
			error(PARA_LIST_ERROR, line_num);
			do{
				sym = getsym();
			} while (sym != RPARSY);
			break;
		}
		stable.list[stable.func_list[stable.func_num - 1]].size++;
	} while (sym == COMMASY);
}
void sta_list() {
	while (sym == IFSY || sym == WHILESY || sym == SWITCHSY || sym == SCANFSY || sym == PRINTFSY || sym == RETURNSY || sym == LBPARSY || sym == SEMISY || sym == RETURNSY||sym==IDENSY) {
		statement();
	}
	fprintf(graana_file,"This is a statement list!\n");
}
void com_sta() {
	if (sym == CONSY) {
		con_dec();
	}
	if (sym == INTSY || sym == CHARSY) {
		var_dec();
	}
	sta_list();
	fprintf(graana_file,"This is a complex statement!\n");
}
void void_fun_def() {
	sym = getsym();
	if (sym == IDENSY) {
		addr = -1;
		addr++;
		append_stable(token, 2, 0, 0, 0, addr);
		append_mid_code(9, mid_empty, mid_empty, token);
		sym = getsym();
		if (sym == LPARSY) {
			sym = getsym();
			para_list();
			if (sym == RPARSY) {
				sym = getsym();
				if (sym == LBPARSY) {
					sym = getsym();
					com_sta();
					if (sym != RBPARSY) {
						error(LESS_RBRASY, line_num);
						do{
							sym = getsym();
						} while (sym != VOIDSY && sym != INTSY && sym != CHARSY);
						return;
					}
					else {
						append_mid_code(30, mid_empty, mid_empty, mid_empty);
						append_mid_code(34, mid_empty, mid_empty, mid_empty);
						sym = getsym();
						fprintf(graana_file, "This is a void function defination!\n");
						return;
					}
				}
				else {
					error(LESS_LBRASY, line_num);
					do {
						sym = getsym();
					} while (sym != VOIDSY && sym != INTSY && sym != CHARSY);
					return;
				}
			}
			else {
				error(LESS_RPARSY, line_num);
				do {
					sym = getsym();
				} while (sym != VOIDSY && sym != INTSY && sym != CHARSY);
				return;
			}
		}
	}
	else {
		error(LESS_IDEN, line_num);
		do {
			sym = getsym();
		} while (sym != VOIDSY && sym != INTSY && sym != CHARSY);
		return;
	}
	fprintf(graana_file,"This is a void function defination!\n");
}
void val_fun_def() {     //要有返回值
	def_head();
	if (sym == LPARSY) {
		if (type_flag == 0) {
			func_type = 1;
			append_mid_code(7, mid_empty, mid_empty, name_id);
		}
		else {
			func_type = 2;
			append_mid_code(8, mid_empty, mid_empty, name_id);
		}
		sym = getsym();
		para_list();
		if (sym == RPARSY) {
			sym = getsym();
			if (sym == LBPARSY) {
				sym = getsym();
				com_sta();
				if (sym != RBPARSY) {
					error(LESS_RBRASY, line_num);
					do {
						sym = getsym();
					} while (sym != VOIDSY && sym != INTSY && sym != CHARSY);
					return;
				}
				else {
					sym = getsym();
					if (return_flag == 0) {
						error(LESS_RETURN, line_num);
					}
					append_mid_code(34, mid_empty, mid_empty, mid_empty);
					return_flag = 0;
					fprintf(graana_file, "This is a value function defination!\n");
					return;
				}
			}
			else {
				error(LESS_LBRASY, line_num);
				do {
					sym = getsym();
				} while (sym != VOIDSY && sym != INTSY && sym != CHARSY);
				return;
			}
		}
		else {
			error(LESS_RPARSY, line_num);
			do {
				sym = getsym();
			} while (sym != VOIDSY && sym != INTSY && sym != CHARSY);
			return;
		}
	}
	else {
		error(LESS_LPARSY, line_num);
		do {
			sym = getsym();
		} while (sym != VOIDSY && sym != INTSY && sym != CHARSY);
		return;
	}
	fprintf(graana_file,"This is a value function defination!\n");
}
void var_def() {
	 do{
		sym = getsym();
		if (sym == IDENSY) {
			strcpy(name_id, token);
			sym = getsym();
			if (sym == COMMASY || sym == SEMISY) {
				addr++;
				append_stable(name_id, 1, sign, 0, -1, addr);
				if (sign == 1) {
					append_mid_code(3, mid_empty, mid_empty, name_id);
				}
				else {
					append_mid_code(4, mid_empty, mid_empty, name_id);
				}
				continue;
			}
			else if (sym == LBRASY) {
				sym = getsym();
				if (sym == INT2SY) {
					if (cal_num > 0) {
						sym = getsym();
						if (sym == RBRASY) {
							addr += cal_num;
							append_stable(name_id,4,sign,0,cal_num,addr);
							sprintf(mid_array, "%d", cal_num);
							if (sign == 1) {
								append_mid_code(5, mid_array, mid_empty, name_id);
							}
							else {
								append_mid_code(6, mid_array, mid_empty, name_id);
							}
							sym = getsym();
						}
						else {
							error(LESS_RBRA, line_num);
							do{
								sym = getsym();
							} while (sym != COMMASY && sym != SEMISY);
							return;
						}
					}
					else {
						error(VAR_DEF_ARRAY_ERROR,line_num);
						do {
							sym = getsym();
						} while (sym != COMMASY && sym != SEMISY);
						return;
					}
				}
				else {
					error(INVALID_INT, line_num);
					do {
						sym = getsym();
					} while (sym != COMMASY && sym != SEMISY);
					return;
				}
			}
			else {
				error(VAR_DEF_ERROR, line_num);
				do {
					sym = getsym();
				} while (sym != COMMASY && sym != SEMISY);
				return;
			}
		}
		else {
			error(LESS_IDEN, line_num);
			do {
				sym = getsym();
			} while (sym != COMMASY && sym != SEMISY);
			return;
		}
	} while (sym == COMMASY);
	fprintf(graana_file,"This is a variable defination!\n");
}
void var_dec() {
	while (sym == INTSY || sym == CHARSY) {
		if (sym == INTSY)
			sign = 1;
		else
			sign = 2;
		var_def();
		if (sym == SEMISY) {
			sym = getsym();
		}
		else{
			error(SEMI_ERROR, line_num);
			do{
				sym = getsym();
			}while (sym != INTSY && sym != CHARSY && sym != VOIDSY && sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != PRINTFSY && sym != RETURNSY && sym != LBRASY && sym != IDENSY);
			return;
		}
	}
	fprintf(graana_file,"This is a variable declaration!\n");
}
void def_head() {
	int i = 2;
	if (sym == INTSY || sym == CHARSY) {
		if (sym == INTSY) {
			i = 1;
			type_flag = 0;
		}
		else {
			type_flag = 1;
		}
		sym = getsym();
	}
	if (sym == IDENSY) {     //填表
		strcpy(name_id, token);
		addr = -1;
		addr++;
		append_stable(name_id, 2, i, 0, 0, addr);
		fprintf(graana_file,"This is a defination head!\n"); 
		sym = getsym();
	}
	else {
		error(LESS_IDEN, line_num);
	}
}
void statement() {
	var_num = 0;
	int func_type;
	if (sym == IFSY) {
		if_sta();
	}
	else if (sym == WHILESY) {
		while_sta();
	}
	else if (sym == SWITCHSY) {
		switch_sta();
	}
	else if (sym == LBPARSY) {
		sym = getsym();
		sta_list();
		if (sym != RBPARSY) {
			error(LESS_RBRASY, line_num);
			do{
				sym = getsym();
			} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
			return;
		}
		else {
			sym = getsym();
		}
	}
	else if (sym == SCANFSY) {
		scanf_sta();
		if (sym == SEMISY) {
			sym = getsym();
		}
		else{
			error(SEMI_ERROR, line_num);
			do {
				sym = getsym();
			} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
			return;
		}
	}
	else if (sym == PRINTFSY) {
		printf_sta();
		if (sym == SEMISY) {
			sym = getsym();
		}
		else {
			error(SEMI_ERROR, line_num);
			do {
				sym = getsym();
			} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
			return;
		}
	}
	else if (sym == RETURNSY) {
		return_sta();
		if (sym == SEMISY) {
			sym = getsym();
		}
		else {
			error(SEMI_ERROR, line_num);
			do {
				sym = getsym();
			} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
			return;
		}
	}
	else if (sym == SEMISY) {
		sym = getsym();
	}
	else if (sym == IDENSY) {
		f_ch = ch;
		f_line_loc = line_loc;
		f_sym = sym;
		strcpy(f_token, token);
		sym = getsym();
		if (sym == LPARSY) {
			ch = f_ch;
			line_loc = f_line_loc;
			sym = f_sym;
			strcpy(token, f_token);
			func_type = index_stable(token, 2);
			if (func_type == 1 || func_type == 2) {
				val_fun_call(0);
			}
			else if (func_type == 0) {
				void_fun_call();
			}
			else {
				sym = getsym();
				do {
					sym = getsym();
				} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
				return;
			}
			if (sym == SEMISY) {
				sym = getsym();
			}
			else {
				error(SEMI_ERROR, line_num);
				do {
					sym = getsym();
				} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
				return;
			}
		}
		else if (sym == ASSIGNSY || sym == LBRASY) {
			ch = f_ch;
			line_loc = f_line_loc;
			sym = f_sym;
			strcpy(token, f_token);
			assign_sta();
			if (sym == SEMISY) {
				sym = getsym();
			}
			else {
				error(SEMI_ERROR, line_num);
				do {
					sym = getsym();
				} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
				return;
			}
		}
	}
	else {
		error(STA_ERROR, line_num);
		do {
			sym = getsym();
		} while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY);
		return;
	}
	fprintf(graana_file,"This is a statement!\n");
}
int int_judge() {
	if (sym == PLUSSY || sym == MINUSSY)
	{
		if (sym == MINUSSY) {
			sign = 0;
		}
		sym = getsym();
	}
	if (sym == INT2SY) {
		return 1;
	}
	return 0;
}
void con_def() {
	sign = 1;
	int zf_flag = 0;
	int flag = 0;
	if (sym == INTSY || sym == CHARSY) {
		if (sym == CHARSY)
			flag = 1;
		sym = getsym();
		do{
			if (sym == COMMASY) {
				sym = getsym();
			}
			if (sym == IDENSY) {
				strcpy(name_id, token);
				sym = getsym();
				if (sym == ASSIGNSY) {
					sym = getsym();
					if (!flag){
						if (sym == PLUSSY || sym == MINUSSY) {
							if (sym == PLUSSY) {
								sign = 1;
							}
							else {
								sign = 0;
							}
							zf_flag = 1;
							sym = getsym();
						}
						if (sym != INT2SY) {
							error(INVALID_INT, line_num);
							do {
								sym = getsym();
							}while (sym != COMMASY && sym != SEMISY);
							continue;
						}
						if (sign == 0) {
							cal_num = -cal_num;
							sign = 1;
						}
						addr++;
						append_stable(name_id, 0, 1, cal_num, -1, addr);
						sprintf(mid_array, "%d", cal_num);
						append_mid_code(1, mid_array,mid_empty, name_id);
						sym = getsym();
					}
					else if (flag && (sym == CHAR2SY)) {
						addr++;
						append_stable(name_id, 0, 2, ch1, -1, addr);
						sprintf(mid_array, "%d", ch1);
						append_mid_code(2, mid_array, mid_empty, name_id);
						sym = getsym();
					}
					else {
						error(CONST_DEF_VALUE_ERROR, line_num);
						do {
							sym = getsym();
						} while (sym != COMMASY && sym != SEMISY);
						continue;
					}
				}
				else {
					error(CONST_DEF_VALUE_ERROR, line_num);
					do {
						sym = getsym();
					} while (sym != COMMASY && sym != SEMISY);
					continue;
				}
			}
			else {
				error(LESS_IDEN, line_num);
				do {
					sym = getsym();
				} while (sym != COMMASY && sym != SEMISY);
				continue;
			}
		} while (sym==COMMASY);
		fprintf(graana_file,"This is a constant definition!\n");
	}
	else {
		error(CONST_DEF_ERROR, line_num);
		do {
			sym = getsym();
		} while (sym != COMMASY && sym != SEMISY);
		return;
	}
}
void con_dec() {
	while (sym == CONSY) {
		sym = getsym();
		con_def();
		if (sym != SEMISY) {
			error(SEMI_ERROR, line_num);
			do{
				sym = getsym();
			} while (sym != CONSY && sym != INTSY && sym != CHARSY && sym != VOIDSY && sym != IFSY && sym != WHILESY && sym != LBRASY && sym != IDENSY && sym != SCANFSY && sym != PRINTFSY && sym != SWITCHSY && sym != RETURNSY);
			return;
		}
		else
			sym = getsym();
	}
	fprintf(graana_file,"This is a constant declaration!\n");
}
void program() {
	if (sym == CONSY) {   
		con_dec();
	}
	while (sym == INTSY || sym == CHARSY) {   
		if (sym == INTSY)
			sign = 1;
		else
			sign = 2;
		f_sym = sym;	
		strcpy(f_token, token);
		f_line_loc = line_loc;    
		f_ch = ch;
		sym = getsym();
		if (sym != IDENSY) {	
			error(LESS_IDEN, line_num);
			do{
				sym = getsym();
			} while (sym != INTSY && sym != CHARSY && sym != VOIDSY);
			continue;
		}
		else {
			sym = getsym();
			if (sym == COMMASY || sym == LBRASY || sym == SEMISY) {			
				sym = f_sym;
				strcpy(token, f_token);
				line_loc = f_line_loc;
				ch = f_ch;
				var_def();
				if (sym != SEMISY) {
					error(SEMI_ERROR, line_num);
					do{
						sym = getsym();
					}while (sym != INTSY && sym != CHARSY && sym != VOIDSY);
					continue;
				}
				else {
					sym = getsym();
				}
			}
			else if (sym == LPARSY) {	
				sym = f_sym;
				strcpy(token, f_token);
				line_loc = f_line_loc;
				ch = f_ch;
				break;
			}
			else {
				error(VAR_DEC_ERROR, line_num);
				do{
					sym = getsym();
				}while (sym != INTSY && sym != CHARSY && sym != VOIDSY);
				continue;
			}
		}
	}
	while (sym == INTSY || sym == CHARSY || sym == VOIDSY) {
		if (sym == INTSY || sym == CHARSY) {
			val_fun_def();
		}
		else {
			strcpy(f_token, token);
			f_sym = sym;
			f_line_loc = line_loc;
			f_ch = ch;
			sym = getsym();
			if (sym == MAINSY) {
				strcpy(token, f_token);
				sym = f_sym;
				line_loc = f_line_loc;
				ch = f_ch;
				break;
			}
			else if(sym==IDENSY){
				strcpy(token, f_token);
				sym = f_sym;
				line_loc = f_line_loc;
				ch = f_ch;
				void_fun_def();
			}
			else {
				error(FUN_DEC_ERROR, line_num);
				do{
					sym = getsym();
				}while (sym != INTSY && sym != CHARSY && sym != VOIDSY);
				continue;
			}
		}
	}
	main_func();
	fprintf(graana_file,"This is a program!\n");
	printf("Grammar analysis completed!\n");
	fprintf(graana_file, "Grammar analysis completed!\n");
}
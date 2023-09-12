#include<stdio.h>
#include<stdlib.h>
#include"gra_ana.h"
#include"lex_ana.h"
#include"error.h"
extern FILE *graana_file;
int f_sym;
int f_ch;
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
void case_list();
void case_sub_sta();
void default_sta();
void val_fun_call();
void void_fun_call();
void val_para_list();
void scanf_sta();
void printf_sta();
void return_sta();
int int_judge();
void return_sta() {
	sym = getsym();
	if (sym == LPARSY) {
		sym = getsym();
		expr();
		if (sym == RPARSY) {
			sym = getsym();
			fprintf(graana_file,"This is a return statement!\n");
			return;
		}
		else {
			error(LESS_RPARSY, line_num);
			 while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
				 sym = getsym();
			 }
			return;
		}
	}
	else if (sym == SEMISY) {
		fprintf(graana_file,"This is a return statement!\n");
		return;
	}
	else {
		error(RETURN_ERROR, line_num);
		  while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
			  sym = getsym();
		  }
		return;
	}
	fprintf(graana_file,"This is a return statement!\n");
}
void printf_sta() {
	sym = getsym();
	if (sym == LPARSY) {
		sym = getsym();
		if (sym == STRINGSY) {
			sym = getsym();
			if (sym == COMMASY) {
				sym = getsym();
				expr();
			}
		}
		else {
			expr();
		}
		if (sym == RPARSY) {
			sym = getsym();
			fprintf(graana_file,"This is a print statement!\n");
			return;
		}
		else {
			error(LESS_RPARSY, line_num);
			  while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
				  sym = getsym();
			  }
			return;
		}
	}
	else {
		error(LESS_LPARSY, line_num);
		  while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
			  sym = getsym();
		  }
		return;
	}
	fprintf(graana_file,"This is a scan statement!\n");
}
void scanf_sta() {
	sym = getsym();
	if (sym == LPARSY) {
		sym = getsym();
		 do{
			if(sym == COMMASY) {
				sym = getsym();
			}
			if (sym == IDENSY) {
				sym = getsym();
			}
			else {
				error(LESS_IDEN, line_num);
				 while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
					 sym = getsym();
				 }
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
			 while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
				 sym = getsym();
			 }
			return;
		}
	}
	else {
		error(LESS_LPARSY, line_num);
		 while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
			 sym = getsym();
		 }
		return;
	}
	fprintf(graana_file,"This is a scan statement!\n");
}
void val_para_list() {
	 do{
		if (sym == RPARSY) {
			break;
		}
		if (sym == COMMASY) {
			sym = getsym();
		}
		if (sym == IDENSY || sym == CHAR2SY || int_judge() || sym == LPARSY) {
			expr();
		}
		else {
			error(VAL_FUNC_LIST_ERROR, line_num);
			while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
				sym = getsym();
			}
			return;
		}
	} while (sym == COMMASY);
}
void void_fun_call() {
	if (sym == IDENSY) {
		sym = getsym();
		if (sym == LPARSY) {
			sym = getsym();
			val_para_list();
			if (sym == RPARSY) {
				sym = getsym();
				fprintf(graana_file,"This is a void function call!\n");
				return;
			}
			else {
				error(LESS_RPARSY, line_num);
				  while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
					  sym = getsym();
				  }
				return;
			}
		}
		else {
			error(LESS_LPARSY, line_num);
			 while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
				 sym = getsym();
			 }
			return;
		}
	}
	else {
		error(LESS_IDEN, line_num);
		while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
			sym = getsym();
		}
		return;
	}
	fprintf(graana_file,"This is a void function call!\n");
}
void val_fun_call() {
	if (sym == IDENSY) {
		sym = getsym();
		if (sym == LPARSY) {
			sym = getsym();
			val_para_list();
			if (sym == RPARSY) {
				sym = getsym();
				fprintf(graana_file,"This is a value function call!\n");
				return;
			}
			else {
				error(LESS_RPARSY, line_num);
				while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
					sym = getsym();
				}
				return;
			}
		}
		else {
			error(LESS_LPARSY, line_num);
			while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
				sym = getsym();
			}
			return;
		}
	}
	else {
		error(LESS_IDEN, line_num);
		while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
			sym = getsym();
		}
		return;
	}
	fprintf(graana_file,"This is a value function call!\n");
}
void default_sta() {
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
			}
		}
		else {
			error(LESS_COLON, line_num);
			while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
				sym = getsym();
			}
			return;
		}
	}
	else {
		error(DEFAULT_ERROR, line_num);
		while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
			sym = getsym();
		}
		return;
	}
	fprintf(graana_file,"This is a default!\n");
}
void case_sub_sta() {
	if (sym == CASESY) {
		sym = getsym();
		if (int_judge() || sym == CHAR2SY) {
			sym = getsym();
			if (sym == COLONSY) {
				sym = getsym();
				statement();
			}
			else {
				error(LESS_COLON, line_num);
				while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
					sym = getsym();
				}
				return;
			}
		}
		else {
			error(CONST_DEF_VALUE_ERROR, line_num);
			while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
				sym = getsym();
			}
			return;
		}
	}
	else {
		error(CASE_ERROR, line_num);
		while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
			sym = getsym();
		}
		return;
	}
}
void case_list() {
	 do{
		case_sub_sta();
	} while (sym == CASESY);
}
void switch_sta() {
	sym = getsym();
	if (sym == LPARSY) {
		sym = getsym();
		expr();
		if (sym == RPARSY) {
			sym = getsym();
			if (sym == LBPARSY) {
				sym = getsym();
				case_list();
				default_sta();
				if (sym == RBPARSY) {
					sym = getsym();
					fprintf(graana_file,"This is a switch statement!\n");
					return;
				}
				else {
					error(LESS_RBRASY, line_num);
					while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
						sym = getsym();
					}
					return;
				}
			}
			else {
				error(LESS_LPARSY, line_num);
				while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
					sym = getsym();
				}
				return;
			}
		}
		else {
			error(LESS_RPARSY, line_num);
			while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
				sym = getsym();
			}
			return;
		}
	}
	else {
		error(LESS_LPARSY, line_num);
		while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
			sym = getsym();
		}
		return;
	}
	fprintf(graana_file,"This is a switch statement!\n");
}
void while_sta() {
	sym = getsym();
	if (sym == LPARSY) {
		sym = getsym();
		condition();
		if (sym == RPARSY) {
			sym = getsym();
			statement();
		}
		else {
			error(LESS_RPARSY, line_num);
			while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
				sym = getsym();
			}
			return;
		}
	}
	else {
		error(LESS_LPARSY, line_num);
		while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
			sym = getsym();
		}
		return;
	}
	fprintf(graana_file,"This is a loop statement!\n");
}
void condition() {
	expr();
	if (sym == EQSY || sym == NEQSY || sym == LEEQSY || sym == LESY || sym == MOEQSY || sym == MOSY) {
		sym = getsym();
		expr();
	}
	fprintf(graana_file,"This is a condition!\n");
}
void if_sta() {
	sym = getsym();
	if (sym == LPARSY) {
		sym = getsym();
		condition();
		if (sym == RPARSY) {
			sym = getsym();
			statement();
		}
		else {
			error(LESS_RPARSY,line_num);
			while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
				sym = getsym();
			}
			return;
		}
	}
	else {
		error(LESS_LPARSY,line_num);
		while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
			sym = getsym();
		}
		return;
	}
	fprintf(graana_file,"This is a condition statement!\n");
}
void assign_sta() {
	sym = getsym();
	if (sym == ASSIGNSY) {
		sym = getsym();
		expr();
	}
	else if (sym == LBRASY) {
		sym = getsym();
		expr();
		if (sym == RBRASY) {
			sym = getsym();
			if (sym = ASSIGNSY) {
				sym = getsym();
				expr();
			}
			else {
				error(LESS_ASSIGN, line_num);
				while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
					sym = getsym();
				}
				return;
			}
		}
		else {
			error(LESS_RBRASY, line_num);
			while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
				sym = getsym();
			}
			return;
		}
	}
	else {
		error(ASSIGN_ERROR, line_num);
		while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
			sym = getsym();
		}
		return;
	}
	fprintf(graana_file,"This is an assign statement!\n");
}
void factor() {
	if (sym == PLUSSY || sym == MINUSSY) {
		if (int_judge()) {
			sym = getsym();
			fprintf(graana_file,"This is a factor!\n");
			return;
		}
		else {
			error(INVALID_INT, line_num);
			while (sym != SEMISY && sym != ASSIGNSY && sym != PLUSSY && sym != MINUSSY && sym != MULTSY && sym != DIVSY && sym != RPARSY && sym != COMMASY && sym != LEEQSY && sym != LESY && sym != MOSY && sym != MOEQSY && sym != EQSY && sym != NEQSY) {
				sym = getsym();
			}
			return;
		}
	}
	else if (sym == INT2SY) {
		sym = getsym();
		fprintf(graana_file,"This is a factor!\n");
		return;
	}
	else if (sym == CHAR2SY) {
		sym = getsym();
		fprintf(graana_file,"This is a factor!\n");
		return;
	}
	else if (sym == LPARSY) {
		sym = getsym();
		expr();
		if (sym == RPARSY) {
			sym = getsym();
			fprintf(graana_file,"This is a factor!\n");
			return;
		}
		else {
			error(LESS_RPARSY, line_num);
			while (sym != SEMISY && sym != ASSIGNSY && sym != PLUSSY && sym != MINUSSY && sym != MULTSY && sym != DIVSY && sym != RPARSY && sym != COMMASY && sym != LEEQSY && sym != LESY && sym != MOSY && sym != MOEQSY && sym != EQSY && sym != NEQSY) {
				sym = getsym();
			}
			return;
		}
	}
	else if (sym == IDENSY) {
		f_sym = sym;
		f_line_loc = line_loc;
		f_ch = ch;
		sym = getsym();
		if (sym == LBRASY) {
			sym = getsym();
			expr();
			if (sym == RBRASY) {
				sym = getsym();
				fprintf(graana_file,"This is a factor!\n");
				return;
			}
			else {
				error(LESS_RBRA, line_num);
				while (sym != SEMISY && sym != ASSIGNSY && sym != PLUSSY && sym != MINUSSY && sym != MULTSY && sym != DIVSY && sym != RPARSY && sym != COMMASY && sym != LEEQSY && sym != LESY && sym != MOSY && sym != MOEQSY && sym != EQSY && sym != NEQSY) {
					sym = getsym();
				}
				return;
			}
		}
		else if (sym == LPARSY) {
			sym = f_sym;
			line_loc = f_line_loc;
			ch = f_ch;
			val_fun_call();
			fprintf(graana_file,"This is a factor!\n");
			return;
		}
		else
		{
			fprintf(graana_file,"This is a factor!\n");
			return;
		}
	}
	else {
		error(FACTOR_ERROR, line_num);
		while (sym != SEMISY && sym != ASSIGNSY && sym != PLUSSY && sym != MINUSSY && sym != MULTSY && sym != DIVSY && sym != RPARSY && sym != COMMASY && sym != LEEQSY && sym != LESY && sym != MOSY && sym != MOEQSY && sym != EQSY && sym != NEQSY) {
			sym = getsym();
		}
		return;
	}
}
void term() {
	factor();
	while (sym == MULTSY || sym == DIVSY) {
		sym = getsym();
		factor();
	}
}
void expr() {
	if (sym == PLUSSY || sym == MINUSSY) {
		sym = getsym();
	}
	term();
	while (sym == PLUSSY || sym == MINUSSY) {
		sym = getsym();
		term();
	}
}
void main_func() {
	sym = getsym();
	if (sym == MAINSY) {
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
		while (sym != RPARSY) {
			sym = getsym();
		}
		return;
	}
	sym = getsym();
}
void para_list() {
	 do{
		if (sym == COMMASY) {
			sym = getsym();
		}
		if (sym == INTSY || sym == CHARSY) {
			para();
		}
		else if(sym==RPARSY){
			return;
		}
		else {
			error(PARA_LIST_ERROR, line_num);
			while (sym != RPARSY) {
				sym = getsym();
			}
			break;
		}
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
						while (sym != VOIDSY && sym != INTSY && sym != CHARSY) {
							sym = getsym();
						}
						return;
					}
					else {
						sym = getsym();
					}
				}
				else {
					error(LESS_LBRASY, line_num);
					while (sym != VOIDSY && sym != INTSY && sym != CHARSY) {
						sym = getsym();
					}
					return;
				}
			}
			else {
				error(LESS_RPARSY, line_num);
				while (sym != VOIDSY && sym != INTSY && sym != CHARSY) {
					sym = getsym();
				}
				return;
			}
		}
	}
	else {
		error(LESS_IDEN, line_num);
		while (sym != VOIDSY && sym != INTSY && sym != CHARSY) {
			sym = getsym();
		}
		return;
	}
	fprintf(graana_file,"This is a void function defination!\n");
}
void val_fun_def() {     //要有返回值
	def_head();
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
					while (sym != VOIDSY && sym != INTSY && sym != CHARSY) {
						sym = getsym();
					}
					return;
				}
				else {
					sym = getsym();
				}
			}
			else {
				error(LESS_LBRASY, line_num);
				while (sym != VOIDSY && sym != INTSY && sym != CHARSY) {
					sym = getsym();
				}
				return;
			}
		}
		else {
			error(LESS_RPARSY, line_num);
			while (sym != VOIDSY && sym != INTSY && sym != CHARSY) {
				sym = getsym();
			}
			return;
		}
	}
	else {
		error(LESS_LPARSY, line_num);
		while (sym != VOIDSY && sym != INTSY && sym != CHARSY) {
			sym = getsym();
		}
		return;
	}
	fprintf(graana_file,"This is a value function defination!\n");
}
void var_def() {
	 do{
		sym = getsym();
		if (sym == IDENSY) {
			sym = getsym();
			if (sym == COMMASY || sym == SEMISY) {
				continue;
			}
			else if (sym == LBRASY) {
				sym = getsym();
				if (sym == INT2SY) {
					cal_num = stringtonum();
					if (cal_num != 0) {
						sym = getsym();
						if (sym == RBRASY) {
							sym = getsym();
						}
						else {
							error(LESS_RBRA, line_num);
							while (sym != COMMASY && sym != SEMISY) {
								sym = getsym();
							}
							return;
						}
					}
					else {
						error(VAR_DEF_ARRAY_ERROR,line_num);
						while (sym != COMMASY && sym != SEMISY) {
							sym = getsym();
						}
						return;
					}
				}
				else {
					error(INVALID_INT, line_num);
					while (sym != COMMASY && sym != SEMISY) {
						sym = getsym();
					}
					return;
				}
			}
			else {
				error(VAR_DEF_ERROR, line_num);
				while (sym != COMMASY && sym != SEMISY) {
					sym = getsym();
				}
				return;
			}
		}
		else {
			error(LESS_IDEN, line_num);
			while (sym != COMMASY && sym != SEMISY) {
				sym = getsym();
			}
			return;
		}
	} while (sym == COMMASY);
	fprintf(graana_file,"This is a variable defination!\n");
}
void var_dec() {
	while (sym == INTSY || sym == CHARSY) {
		var_def();
		if (sym == SEMISY) {
			sym = getsym();
		}
		else{
			error(SEMI_ERROR, line_num);
			while (sym != INTSY && sym != CHARSY && sym != VOIDSY && sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != PRINTFSY && sym != RETURNSY && sym != LBRASY && sym != IDENSY) {
				sym = getsym();
			}
			return;
		}
	}
	fprintf(graana_file,"This is a variable declaration!\n");
}
void def_head() {
	if (sym == INTSY || sym == CHARSY) {
		sym = getsym();
	}
	if (sym == IDENSY) {     //填表
		fprintf(graana_file,"This is a defination head!\n"); 
		sym = getsym();
	}
	else {
		error(LESS_IDEN, line_num);
	}
}
void statement() {
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
			while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
				sym = getsym();
			}
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
			while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
				sym = getsym();
			}
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
			while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
				sym = getsym();
			}
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
			while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
				sym = getsym();
			}
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
		sym = getsym();
		if (sym == LPARSY) {
			ch = f_ch;
			line_loc = f_line_loc;
			sym = f_sym;
			void_fun_call();
			if (sym == SEMISY) {
				sym = getsym();
			}
			else {
				error(SEMI_ERROR, line_num);
				while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
					sym = getsym();
				}
				return;
			}
		}
		else if (sym == ASSIGNSY || sym == LBRASY) {
			ch = f_ch;
			line_loc = f_line_loc;
			sym = f_sym;
			assign_sta();
			if (sym == SEMISY) {
				sym = getsym();
			}
			else {
				error(SEMI_ERROR, line_num);
				while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
					sym = getsym();
				}
				return;
			}
		}
	}
	else {
		error(STA_ERROR, line_num);
		while (sym != IFSY && sym != WHILESY && sym != SWITCHSY && sym != SCANFSY && sym != LBRASY && sym != IDENSY && sym != PRINTFSY && sym != RETURNSY && sym != SEMISY) {
			sym = getsym();
		}
		return;
	}
	fprintf(graana_file,"This is a statement!\n");
}
int int_judge() {
	if (sym == PLUSSY || sym == MINUSSY)
		sym = getsym();
	if (sym == INT2SY) {
		return 1;
	}
	return 0;
}
void con_def() {
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
				sym = getsym();
				if (sym == ASSIGNSY) {
					sym = getsym();
					if ((!flag&&int_judge()) || (flag&&(sym==CHAR2SY))) {
						sym = getsym();
					}
					else {
						error(CONST_DEF_VALUE_ERROR, line_num);
						while (sym != COMMASY && sym != SEMISY) {
							sym = getsym();
						}
						return;
					}
				}
				else {
					error(CONST_DEF_VALUE_ERROR, line_num);
					while (sym != COMMASY && sym != SEMISY) {
						sym = getsym();
					}
					return;
				}
			}
			else {
				error(LESS_IDEN, line_num);
				while (sym != COMMASY && sym != SEMISY) {
					sym = getsym();
				}
				return;
			}
		} while (sym==COMMASY);
		fprintf(graana_file,"This is a constant definition!\n");
	}
	else {
		error(CONST_DEF_ERROR, line_num);
		while (sym != SEMISY) {
			sym = getsym();
		}
		return;
	}
}
void con_dec() {
	while (sym == CONSY) {
		sym = getsym();
		con_def();
		if (sym != SEMISY) {
			error(SEMI_ERROR, line_num);
			while (sym != CONSY && sym != INTSY && sym != CHARSY && sym != VOIDSY && sym != IFSY && sym != WHILESY && sym != LBRASY && sym != IDENSY && sym != SCANFSY && sym != PRINTFSY && sym != SWITCHSY && sym != RETURNSY) {
				sym = getsym();
			}
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
		f_sym = sym;	
		f_line_loc = line_loc;    
		f_ch = ch;
		sym = getsym();
		if (sym != IDENSY) {	
			error(LESS_IDEN, line_num);
			while (sym != INTSY && sym != CHARSY && sym != VOIDSY) {
				sym = getsym();
			}
			continue;
		}
		else {
			sym = getsym();
			if (sym == COMMASY || sym == LBRASY || sym == SEMISY) {			
				sym = f_sym;
				line_loc = f_line_loc;
				ch = f_ch;
				var_def();
				if (sym != SEMISY) {
					error(SEMI_ERROR, line_num);
					while (sym != INTSY && sym != CHARSY && sym != VOIDSY) {
						sym = getsym();
					}
					continue;
				}
				else {
					sym = getsym();
				}
			}
			else if (sym == LPARSY) {	
				sym = f_sym;
				line_loc = f_line_loc;
				ch = f_ch;
				break;
			}
			else {
				error(VAR_DEC_ERROR, line_num);
				while (sym != INTSY && sym != CHARSY && sym != VOIDSY) {
					sym = getsym();
				}
				continue;
			}
		}
	}
	while (sym == INTSY || sym == CHARSY || sym == VOIDSY) {
		if (sym == INTSY || sym == CHARSY) {
			val_fun_def();
		}
		else {
			f_sym = sym;
			f_line_loc = line_loc;
			f_ch = ch;
			sym = getsym();
			if (sym == MAINSY) {
				sym = f_sym;
				line_loc = f_line_loc;
				ch = f_ch;
				break;
			}
			else if(sym==IDENSY){
				sym = f_sym;
				line_loc = f_line_loc;
				ch = f_ch;
				void_fun_def();
			}
			else {
				error(FUN_DEC_ERROR, line_num);
				while (sym != INTSY && sym != CHARSY && sym != VOIDSY) {
					sym = getsym();
				}
				continue;
			}
		}
	}
	main_func();
	fprintf(graana_file,"This is a program!\n");
	printf("Grammar analysis completed!\n");
	fprintf(graana_file, "Grammar analysis completed!\n");
}
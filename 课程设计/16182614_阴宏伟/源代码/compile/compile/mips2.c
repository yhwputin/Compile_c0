#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lex_ana.h"
#include"gra_ana.h"
#include"sym_tab.h"
#include"error.h"
#include"mid_code.h"
#include"mips.h"
#include"mips2.h"
#include"optimizer.h"
char tep_func[100];
int assign_flag;
int va_fl = 0;
int fun_loop = 0;
extern FILE *mips_file;
void count_var() {
	int i,j,k;
	int end;
	for (i = 0; i < f_block.func_index; i++) {
		if (i + 1 == f_block.func_index) {
			end == m_table.mid_num;
		}
		else {
			end = f_block.func_list[i + 1].start_num;
		}
		for (j = f_block.func_list[i].start_num; j < end; j++) {
			if (m_table.mid_list[j].use == 0) {
				continue;
			}
			if (m_table.mid_list[j].op == 7 || m_table.mid_list[j].op == 8 || m_table.mid_list[j].op == 9) {
				strcpy(f_c_var[i].func_name, m_table.mid_list[j].result);
				f_c_var[i].index = 0;
			}
			else if (m_table.mid_list[j].op == 3 || m_table.mid_list[j].op == 4) {
				f_c_var[i].var_clist[f_c_var[i].index].num = 0;
				strcpy(f_c_var[i].var_clist[f_c_var[i].index].var_num, m_table.mid_list[j].result);
				f_c_var[i].index++;
			}
			else {
				if (m_table.mid_list[j].result[0] != '@'&&m_table.mid_list[j].result[0] != '$') {
					for (k = 0; k < f_c_var[i].index; k++) {
						if(strcmp())
					}
				}
			}
		}
	}
}
void load_ins2(char reg[], char name[]) {
	int count;
	if ((name[0] >= 'a'&&name[0] <= 'z') || name[0] == '_' || name[0] == '$') {
		count = index_inf(name);
		if (global_flag == 1) {
			if (var_flag == 1) {
				fprintf(mips_file, "la $t8,%s\n", name);
				fprintf(mips_file, "lw %s,0($t8)\n", reg);
			}
			else if (const_flag == 1) {
				fprintf(mips_file, "li %s,%d\n", reg, count);
			}
		}
		else {
			if (const_flag == 1) {
				fprintf(mips_file, "li %s0,%d\n", reg, count);
			}
			else if (var_flag == 1 || para_flag == 1) {
				fprintf(mips_file, "lw %s,%d($fp)\n", reg, (-count - 1) * 4);
			}
		}
	}
	else {
		fprintf(mips_file, "li %s,%s\n", reg, name);
	}
}
void store_ins2(char reg[], char name[]) {
	int count;
	count = index_inf(name);
	if (global_flag == 1) {
		fprintf(mips_file, "la $t9,%s\n", name);
		fprintf(mips_file, "sw %s,0($t9)\n", reg);
	}
	else {
		fprintf(mips_file, "sw %s,%d($fp)\n", reg, (-count - 1) * 4);
	}
}
void data_process() {
	int func_i, i;
	int j = 0;
	int max_var;
	func_i = stable.func_list[0];
	for (i = 0; i < func_i; i++) {
		if (stable.list[i].kind == 0) {
			fprintf(mips_file, "%s: .word %d\n", stable.list[i].name, stable.list[i].value);
		}
		else {
			if (stable.list[i].size != -1) {
				fprintf(mips_file, "%s: .space %d\n", stable.list[i].name, stable.list[i].size * 4);
			}
			else {
				fprintf(mips_file, "%s: .word 0\n", stable.list[i].name);
			}
		}
	}
	for (i = 0; i < m_table.mid_num; i++) {
		max_var = 0;
		if (m_table.mid_list[i].result[0] == '$') {
			if (m_table.mid_list[i].result[5] >= '0'&&m_table.mid_list[i].result[5] <= '9') {
				if (m_table.mid_list[i].result[6] >= '0'&&m_table.mid_list[i].result[6] <= '9') {
					max_var = (m_table.mid_list[i].result[4] - '0') * 100 + (m_table.mid_list[i].result[5] - '0') * 10 + (m_table.mid_list[i].result[6] - '0');
				}
				else {
					max_var = (m_table.mid_list[i].result[4] - '0') * 10 + (m_table.mid_list[i].result[5] - '0');
				}
			}
			else {
				max_var = (m_table.mid_list[i].result[4] - '0');
			}
			if (max_var_num < max_var) {
				max_var_num = max_var;
			}
		}
		if (m_table.mid_list[i].op == 7 || m_table.mid_list[i].op == 8 || m_table.mid_list[i].op == 9) {
			if (va_fl == 0) {
				va_fl = 1;
			}
			else {
				stable.var_num[j++] = max_var_num + 1;
				max_var_num = 0;
			}
		}
		if (m_table.mid_list[i].op == 32 && m_table.mid_list[i].result[0] == '\"') {
			fprintf(mips_file, "STR%d: .asciiz %s\n", i, m_table.mid_list[i].result);
		}
	}
	stable.var_num[j++] = max_var_num + 1;
	max_var_num = 0;
	va_fl = 0;
}
void mips_process() {
	int condition_judge;
	int i;
	int i2;
	int addr;
	int size;
	int para_num;
	for (i = 0; i < m_table.mid_num; i++) {
		switch (m_table.mid_list[i].op) {
		case 7:
		case 8:
		case 9: {
			strcpy(tep_func, m_table.mid_list[i].result);
			size = get_func_size(tep_func);
			para_num = get_func_para_num(tep_func);
			fprintf(mips_file, "%s:\n", tep_func);
			fprintf(mips_file, "li $t0,0\n");
			for (i2 = 0; i2 < para_num; i2++) {
				fprintf(mips_file, "lw $s4,0($sp)\n");
				fprintf(mips_file, "subi $sp,$sp,8\n");
				fprintf(mips_file, "sw $s4,0($sp)\n");
				fprintf(mips_file, "addi $sp,$sp,12\n");
			}
			fprintf(mips_file, "move $s1,$fp\n");
			fprintf(mips_file, "move $fp,$sp\n");
			fprintf(mips_file, "addi $fp,$fp,-4\n");
			fprintf(mips_file, "sw $s1,0($fp)\n");
			fprintf(mips_file, "sw $ra,-4($fp)\n");
			fprintf(mips_file, "addi $sp,$sp,-8\n");
			if (size != 0) {
				fprintf(mips_file, "li $t1,%d\n", size);
				fprintf(mips_file, "TEP_%d:\n", fun_loop);
				fprintf(mips_file, "lw $0,0($sp)\n");
				fprintf(mips_file, "addi $sp,$sp,-4\n");
				fprintf(mips_file, "addi $t0,$t0,1\n");
				fprintf(mips_file, "bne $t0,$t1,TEP_%d\n", fun_loop++);
			}
			break;
		}
		case 10: {
			break;
		}
		case 11: {
			break;
		}
		case 12: {
			load_ins("$t0", m_table.mid_list[i].src1);
			load_ins("$t1", m_table.mid_list[i].src2);
			fprintf(mips_file, "add $t0,$t0,$t1\n");
			store_ins("$t0", m_table.mid_list[i].result);
			break;
		}
		case 13: {
			load_ins("$t0", m_table.mid_list[i].src1);
			load_ins("$t1", m_table.mid_list[i].src2);
			fprintf(mips_file, "sub $t0,$t0,$t1\n");
			store_ins("$t0", m_table.mid_list[i].result);
			break;
		}
		case 14: {
			load_ins("$t0", m_table.mid_list[i].src1);
			load_ins("$t1", m_table.mid_list[i].src2);
			fprintf(mips_file, "mult $t0,$t1\n");
			fprintf(mips_file, "mflo $t0\n");
			store_ins("$t0", m_table.mid_list[i].result);
			break;
		}
		case 15: {
			load_ins("$t0", m_table.mid_list[i].src1);
			load_ins("$t1", m_table.mid_list[i].src2);
			fprintf(mips_file, "div $t0,$t1\n");
			fprintf(mips_file, "mflo $t0\n");
			store_ins("$t0", m_table.mid_list[i].result);
			break;
		}
		case 16: {
			load_ins("$t0", m_table.mid_list[i].src1);
			store_ins("$t0", m_table.mid_list[i].result);
			break;
		}
		case 17: {
			load_ins("$t0", m_table.mid_list[i].src2);
			fprintf(mips_file, "sll $s5,$t0,2\n");
			addr = index_inf(m_table.mid_list[i].src1);
			if (global_flag == 1) {
				fprintf(mips_file, "la $s0,%s\n", m_table.mid_list[i].src1);
			}
			else {
				fprintf(mips_file, "addi $s0,$fp,-%d\n", addr * 4 + 4);
			}
			fprintf(mips_file, "add $s0,$s5,$s0\n");
			fprintf(mips_file, "lw $t7,0($s0)\n");
			store_ins("$t7", m_table.mid_list[i].result);
			break;
		}
		case 18: {
			load_ins("$t3", m_table.mid_list[i].src1);
			load_ins("$t4", m_table.mid_list[i].src2);
			fprintf(mips_file, "sll $s5,$t4,2\n");
			addr = index_inf(m_table.mid_list[i].result);
			if (global_flag == 1) {
				fprintf(mips_file, "la $s6,%s\n", m_table.mid_list[i].result);
			}
			else {
				fprintf(mips_file, "addi $s6,$fp,-%d\n", addr * 4 + 4);
			}
			fprintf(mips_file, "add $s6,$s6,$s5\n");
			fprintf(mips_file, "sw $t3,0($s6)\n");
			break;
		}
		case 19: {
			condition_judge = 0;
			load_ins("$t0", m_table.mid_list[i].src1);
			load_ins("$t1", m_table.mid_list[i].src2);
			fprintf(mips_file, "sub $t2,$t0,$t1\n");
			break;
		}
		case 20: {
			condition_judge = 1;
			load_ins("$t0", m_table.mid_list[i].src1);
			load_ins("$t1", m_table.mid_list[i].src2);
			fprintf(mips_file, "sub $t2,$t0,$t1\n");
			break;
		}
		case 21: {
			condition_judge = 2;
			load_ins("$t0", m_table.mid_list[i].src1);
			load_ins("$t1", m_table.mid_list[i].src2);
			fprintf(mips_file, "sub $t2,$t0,$t1\n");
			break;
		}
		case 22: {
			condition_judge = 3;
			load_ins("$t0", m_table.mid_list[i].src1);
			load_ins("$t1", m_table.mid_list[i].src2);
			fprintf(mips_file, "sub $t2,$t0,$t1\n");
			break;
		}
		case 23: {
			condition_judge = 4;
			load_ins("$t0", m_table.mid_list[i].src1);
			load_ins("$t1", m_table.mid_list[i].src2);
			fprintf(mips_file, "sub $t2,$t0,$t1\n");
			break;
		}
		case 24: {
			condition_judge = 5;
			load_ins("$t0", m_table.mid_list[i].src1);
			load_ins("$t1", m_table.mid_list[i].src2);
			fprintf(mips_file, "sub $t2,$t0,$t1\n");
			break;
		}
		case 25: {
			fprintf(mips_file, "j %s\n", m_table.mid_list[i].result);
			break;
		}
		case 26: {
			if (condition_judge == 0) {
				fprintf(mips_file, "beq $t2,$0,%s\n", m_table.mid_list[i].result);
			}
			else if (condition_judge == 1) {
				fprintf(mips_file, "blez $t2,%s\n", m_table.mid_list[i].result);
			}
			else if (condition_judge == 2) {
				fprintf(mips_file, "bgez $t2,%s\n", m_table.mid_list[i].result);
			}
			else if (condition_judge == 3) {
				fprintf(mips_file, "bne $t2,$0,%s\n", m_table.mid_list[i].result);
			}
			else if (condition_judge == 4) {
				fprintf(mips_file, "bltz $t2,%s\n", m_table.mid_list[i].result);
			}
			else {
				fprintf(mips_file, "bgtz $t2,%s\n", m_table.mid_list[i].result);
			}
			break;
		}
		case 27: {
			if (condition_judge == 0) {
				fprintf(mips_file, "bne $t2,$0,%s\n", m_table.mid_list[i].result);
			}
			else if (condition_judge == 1) {
				fprintf(mips_file, "bgtz $t2,%s\n", m_table.mid_list[i].result);
			}
			else if (condition_judge == 2) {
				fprintf(mips_file, "bltz $t2,%s\n", m_table.mid_list[i].result);
			}
			else if (condition_judge == 3) {
				fprintf(mips_file, "beq $t2,$0,%s\n", m_table.mid_list[i].result);
			}
			else if (condition_judge == 4) {
				fprintf(mips_file, "bgez $t2,%s\n", m_table.mid_list[i].result);
			}
			else {
				fprintf(mips_file, "blez $t2,%s\n", m_table.mid_list[i].result);
			}
			break;
		}
		case 28: {
			load_ins("$t0", m_table.mid_list[i].result);
			fprintf(mips_file, "subi $sp,$sp,4\n");
			fprintf(mips_file, "sw $t0,0($sp)\n");
			break;
		}
		case 29: {
			fprintf(mips_file, "jal %s\n", m_table.mid_list[i].src1);
			if (strcmp(m_table.mid_list[i].result, mid_empty) != 0) {
				fprintf(mips_file, "move $t0,$v0\n");
				store_ins("$t0", m_table.mid_list[i].result);
			}
			break;
		}
		case 30: {
			if (strcmp(m_table.mid_list[i].result, mid_empty) != 0) {
				load_ins("$v0", m_table.mid_list[i].result);
			}
			fprintf(mips_file, "lw $ra,-4($fp)\n");
			fprintf(mips_file, "addi $sp,$fp,4\n");
			fprintf(mips_file, "lw $fp,0($fp)\n");
			fprintf(mips_file, "jr $ra\n");
			break;
		}
		case 31: {
			if (strcmp(m_table.mid_list[i].src1, mid_int) == 0) {
				fprintf(mips_file, "li $v0,5\n");
				fprintf(mips_file, "syscall\n");
				fprintf(mips_file, "move $t0,$v0\n");
				store_ins("$t0", m_table.mid_list[i].result);
			}
			else {
				fprintf(mips_file, "li $v0,12\n");
				fprintf(mips_file, "syscall\n");
				fprintf(mips_file, "move $t0,$v0\n");
				store_ins("$t0", m_table.mid_list[i].result);
			}
			break;
		}
		case 32: {
			if (strcmp(m_table.mid_list[i].src1, mid_str) == 0) {
				fprintf(mips_file, "la $a0,STR%d\n", i);
				fprintf(mips_file, "li $v0,4\n");
				fprintf(mips_file, "syscall\n");
				fprintf(mips_file, "li $a0,10\n");
				fprintf(mips_file, "li $v0,11\n");
				fprintf(mips_file, "syscall\n");
			}
			else {
				load_ins("$a0", m_table.mid_list[i].result);
				if (strcmp(m_table.mid_list[i].src1, mid_int) == 0) {
					fprintf(mips_file, "li $v0,1\n");
					fprintf(mips_file, "syscall\n");
					fprintf(mips_file, "li $a0,10\n");
					fprintf(mips_file, "li $v0,11\n");
					fprintf(mips_file, "syscall\n");
				}
				else if (strcmp(m_table.mid_list[i].src1, mid_char) == 0) {
					fprintf(mips_file, "li $v0,11\n");
					fprintf(mips_file, "syscall\n");
					fprintf(mips_file, "li $a0,10\n");
					fprintf(mips_file, "li $v0,11\n");
					fprintf(mips_file, "syscall\n");
				}
				else {
					fprintf(mips_file, "la $a0,STR%d\n", i);
					fprintf(mips_file, "li $v0,4\n");
					fprintf(mips_file, "syscall\n");
					fprintf(mips_file, "li $a0,10\n");
					fprintf(mips_file, "li $v0,11\n");
					fprintf(mips_file, "syscall\n");
				}
			}
			break;
		}
		case 33: {
			fprintf(mips_file, "%s:\n", m_table.mid_list[i].result);
			break;
		}
		case 34: {
			break;
		}
		case 35: {
			fprintf(mips_file, "li $v0,10\n");
			fprintf(mips_file, "syscall\n");
			break;
		}
		}
	}
}
int get_func_size(char name[]) {
	int i, func_i;
	for (i = 0; i < stable2.func_num; i++) {
		func_i = stable2.func_list[i];
		if (strcmp(stable2.list[func_i].name, name) == 0) {
			break;
		}
	}
	if (i == stable2.func_num) {
		return -1;
	}
	else {
		if (i < stable2.func_num - 1) {
			return stable2.list[stable2.func_list[i + 1] - 1].address;
		}
		else {
			return stable2.list[stable2.list_index - 1].address;
		}
	}
}
void append_mips_code() {
	init_mips2();
	fprintf(mips_file, ".data\n");
	data_process();
	append_new_table();
	fprintf(mips_file, ".text\n");
	fprintf(mips_file, "j main\n");
	mips_process();
}
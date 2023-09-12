#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"optimizer.h"
#include"mid_code.h"
#include"gra_ana.h"
extern FILE *mid_code_file_opt;
void init_opt() {
	f_block.func_index = 0;
}
void add_func_block() {
	f_block.func_list[f_block.func_index].start_num = m_table.mid_num;
	f_block.func_list[f_block.func_index].b_block_index = 0;
	f_block.func_index++;
}
void add_basic_block() {
	int i, j;
	for (i = 0; i < f_block.func_index; i++) {
		j = f_block.func_list[i].start_num;
		f_block.func_list[i].basic_blocks[f_block.func_list[i].b_block_index] = j;
		j++;
		f_block.func_list[i].b_block_index++;
		for (; j < m_table.mid_num; j++) {
			if (m_table.mid_list[j].op == 7 || m_table.mid_list[j].op == 8 || m_table.mid_list[j].op == 9)
				break;
			else if (m_table.mid_list[j].op == 33) {
				f_block.func_list[i].basic_blocks[f_block.func_list[i].b_block_index] = j;
				f_block.func_list[i].b_block_index++;
			}
			else if (m_table.mid_list[j].op == 25 || m_table.mid_list[j].op == 26 || m_table.mid_list[j].op == 27 || m_table.mid_list[j].op == 35 || m_table.mid_list[j].op == 34 || m_table.mid_list[j].op == 30) {
				if (!(m_table.mid_list[j+1].op == 7 || m_table.mid_list[j+1].op == 8 || m_table.mid_list[j+1].op == 9)) {
					if(j+1<m_table.mid_num){
						f_block.func_list[i].basic_blocks[f_block.func_list[i].b_block_index] = j+1;
						f_block.func_list[i].b_block_index++;
					}
				}
			}
		}
	}
}
void delete_same_block() {
	int i, j, k;
	for (i = 0; i < f_block.func_index; i++) {
		for (j = 0; j < f_block.func_list[i].b_block_index; j++) {
			if (j > 0 && f_block.func_list[i].basic_blocks[j] == f_block.func_list[i].basic_blocks[j - 1]) {
				for (k = j; k < f_block.func_list[i].b_block_index; k++) {
					f_block.func_list[i].basic_blocks[j] = f_block.func_list[i].basic_blocks[j + 1];
				}
				j--;
				f_block.func_list[i].b_block_index--;
			}
		}
	}
}
void instead_cal() {
	int i, j, k1, k2, k3, end;
	int src1, src2,use_flag;
	for (i = 0; i < f_block.func_index; i++) {
		for (j = 0; j < f_block.func_list[i].b_block_index; j++) {
			if (j + 1 == f_block.func_list[i].b_block_index) {
				if (i + 1 == f_block.func_index) {
					end = m_table.mid_num;
				}
				else {
					end = f_block.func_list[i + 1].basic_blocks[0];
				}
			}
			else {
				end = f_block.func_list[i].basic_blocks[j + 1];
			}
			for (k1 = f_block.func_list[i].basic_blocks[j]; k1 < end; k1++) {
				if (m_table.mid_list[k1].use == 0)
					continue;
				if (m_table.mid_list[k1].op >= 12 && m_table.mid_list[k1].op <= 15) {
					if (isdigit(m_table.mid_list[k1].src1[0]) && isdigit(m_table.mid_list[k1].src2[0])) {
						src1 = atoi(m_table.mid_list[k1].src1);
						src2 = atoi(m_table.mid_list[k1].src2);
						strcpy(m_table.mid_list[k1].src2, mid_empty);
						if (m_table.mid_list[k1].op == 12) {
							sprintf(m_table.mid_list[k1].src1, "%d", src1 + src2);
						}
						else if (m_table.mid_list[k1].op == 13) {
							sprintf(m_table.mid_list[k1].src1, "%d", src1 - src2);
						}
						else if (m_table.mid_list[k1].op == 14) {
							sprintf(m_table.mid_list[k1].src1, "%d", src1 * src2);
						}
						else{
							sprintf(m_table.mid_list[k1].src1, "%d", src1 / src2);
						}
						m_table.mid_list[k1].op = 16;
					}
				}
				if (m_table.mid_list[k1].op == 16) {
					use_flag = 0;
						k2 = k1;
						do {
							k2++;
							if (strcmp(m_table.mid_list[k1].result, m_table.mid_list[k2].src1)==0) {
								strcpy(m_table.mid_list[k2].src1, m_table.mid_list[k1].src1);
								use_flag = 1;
								break;
							}
							if (strcmp(m_table.mid_list[k1].result, m_table.mid_list[k2].src2)==0) {
								strcpy(m_table.mid_list[k2].src2, m_table.mid_list[k1].src1);
								use_flag = 1;
								break;
							}
						} while ((strcmp(m_table.mid_list[k1].result, m_table.mid_list[k2].result) != 0) && (strcmp(m_table.mid_list[k1].src1, m_table.mid_list[k2].result) != 0)&&(k2<end)&&(m_table.mid_list[k2].op!=29));
						if(use_flag==1&& m_table.mid_list[k1].result[0]=='$')
							m_table.mid_list[k1].use = 0;
				}
			}
		}
	}
}
void constant_merge() {
	int i, j, k1, k2, k3, end;
	for (i = 0; i < f_block.func_index; i++) {
		for (j = 0; j < f_block.func_list[i].b_block_index; j++) {
			if (j + 1 == f_block.func_list[i].b_block_index) {
				if (i + 1 == f_block.func_index) {
					end = m_table.mid_num;
				}
				else {
					end = f_block.func_list[i + 1].basic_blocks[0];
				}
			}
			else {
				end = f_block.func_list[i].basic_blocks[j + 1];
			}
			for (k1 = f_block.func_list[i].basic_blocks[j]; k1 < end; k1++) {
				if (m_table.mid_list[k1].use == 0)
					continue;
				if (!((m_table.mid_list[k1].op >= 12 && m_table.mid_list[k1].op <= 16) || (m_table.mid_list[k1].op == 29)))
					continue;
				for (k2 = k1 + 1; (k2 < end) && (strcmp(m_table.mid_list[k1].src1, m_table.mid_list[k2].result) != 0) && (strcmp(m_table.mid_list[k1].src2, m_table.mid_list[k2].result) != 0) && (m_table.mid_list[k2].op != 29); k2++) {
					if (m_table.mid_list[k2].use == 0)
						continue;
					if ((m_table.mid_list[k1].op == m_table.mid_list[k2].op) && (strcmp(m_table.mid_list[k1].src1, m_table.mid_list[k2].src1) == 0) && (strcmp(m_table.mid_list[k1].src2, m_table.mid_list[k2].src2) == 0) && m_table.mid_list[k2].result[0] == '$') {
						for (k3 = k2 + 1; (k3 < end) && (strcmp(m_table.mid_list[k2].result, m_table.mid_list[k3].result) != 0) && (strcmp(m_table.mid_list[k2].src1, m_table.mid_list[k3].result) != 0) && (strcmp(m_table.mid_list[k2].src2, m_table.mid_list[k3].result) != 0); k3++) {
							if (m_table.mid_list[k3].use == 0)
								continue;
							if (strcmp(m_table.mid_list[k3].src1, m_table.mid_list[k2].result) == 0) {
								strcpy(m_table.mid_list[k3].src1, m_table.mid_list[k1].result);
							}
							if (strcmp(m_table.mid_list[k3].src2, m_table.mid_list[k2].result) == 0) {
								strcpy(m_table.mid_list[k3].src2, m_table.mid_list[k1].result);
							}
						}
						m_table.mid_list[k2].use = 0;
					}
				}
			}
		}
	}
}
void condition_delete() {
	int i,j;
	int src1, src2;
	int result;
	int flag;
	for (i = 0; i < m_table.mid_num; i++) {
		if (m_table.mid_list[i].use == 0) {
			continue;
		}
		if ((m_table.mid_list[i].op == 26 || m_table.mid_list[i].op == 27)&& isdigit(m_table.mid_list[i-1].src1[0])&&isdigit(m_table.mid_list[i-1].src2[0])) {
			flag = 0;
			src1 = atoi(m_table.mid_list[i-1].src1);
			src2 = atoi(m_table.mid_list[i-1].src2);
			result = src1 - src2;
			switch(m_table.mid_list[i - 1].op) {
				case 19: {
					if (result == 0)
						flag = 1;
				}
				case 20: {
					if (result <= 0)
						flag = 1;
				}
				case 21: {
					if (result >= 0)
						flag = 1;
				}
				case 22: {
					if (result != 0)
						flag = 1;
				}
				case 23: {
					if (result < 0)
						flag = 1;
				}
				case 24: {
					if (result > 0)
						flag = 1;
				}
			}
			if (m_table.mid_list[i].op == 26&&flag==1) {
				m_table.mid_list[i].op = 25;
				j = i + 1;
				while ((m_table.mid_list[j].op != 33) && strcmp(m_table.mid_list[j].result, m_table.mid_list[i].result)) {
					m_table.mid_list[j].use = 0;
					j++;
				}
			}
			if (m_table.mid_list[i].op == 27 && flag == 0) {
				m_table.mid_list[i].op = 25;
				j = i + 1;
				while ((m_table.mid_list[j].op != 33) && strcmp(m_table.mid_list[j].result, m_table.mid_list[i].result)) {
					m_table.mid_list[j].use = 0;
					j++;
				}
			}
		}
	}
}
void optimizer() {
	add_basic_block();
	delete_same_block();
	instead_cal();
	condition_delete();
	print_mid_code(mid_code_file_opt);
}
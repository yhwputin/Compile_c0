#include<stdio.h>
#include<stdlib.h>
struct var_number{
	char var_num[100];
	int num;
};
struct func_var_num {
	struct var_number var_clist[64];
	int index;
	char func_name[100];
};
struct func_var_num f_c_var[128];

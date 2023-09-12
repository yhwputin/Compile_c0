#include<stdio.h>
#include<stdlib.h>
#define TABLE_MAX 1024
#define FUNC_MAX 1024
extern void init_stable();
struct tablenode {
	char name[100];
	int kind;//const = 0,var = 1,function = 2,para = 3
	int type;//int:1 char:2 void:0
	int value;	//常量：对应的值
	int size;	//数组：元素个数，函数：参数个数
	int address;	//相对于首地址的偏移
};
struct table {
	struct tablenode list[TABLE_MAX];
	int list_index;
	int func_num;
	int func_list[FUNC_MAX];
	int var_num[FUNC_MAX];
};
struct table stable,stable2;
extern void init();
extern void append_stable(char name[], int kind, int type, int value, int size, int address);
extern int index_stable(char name[], int kind);
extern int get_const_value(char name[]);
extern int get_func_para_num(char name[]);
extern int get_func_type(char name[]);
void print_stable();
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
extern char tep_func[100];
extern void append_mips_code();
extern void load_ins(char reg[], char name[]);
extern void store_ins(char reg[], char name[]);
extern int index_inf(char name[]);
extern void data_process();
extern void mips_process();
extern int get_func_size(char name[]);
extern void append_mips_code();


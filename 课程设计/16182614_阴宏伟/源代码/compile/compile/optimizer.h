#include<stdio.h>
#include<stdlib.h>
#define MAX_BASIC_BLOCK 256
#define MAX_FUNC_BLOCK 128
struct func_block {
	int start_num;
	int basic_blocks[MAX_BASIC_BLOCK];
	int b_block_index;
};
struct func_blocks {
	struct func_block func_list[MAX_FUNC_BLOCK];
	int func_index;
};
struct func_blocks f_block;
extern void add_func_block();
extern void add_basic_block();
extern void optimizer();
extern void init_opt();
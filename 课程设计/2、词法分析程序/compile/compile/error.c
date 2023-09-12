#include<stdio.h>
#include<stdlib.h>
extern FILE * compile_file;
extern FILE * lexana_file;
void error(int eop,int li_num) {
	switch (eop) {
	case 0: {
		printf("Can not open this file!\n");
		fprintf(lexana_file, "Can not open this file!\n");
		break;
	}
	case 1: {
		printf("Line %d:The first digit of the number cannot be 0!\n", li_num);
		fprintf(lexana_file, "Line %d:The first digit of the number cannot be 0!\n", li_num);
		break;
	}
	case 2: {
		printf("Line %d:Invalid character is decleared\n", li_num);
		fprintf(lexana_file, "Line %d:Invalid character is decleared\n", li_num);
		break;
	}
	case 3: {
		printf("Line %d:Invalid character appear in file\n", li_num);
		fprintf(lexana_file, "Line %d:Invalid character appear in file\n", li_num);
		break;
	}
	case 4: {
		printf("Line %d:Single quotes are not matched\n", li_num);
		fprintf(lexana_file, "Line %d:Single quotes are not matched\n", li_num);
		break;
	}
	case 5: {
		printf("Line %d:Double quotes are not matched\n", li_num);
		fprintf(lexana_file, "Line %d:Double quotes are not matched\n", li_num);
		break;
	}
	}
}
#include<stdio.h>
#include<stdlib.h>
extern FILE *error_file;		
void error(int eop,int li_num) {
	switch (eop) {
	case 0: {
		printf("Can not open this file!\n");
		fprintf(error_file, "Can not open this file!\n");
		break;
	}
	case 1: {
		printf("Line %d: The first digit of the number cannot be 0!\n", li_num);
		fprintf(error_file, "Line %d: The first digit of the number cannot be 0!\n", li_num);
		break;
	}
	case 2: {
		printf("Line %d: Invalid character is decleared!\n", li_num);
		fprintf(error_file, "Line %d: Invalid character is decleared!\n", li_num);
		break;
	}
	case 3: {
		printf("Line %d: Invalid character appear in file!\n", li_num);
		fprintf(error_file, "Line %d: Invalid character appear in file!\n", li_num);
		break;
	}
	case 4: {
		printf("Line %d: Single quotes are not matched!\n", li_num);
		fprintf(error_file, "Line %d: Single quotes are not matched!\n", li_num);
		break;
	}
	case 5: {
		printf("Line %d: Double quotes are not matched!\n", li_num);
		fprintf(error_file, "Line %d: Double quotes are not matched!\n", li_num);
		break;
	}
	case 6: {
		printf("Line %d: A symbol that does not belong to a character!\n", li_num);
		fprintf(error_file, "Line %d: A symbol that does not belong to a character!\n", li_num);
		break;
	}
	case 7: {
		printf("Line %d: A symbol that does not belong to a integer!\n", li_num);
		fprintf(error_file, "Line %d: A symbol that does not belong to a integer!\n", li_num);
		break;
	}
	case 8: {
		printf("line %d: This place should be a semicolon!\n", li_num);
		fprintf(error_file, "line %d: This place should be a semicolon!\n", li_num);
		break;
	}
	case 9: {
		printf("line %d: This place should be a right big parenthese!\n", li_num);
		fprintf(error_file, "line %d: This place should be a right big parenthese!\n", li_num);
		break;
	}
	case 10: {
		printf("line %d: This place should be a identifier!\n", li_num);
		fprintf(error_file, "line %d: This place should be a identifier!\n", li_num);
		break;
	}
	case 11: {
		printf("Line %d: Variable declaration error!\n", li_num);
		fprintf(error_file, "Line %d: Variable declaration error!\n", li_num);
		break;
	}
	case 12: {
		printf("Line %d: Function declaration error\n", li_num);
		fprintf(error_file, "Line %d: Function declaration error!\n", li_num);
		break;
	}
	case 13: {
		printf("Line %d: Constant definition error!\n", li_num);
		fprintf(error_file, "Line %d: Constant definition error!\n", li_num);
		break;
	}
	case 14: {
		printf("Line %d: Assignment error in constant definition!\n", li_num);
		fprintf(error_file, "Line %d: Assignment error in constant definition!\n", li_num);
		break;
	}
	case 15: {
		printf("Line %d: This place should be a right bracket!\n", li_num);
		fprintf(error_file, "Line %d: This place should be a right bracket!\n", li_num);
		break;
	}
	case 16: {
		printf("Line %d: When defining an array, the number of elements is 0!\n", li_num);
		fprintf(error_file, "Line %d: When defining an array, the number of elements is 0!\n", li_num);
		break;
	}
	case 17: {
		printf("Line %d: Variable definition error!\n", li_num);
		fprintf(error_file, "Line %d: Variable definition error!\n", li_num);
		break;
	}
	case 18: {
		printf("Line %d: This place should be a left big parenthese!\n", li_num);
		fprintf(error_file, "Line %d: This place should be a left big parenthese!\n", li_num);
		break;
	}
	case 19: {
		printf("Line %d: This place should be a right parenthese!\n", li_num);
		fprintf(error_file, "Line %d: This place should be a right parenthese!\n", li_num);
		break;
	}
	case 20: {
		printf("Line %d: This place should be a left parenthese!\n", li_num);
		fprintf(error_file, "Line %d: This place should be a left parenthese!\n", li_num);
		break;
	}
	case 21: {
		printf("Line %d: Parameter list error!\n", li_num);
		fprintf(error_file, "Line %d: Parameter list error!\n", li_num);
		break;
	}
	case 22: {
		printf("Line %d: Main function error!\n", li_num);
		fprintf(error_file, "Line %d: Main function error!\n", li_num);
		break;
	}
	case 23: {
		printf("Line %d: This place should be an assignment!\n", li_num);
		fprintf(error_file, "Line %d: This place should be an assignment!\n", li_num);
		break;
	}
	case 24: {
		printf("Line %d: Assign statement error!\n", li_num);
		fprintf(error_file, "Line %d: Assign statement error!\n", li_num);
		break;
	}
	case 25: {
		printf("Line %d: This place should be a colon!\n", li_num);
		fprintf(error_file, "Line %d: This place should be a colon!\n", li_num);
		break;
	}
	case 26: {
		printf("Line %d: This place should be a word \"case\"!\n", li_num);
		fprintf(error_file, "Line %d: This place should be a word \"case\"!\n", li_num);
		break;
	}
	case 27: {
		printf("Line %d: Default part error!\n", li_num);
		fprintf(error_file, "Line %d: Default part error!\n", li_num);
		break;
	}
	case 28: {
		printf("Line %d: Value function list error!\n", li_num);
		fprintf(error_file, "Line %d: Value function list error!\n", li_num);
		break;
	}
	case 29: {
		printf("Line %d: Return statement error!\n", li_num);
		fprintf(error_file, "Line %d: Return statement error!\n", li_num);
		break;
	}
	case 30: {
		printf("Line %d: Statement error!\n", li_num);
		fprintf(error_file, "Line %d: Statement error!\n", li_num);
		break;
	}
	case 31: {
		printf("Line %d: Factor error!\n", li_num);
		fprintf(error_file, "Line %d: Factor error!\n", li_num);
		break;
	}
	}
}
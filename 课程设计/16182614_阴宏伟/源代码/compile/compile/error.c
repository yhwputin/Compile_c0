#include<stdio.h>
#include<stdlib.h>
extern FILE *error_file;	
int e_flag = 0;
void error(int eop,int li_num) {
	e_flag = 1;
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
	case 32: {
		printf("Line %d: The symbol table is full!\n", li_num);
		fprintf(error_file, "Line %d: The symbol table is full!\n", li_num);
		break;
	}
	case 33: {
		printf("Line %d: The function has defined!\n", li_num);
		fprintf(error_file, "Line %d: The function has defined!\n", li_num);
		break;
	}
	case 34: {
		printf("Line %d: The variable or constant has defined!\n", li_num);
		fprintf(error_file, "Line %d: The variable or constant has defined!\n", li_num);
		break;
	}
	case 35: {
		printf("Line %d: The function is not defined!\n", li_num);
		fprintf(error_file, "Line %d: The function is not defined!\n", li_num);
		break;
	}
	case 36: {
		printf("Line %d: The identifier is not defined!\n", li_num);
		fprintf(error_file, "Line %d: The identifier is not defined!\n", li_num);
		break;
	}
	case 37: {
		printf("Line %d: The symbol after addition operator is invalid!\n", li_num);
		fprintf(error_file, "Line %d: The symbol after addition operator is invalid!\n", li_num);
		break;
	}
	case 38: {
		printf("Line %d: The mid code table is full!\n", li_num);
		fprintf(error_file, "Line %d: The mid code table is full!\n", li_num);
		break;
	}
	case 39: {
		printf("Line %d: Less return statement!\n", li_num);
		fprintf(error_file, "Line %d: Less return statement!\n", li_num);
		break;
	}
	case 40: {
		printf("Line %d: Invalid expression!\n", li_num);
		fprintf(error_file, "Line %d: Invalid expression!\n", li_num);
		break;
	}
	case 41: {
		printf("Line %d: The entire array is assigned!\n", li_num);
		fprintf(error_file, "Line %d: The entire array is assigned!\n", li_num);
		break;
	}
	case 42: {
		printf("Line %d: The constant is assigned!\n", li_num);
		fprintf(error_file, "Line %d: The constant is assigned!\n", li_num);
		break;
	}
	case 43: {
		printf("Line %d: The character can not be assigned by the integer!\n", li_num);
		fprintf(error_file, "Line %d: The character can not be assigned by the integer!\n", li_num);
		break;
	}
	case 44: {
		printf("Line %d: Invalid relationship operator!\n", li_num);
		fprintf(error_file, "Line %d: Invalid relationship operator!\n", li_num);
		break;
	}
	case 45: {
		printf("Line %d: The parameter is not equal with the function!\n", li_num);
		fprintf(error_file, "Line %d: The parameter is not equal with the function!\n", li_num);
		break;
	}
	case 46: {
		printf("Line %d: Read statement error!\n", li_num);
		fprintf(error_file, "Line %d: Read statement error!\n", li_num);
		break;
	}
	case 47: {
		printf("Line %d: The return value should be an integer or character!\n", li_num);
		fprintf(error_file, "Line %d: The return value should be an integer or character!\n", li_num);
		break;
	}
	case 48: {
		printf("Line %d: The return value should be void!\n", li_num);
		fprintf(error_file, "Line %d: The return value should be void!\n", li_num);
		break;
	}
	case 49: {
		printf("Line %d: The expression sides of realtionship operaotr should be same type!\n", li_num);
		fprintf(error_file, "Line %d: The expression sides of realtionship operaotr should be same type!\n", li_num);
		break;
	}
	case 50: {
		printf("Line %d: The parameter type is inconsistent with definition!\n", li_num);
		fprintf(error_file, "Line %d: The parameter type is inconsistent with definition!\n", li_num);
		break;
	}
	case 51: {
		printf("Line %d: The divisor is zero!\n", li_num);
		fprintf(error_file, "Line %d: The divisor is zero!\n", li_num);
		break;
	}
	}
}
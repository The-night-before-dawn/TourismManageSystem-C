#include "wrapper.h"

//处理字符串
void process_string(char *str, int length){
	for (int i = 0; i < length; i++){
		if (str[i] == '\n'){
			str[i] = '\0';
		}
	}
}

//计算数字
int calculate_string(char *str){
	int count = 0;
	int i = 0;

	for (; str[i] != '\0'; i++){
		if (str[i] <= '9' && str[i] >= '0'){
			count = count * 10 + (str[i] - '0');
		}
		else{
			count = -1;
			break;
		}
	}

	if (i == 0){
		count = -1;
	}

	return count;
}

//计算日期
void process_date_string(char *str, TIMESTAMP_STRUCT *date){
	int i = 0;
	date->year = 0;
	date->month = 0;
	date->day = 0;
	date->hour = 0;
	date->minute = 0;
	date->second = 0;
	date->fraction = 0;

	//计算年
	for (; str[i] != '-'; i++){
		if (str[i] <= '9' && str[i] >= '0'){
			date->year = (date->year) * 10 + (str[i] - '0');
		}
		else{
			date->year = 1970;
			date->month = 1;
			date->day = 1;
			return;
		}
	}
	//计算月
	for (i++; str[i] != '-'; i++){
		if (str[i] <= '9' && str[i] >= '0'){
			date->month = (date->month) * 10 + (str[i] - '0');
		}
		else{
			date->year = 1970;
			date->month = 1;
			date->day = 1;
			return;
		}
	}
	//计算天
	for (i++; str[i] != '\0'; i++){
		if (str[i] <= '9' && str[i] >= '0'){
			date->day = (date->day) * 10 + (str[i] - '0');
		}
		else{
			date->year = 1970;
			date->month = 1;
			date->day = 1;
			return;
		}
	}
}

//退出
void ending(){
	system("cls");

	printf("\n\n\n\n\n\n\n");
	printf("                                          |-------------------------------|\n");
	printf("                                          |  成   功   退   出   系   统  |\n");
	printf("                                          |-------------------------------|\n\n\n");
	printf("            --------------------------------------------------------------------------------------------\n\n\n");
	printf("                                              -> 结束：");
}

int write_choice(){
	int choice;
	char str[MAX_LENGTH];

	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	choice = calculate_string(str);

	return choice;
}

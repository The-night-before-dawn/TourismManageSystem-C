#include "wrapper.h"

//用户注册，注册成功为1，注册失败为0，退出-1
int sign_up(SQLHENV *dbhenv, SQLHDBC *dbhdbc, long consumer_level){
	/*定义句柄和变量*/
	SQLHSTMT dbhstmt;       //语句句柄
	SQLRETURN ret;          //返回值
	struct consumer consumer_temp;

	system("cls");
	title();
	printf("                                                     输入 E 退出\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                            [账号8位，密码不可超过15位]\n\n");

	//输入用户账号
	printf("\n                                                 > 用户账号：");
	fgets(consumer_temp.consumer_id, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(consumer_temp.consumer_id, MAX_LENGTH);
	
	if (strcmp(consumer_temp.consumer_id, "E") == 0)
		return -1;

	//输入用户密码
	printf("\n                                                 > 用户密码：");
	fgets(consumer_temp.pass_word, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(consumer_temp.pass_word, MAX_LENGTH);
	
	if (strcmp(consumer_temp.pass_word, "E") == 0)
		return -1;
	
	/*创建语句句柄，并初始化语句句柄*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*预编译带参数的SQL语句，并进行参数绑定*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"INSERT INTO Consumer VALUES(?, ?, ?);", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		ret = SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, consumer_temp.consumer_id, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, consumer_temp.pass_word, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 3, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &consumer_level, 0, NULL);
	}
	else{
		printf("参数绑定失败！\n");
		exit(0);
	}

	/*执行语句句柄中的SQL语句*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > 注册成功！\n");
	else
		printf("\n                                                 > 注册失败,用户名重复或格式不规范！\n");

	/*释放语句句柄*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");

	return 0;
}


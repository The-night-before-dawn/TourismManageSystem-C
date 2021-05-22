#include "wrapper.h"

void add_insure(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*定义句柄和变量*/
	SQLHSTMT dbhstmt;       //语句句柄
	SQLRETURN ret;          //返回值
	struct insure_node insure_temp;
	char str[MAX_LENGTH];
	char errmsg[256];
	long len;

	system("cls");
	title();
	printf("                                                     输入 E 退出\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                           [保险单号5位数字，否则进行截断]\n\n");

	//输入保险单号
	printf("\n                                                 > 保险  单号：");
	fgets(insure_temp.insure_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(insure_temp.insure_number, MAX_LENGTH);

	if (strcmp(insure_temp.insure_number, "E") == 0)
		return;

	//输入人均保险费
	printf("\n                                                 > 人均保险费：");
	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	insure_temp.avg_price = calculate_string(str);

	if (strcmp(str, "E") == 0)
		return;

	//输入保险期限 
	printf("\n                                                 > 保险  期限：");
	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	process_date_string(str, &insure_temp.deadline);

	if (strcmp(str, "E") == 0)
		return;

	/*创建语句句柄，并初始化语句句柄*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*预编译带参数的SQL语句，并进行参数绑定*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"INSERT INTO Insure VALUES(?, ?, ?);", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		ret = SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, insure_temp.insure_number, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, MAX_LENGTH, 0, &insure_temp.avg_price, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 3, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 23, 3, (SQLPOINTER)(&insure_temp.deadline), 0, NULL);
	}
	else{
		printf("参数绑定失败！\n");
		exit(0);
	}
	/*执行语句句柄中的SQL语句*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > 保险单添加成功！\n");
	else if (ret == SQL_NEED_DATA){
		printf("\n                                                 > SQL_NEED_DATA！\n");
		SQLError(*dbhenv, *dbhdbc, dbhstmt, NULL, NULL, errmsg, sizeof(errmsg), NULL);
		printf("\n                                                 > %s\n", errmsg);
	}
	else if (ret == SQL_ERROR){
		printf("\n                                                 > SQL_ERROR！\n");
		SQLError(*dbhenv, *dbhdbc, dbhstmt, NULL, NULL, errmsg, sizeof(errmsg), NULL);
		printf("\n                                                 > %s\n", errmsg);
	}
	else
		printf("\n                                                 > 保险单添加失败！\n");

	/*释放语句句柄*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void delete_insure(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*定义句柄和变量*/
	SQLHSTMT dbhstmt;       //语句句柄
	SQLRETURN ret;          //返回值
	struct insure_node insure_temp;

	system("cls");
	title();
	printf("                                                     输入 E 退出\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                                [保险单号5位数字]\n\n");

	//输入保险单号
	printf("\n                                                 > 保险单号：");
	fgets(insure_temp.insure_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(insure_temp.insure_number, MAX_LENGTH);

	if (strcmp(insure_temp.insure_number, "E") == 0)
		return;

	/*创建语句句柄，并初始化语句句柄*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*预编译带参数的SQL语句，并进行参数绑定*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"DELETE FROM Insure WHERE insure_number = ?;", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		ret = SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, insure_temp.insure_number, 0, NULL);
	}
	else{
		printf("参数绑定失败！\n");
		exit(0);
	}

	/*执行语句句柄中的SQL语句*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > 保险单删除成功！\n");
	else
		printf("\n                                                 > 保险单删除失败！\n");

	/*释放语句句柄*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void query_insure(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*定义句柄和变量*/
	SQLHSTMT dbhstmt;       //语句句柄
	SQLRETURN ret;          //返回值
	long len;
	struct insure_node insure_temp;

	system("cls");
	title();
	/*创建语句句柄，并初始化语句句柄*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*预编译带参数的SQL语句，并进行参数绑定*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"SELECT * FROM Insure;", SQL_NTS);
	ret = SQLBindCol(dbhstmt, 1, SQL_C_CHAR, insure_temp.insure_number, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 2, SQL_C_LONG, &insure_temp.avg_price, 0, &len);
	ret = SQLBindCol(dbhstmt, 3, SQL_C_TYPE_TIMESTAMP, &insure_temp.deadline, 0, &len);

	/*执行语句句柄中的SQL语句*/
	ret = SQLExecute(dbhstmt);

	/*获取结果*/
	ret = SQLFetch(dbhstmt);
	while (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		printf("             --------------------------------------------------------------------------------------------\n\n");
		printf("             #%s\t", insure_temp.insure_number);
		printf("%d\t", insure_temp.avg_price);
		printf("%d-%d-%d\n\n", insure_temp.deadline.year, insure_temp.deadline.month, insure_temp.deadline.day);
		ret = SQLFetch(dbhstmt);
	}

	/*释放语句句柄*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void insure(){
	int choice = 0;

	/*定义句柄和变量*/
	SQLHENV dbhenv;	     //环境句柄
	SQLHDBC dbhdbc;      //连接句柄
	SQLRETURN ret;       //返回值

	/*创建环境句柄，初始化环境句柄*/
	ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &dbhenv);
	ret = SQLSetEnvAttr(dbhenv, SQL_ATTR_ODBC_VERSION, (void *)SQL_OV_ODBC3, 0);

	/*创建连接句柄，与数据源建立连接*/
	ret = SQLAllocHandle(SQL_HANDLE_DBC, dbhenv, &dbhdbc);
	ret = SQLConnect(dbhdbc, (SQLCHAR *)"TCDB", SQL_NTS, (SQLCHAR *)"sa", SQL_NTS, (SQLCHAR *)"reply1988", SQL_NTS);
	if (!SQL_SUCCEEDED(ret)){  //判断是否连接成功的函数
		printf("连接出错！\n");
		exit(0);
	}

	do{
		insure_menu();
		if (choice >= 0 && choice <= 5)
			printf("                               -> 请选择要执行的功能: ");
		else
			printf("                               -> 输入有误，请正确选择要执行的功能: ");

		choice = write_choice();

		switch (choice){
		case 1:
			add_insure(&dbhenv, &dbhdbc);
			break;
		case 2:
			delete_insure(&dbhenv, &dbhdbc);
			break;
		case 3:
			query_insure(&dbhenv, &dbhdbc);
			break;
		case 0:
			break;
		}
	} while (choice);

	/*断开数据源和连接句柄的连接*/
	SQLDisconnect(dbhdbc);
	SQLFreeHandle(SQL_HANDLE_DBC, dbhdbc);

	/*释放环境句柄*/
	SQLFreeHandle(SQL_HANDLE_ENV, dbhenv);
}
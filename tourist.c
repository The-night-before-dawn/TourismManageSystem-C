#include "wrapper.h"

void add_tourist(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*定义句柄和变量*/
	SQLHSTMT dbhstmt;       //语句句柄
	SQLRETURN ret;          //返回值
	struct tourist_node tourist_temp;
	char str[MAX_LENGTH];
	char errmsg[256];

	system("cls");
	title();
	printf("                                                     输入 E 退出\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                                  [游客编号8位数字]\n\n");

	//游客编号
	printf("\n                                                 > 游客编号：");
	fgets(tourist_temp.tourist_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(tourist_temp.tourist_number, MAX_LENGTH);

	if (strcmp(tourist_temp.tourist_number, "E") == 0)
		return;

	//输入身份证号
	printf("\n                                                 > 身份证号：");
	fgets(tourist_temp.tourist_id, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(tourist_temp.tourist_id, MAX_LENGTH);

	if (strcmp(tourist_temp.tourist_id, "E") == 0)
		return;

	//输入姓名
	printf("\n                                                 > 姓    名：");
	fgets(tourist_temp.tourist_name, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(tourist_temp.tourist_name, MAX_LENGTH);

	if (strcmp(tourist_temp.tourist_name, "E") == 0)
		return;

	//输入性别
	printf("\n                                                 > 性    别：");
	fgets(tourist_temp.tourist_sex, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(tourist_temp.tourist_sex, MAX_LENGTH);

	if (strcmp(tourist_temp.tourist_sex, "E") == 0)
		return;

	//输入出生日期
	printf("\n                                                 > 出生日期：");
	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	process_date_string(str, &tourist_temp.tourist_birth);

	if (strcmp(str, "E") == 0)
		return;

	//输入住址
	printf("\n                                                 > 住    址：");
	fgets(tourist_temp.tourist_addr, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(tourist_temp.tourist_addr, MAX_LENGTH);

	if (strcmp(tourist_temp.tourist_addr, "E") == 0)
		return;

	//输入联系电话
	printf("\n                                                 > 联系电话：");
	fgets(tourist_temp.tourist_tel, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(tourist_temp.tourist_tel, MAX_LENGTH);

	if (strcmp(tourist_temp.tourist_tel, "E") == 0)
		return;

	//输入旅游路线
	printf("\n                                                 > 旅游路线：");
	fgets(tourist_temp.route_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(tourist_temp.route_number, MAX_LENGTH);

	if (strcmp(tourist_temp.route_number, "E") == 0)
		return;

	//输入出发时间
	printf("\n                                                 > 出发时间：");
	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	process_date_string(str, &tourist_temp.start_time);

	if (strcmp(str, "E") == 0)
		return;

	//输入回程时间
	printf("\n                                                 > 回程时间：");
	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	process_date_string(str, &tourist_temp.end_time);

	if (strcmp(str, "E") == 0)
		return;

	//所属用户
	strcpy(tourist_temp.consumer_number, consumer_node.consumer_id);

	/*创建语句句柄，并初始化语句句柄*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*预编译带参数的SQL语句，并进行参数绑定*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"INSERT INTO Tourist VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		SQLBindParameter(dbhstmt, 1,  SQL_PARAM_INPUT, SQL_C_CHAR,           SQL_CHAR,           MAX_LENGTH, 0, tourist_temp.tourist_number,  0, NULL);
		SQLBindParameter(dbhstmt, 2,  SQL_PARAM_INPUT, SQL_C_CHAR,           SQL_CHAR,           MAX_LENGTH, 0, tourist_temp.tourist_id,      0, NULL);
		SQLBindParameter(dbhstmt, 3,  SQL_PARAM_INPUT, SQL_C_CHAR,           SQL_CHAR,           MAX_LENGTH, 0, tourist_temp.tourist_name,    0, NULL);
		SQLBindParameter(dbhstmt, 4,  SQL_PARAM_INPUT, SQL_C_CHAR,           SQL_CHAR,           MAX_LENGTH, 0, tourist_temp.tourist_sex,     0, NULL);
		SQLBindParameter(dbhstmt, 5,  SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 23,         3, &tourist_temp.tourist_birth,  0, NULL);
		SQLBindParameter(dbhstmt, 6,  SQL_PARAM_INPUT, SQL_C_CHAR,           SQL_CHAR,           MAX_LENGTH, 0, tourist_temp.tourist_addr,    0, NULL);
		SQLBindParameter(dbhstmt, 7,  SQL_PARAM_INPUT, SQL_C_CHAR,           SQL_CHAR,           MAX_LENGTH, 0, tourist_temp.tourist_tel,     0, NULL);
		SQLBindParameter(dbhstmt, 8,  SQL_PARAM_INPUT, SQL_C_CHAR,           SQL_CHAR,           MAX_LENGTH, 0, tourist_temp.route_number,    0, NULL);
		SQLBindParameter(dbhstmt, 9, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 23,         3, &tourist_temp.start_time,     0, NULL);
		SQLBindParameter(dbhstmt, 10, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 23,         3, &tourist_temp.end_time,       0, NULL);
		SQLBindParameter(dbhstmt, 11, SQL_PARAM_INPUT, SQL_C_CHAR,           SQL_CHAR,           MAX_LENGTH, 0, tourist_temp.consumer_number, 0, NULL);
	}
	else{
		printf("参数绑定失败！\n");
		exit(0);
	}
	/*执行语句句柄中的SQL语句*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > 游客添加成功！\n");
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
		printf("\n                                                 > 游客添加失败！\n");

	/*释放语句句柄*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void delete_tourist(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*定义句柄和变量*/
	SQLHSTMT dbhstmt;       //语句句柄
	SQLRETURN ret;          //返回值
	struct tourist_node tourist_temp;

	system("cls");
	title();
	printf("                                                     输入 E 退出\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                                 [游客编号8位数字]\n\n");

	//输入游客编号
	printf("\n                                                 > 游客编号：");
	fgets(tourist_temp.tourist_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(tourist_temp.tourist_number, MAX_LENGTH);

	if (strcmp(tourist_temp.tourist_number, "E") == 0)
		return;

	/*创建语句句柄，并初始化语句句柄*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*预编译带参数的SQL语句，并进行参数绑定*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"DELETE FROM Tourist WHERE tourist_number = ?;", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		ret = SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, tourist_temp.tourist_number, 0, NULL);
	}
	else{
		printf("参数绑定失败！\n");
		exit(0);
	}

	/*执行语句句柄中的SQL语句*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > 游客删除成功！\n");
	else
		printf("\n                                                 > 游客删除失败！\n");

	/*释放语句句柄*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

//查询游客信息
void query_tourist(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*定义句柄和变量*/
	SQLHSTMT dbhstmt;       //语句句柄
	SQLRETURN ret;          //返回值
	struct tourist_node tourist_temp;
	char tourist_number[MAX_LENGTH];

	system("cls");
	title();

	/*创建语句句柄，并初始化语句句柄*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*预编译带参数的SQL语句，并进行参数绑定*/
	SQLPrepare(dbhstmt, (SQLCHAR *)"SELECT * FROM Tourist", SQL_NTS);
	SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, tourist_number, 0, NULL);
	SQLBindCol(dbhstmt, 1,  SQL_C_CHAR,           tourist_temp.tourist_number,  MAX_LENGTH, NULL);
	SQLBindCol(dbhstmt, 2,  SQL_C_CHAR,           tourist_temp.tourist_id,      MAX_LENGTH, NULL);
	SQLBindCol(dbhstmt, 3,  SQL_C_CHAR,           tourist_temp.tourist_name,    MAX_LENGTH, NULL);
	SQLBindCol(dbhstmt, 4,  SQL_C_CHAR,           tourist_temp.tourist_sex,     MAX_LENGTH, NULL);
	SQLBindCol(dbhstmt, 5,  SQL_C_TYPE_TIMESTAMP, &tourist_temp.tourist_birth,  0,          NULL);
	SQLBindCol(dbhstmt, 6,  SQL_C_CHAR,           tourist_temp.tourist_addr,    MAX_LENGTH, NULL);
	SQLBindCol(dbhstmt, 7,  SQL_C_CHAR,           tourist_temp.tourist_tel,     MAX_LENGTH, NULL);
	SQLBindCol(dbhstmt, 8,  SQL_C_CHAR,           tourist_temp.route_number,    MAX_LENGTH, NULL);
	SQLBindCol(dbhstmt, 9,  SQL_C_TYPE_TIMESTAMP, &tourist_temp.start_time,     0,          NULL);
	SQLBindCol(dbhstmt, 10, SQL_C_TYPE_TIMESTAMP, &tourist_temp.end_time,       0,          NULL);
	SQLBindCol(dbhstmt, 11, SQL_C_CHAR,           tourist_temp.consumer_number, MAX_LENGTH, NULL);

	/*执行语句句柄中的SQL语句*/
	ret = SQLExecute(dbhstmt);
	ret = SQLFetch(dbhstmt);
	while (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		printf("-----------------------------------------------------------------------------------------------------------------------\n\n");
		printf("#");
		printf("%s  ", tourist_temp.tourist_number);
		printf("%s  ", tourist_temp.tourist_id);
		printf("%s  ", tourist_temp.tourist_name);
		printf("%s  ", tourist_temp.tourist_sex);
		printf("%d-%d-%d\t", tourist_temp.tourist_birth.year, tourist_temp.tourist_birth.month, tourist_temp.tourist_birth.day);
		printf("%s  ", tourist_temp.tourist_addr);
		printf("%s  ", tourist_temp.tourist_tel);
		printf("%s  ", tourist_temp.route_number);
		printf("%d-%d-%d\t", tourist_temp.start_time.year, tourist_temp.start_time.month, tourist_temp.start_time.day);
		printf("%d-%d-%d\t", tourist_temp.end_time.year, tourist_temp.end_time.month, tourist_temp.end_time.day);
		printf("%s\n\n", tourist_temp.consumer_number);
		ret = SQLFetch(dbhstmt);
	}
	/*释放语句句柄*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);
	printf("\n                                                 > ");
	system("pause");
}

void tourist(){
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
		tourist_menu();
		if (choice >= 0 && choice <= 3)
			printf("                               -> 请选择要执行的功能: ");
		else
			printf("                               -> 输入有误，请正确选择要执行的功能: ");

		choice = write_choice();

		switch (choice){
		case 1:
			add_tourist(&dbhenv, &dbhdbc, 1);
			break;
		case 2:
			delete_tourist(&dbhenv, &dbhdbc);
			break;
		case 3:
			query_tourist(&dbhenv, &dbhdbc);
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
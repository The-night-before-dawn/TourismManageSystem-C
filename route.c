#include "wrapper.h"

void add_route(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*定义句柄和变量*/
	SQLHSTMT dbhstmt;       //语句句柄
	SQLRETURN ret;          //返回值
	struct route_node route_temp;
	char str[MAX_LENGTH];

	system("cls");
	title();
	printf("                                                     输入 E 退出\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                         [路线编号4位数字，否则进行截断]\n\n");

	//输入路线编号
	printf("\n                                                 > 路线编号：");
	fgets(route_temp.route_number, 5, stdin);
	fflush(stdin);
	process_string(route_temp.route_number, 5);

	if (strcmp(route_temp.route_number, "E") == 0)
		return;

	//输入起点
	printf("\n                                                 > 旅游起点：");
	fgets(route_temp.start_addr, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(route_temp.start_addr, MAX_LENGTH);

	if (strcmp(route_temp.start_addr, "E") == 0)
		return;

	//输入终点
	printf("\n                                                 > 旅游终点：");
	fgets(route_temp.end_addr, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(route_temp.end_addr, MAX_LENGTH);

	if (strcmp(route_temp.end_addr, "E") == 0)
		return;

	//输入旅游天数
	printf("\n                                                 > 旅游天数：");
	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	route_temp.days_count = calculate_string(str);

	if (strcmp(str, "E") == 0)
		return;

	//输入主要景点
	printf("\n                                                 > 主要景点：");
	fgets(route_temp.main_attraction, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(route_temp.main_attraction, MAX_LENGTH);

	if (strcmp(route_temp.main_attraction, "E") == 0)
		return;

	/*创建语句句柄，并初始化语句句柄*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*预编译带参数的SQL语句，并进行参数绑定*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"INSERT INTO Route VALUES(?, ?, ?, ?, ?);", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		ret = SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, route_temp.route_number, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, route_temp.start_addr, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, route_temp.end_addr, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 4, SQL_PARAM_INPUT, SQL_C_SHORT, SQL_SMALLINT, 0, 0, &route_temp.days_count, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, route_temp.main_attraction, 0, NULL);
	}
	else{
		printf("参数绑定失败！\n");
		exit(0);
	}

	/*执行语句句柄中的SQL语句*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > 路线添加成功！\n");
	else
		printf("\n                                                 > 路线添加失败！\n");

	/*释放语句句柄*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void delete_route(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*定义句柄和变量*/
	SQLHSTMT dbhstmt;       //语句句柄
	SQLRETURN ret;          //返回值
	struct route_node route_temp;

	system("cls");
	title();
	printf("                                                     输入 E 退出\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                         [路线编号4位数字，否则进行截断]\n\n");

	//输入路线编号
	printf("\n                                                 > 路线编号：");
	fgets(route_temp.route_number, 5, stdin);
	fflush(stdin);
	process_string(route_temp.route_number, 5);

	if (strcmp(route_temp.route_number, "E") == 0)
		return;

	/*创建语句句柄，并初始化语句句柄*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*预编译带参数的SQL语句，并进行参数绑定*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"DELETE FROM Route WHERE route_number = ?;", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		ret = SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, route_temp.route_number, 0, NULL);
	}
	else{
		printf("参数绑定失败！\n");
		exit(0);
	}

	/*执行语句句柄中的SQL语句*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > 路线删除成功！\n");
	else
		printf("\n                                                 > 路线删除失败！\n");

	/*释放语句句柄*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void query_route(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*定义句柄和变量*/
	SQLHSTMT dbhstmt;       //语句句柄
	SQLRETURN ret;          //返回值
	long len;
	struct route_node route_temp;

	system("cls");
	title();
	/*创建语句句柄，并初始化语句句柄*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*预编译带参数的SQL语句，并进行参数绑定*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"SELECT * FROM Route;", SQL_NTS);
	ret = SQLBindCol(dbhstmt, 1, SQL_C_CHAR, route_temp.route_number, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 2, SQL_C_CHAR, route_temp.start_addr, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 3, SQL_C_CHAR, route_temp.end_addr, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 4, SQL_C_SHORT, &route_temp.days_count, 0, &len);
	ret = SQLBindCol(dbhstmt, 5, SQL_C_CHAR, route_temp.main_attraction, MAX_LENGTH, &len);

	/*执行语句句柄中的SQL语句*/
	ret = SQLExecute(dbhstmt);

	/*获取结果*/
	ret = SQLFetch(dbhstmt);
	while (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		printf("             --------------------------------------------------------------------------------------------\n\n");
		printf("             #%s\t%s\t%s\t%d\t%s\n\n", route_temp.route_number, route_temp.start_addr, route_temp.end_addr, route_temp.days_count, route_temp.main_attraction);
		ret = SQLFetch(dbhstmt);
	}

	/*释放语句句柄*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void route(){
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
		route_menu();
		if (choice >= 0 && choice <= 3)
			printf("                               -> 请选择要执行的功能: ");
		else
			printf("                               -> 输入有误，请正确选择要执行的功能: ");

		choice = write_choice();

		switch (choice){
			case 1:
				add_route(&dbhenv, &dbhdbc);
				break;
			case 2:
				delete_route(&dbhenv, &dbhdbc);
				break;
			case 3:
				query_route(&dbhenv, &dbhdbc);
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
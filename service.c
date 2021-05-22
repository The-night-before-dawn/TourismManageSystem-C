#include "wrapper.h"

void add_service(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*定义句柄和变量*/
	SQLHSTMT dbhstmt;       //语句句柄
	SQLRETURN ret;          //返回值
	struct service_node service_temp;
	char str[MAX_LENGTH];
	char errmsg[256];
	long len;

	system("cls");
	title();
	printf("                                                     输入 E 退出\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                           [班次编号5位数字，否则进行截断]\n\n");

	//输入路线编号
	printf("\n                                                 > 班次编号：");
	fgets(service_temp.service_number, 6, stdin);
	fflush(stdin);
	process_string(service_temp.service_number, 6);

	if (strcmp(service_temp.service_number, "E") == 0)
		return;

	//输入起点
	printf("\n                                                 > 出发日期：");
	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	process_date_string(str, &service_temp.start_time);

	if (strcmp(str, "E") == 0)
		return;

	//输入终点
	printf("\n                                                 > 回程日期：");
	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	process_date_string(str, &service_temp.end_time);

	if (strcmp(str, "E") == 0)
		return;

	//输入旅游标准
	printf("\n                                                 > 旅游标准：");
	fgets(service_temp.travel_standard, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(service_temp.travel_standard, MAX_LENGTH);

	if (strcmp(service_temp.travel_standard, "E") == 0)
		return;

	//输入报价
	printf("\n                                                 > 报    价：");
	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	service_temp.price = calculate_string(str);

	if (strcmp(str, "E") == 0)
		return;

	//输入折扣率
	printf("\n                                                 > 折 扣 率：");
	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	service_temp.discount = calculate_string(str);

	if (strcmp(str, "E") == 0)
		return;

	/*创建语句句柄，并初始化语句句柄*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*预编译带参数的SQL语句，并进行参数绑定*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"INSERT INTO Service VALUES(?, ?, ?, ?, ?, ?);", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		ret = SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, service_temp.service_number, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 2, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 23, 3, (SQLPOINTER)(&service_temp.start_time), 0, NULL);
		ret = SQLBindParameter(dbhstmt, 3, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 23, 3, (SQLPOINTER)(&service_temp.end_time), 0, NULL);
		ret = SQLBindParameter(dbhstmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, service_temp.travel_standard, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 5, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &service_temp.price, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 6, SQL_PARAM_INPUT, SQL_C_SHORT, SQL_SMALLINT, 0, 0, &service_temp.discount, 0, NULL);
	}
	else{
		printf("参数绑定失败！\n");
		exit(0);
	}
	/*执行语句句柄中的SQL语句*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > 班次添加成功！\n");
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
		printf("\n                                                 > 班次添加失败！\n");

	/*释放语句句柄*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void delete_service(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*定义句柄和变量*/
	SQLHSTMT dbhstmt;       //语句句柄
	SQLRETURN ret;          //返回值
	struct service_node service_temp;

	system("cls");
	title();
	printf("                                                     输入 E 退出\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                           [班次编号5位数字，否则进行截断]\n\n");

	//输入班次编号
	printf("\n                                                 > 班次编号：");
	fgets(service_temp.service_number, 6, stdin);
	fflush(stdin);
	process_string(service_temp.service_number, 6);

	if (strcmp(service_temp.service_number, "E") == 0)
		return;

	/*创建语句句柄，并初始化语句句柄*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*预编译带参数的SQL语句，并进行参数绑定*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"DELETE FROM Service WHERE service_number = ?;", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		ret = SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, service_temp.service_number, 0, NULL);
	}
	else{
		printf("参数绑定失败！\n");
		exit(0);
	}

	/*执行语句句柄中的SQL语句*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > 班次删除成功！\n");
	else
		printf("\n                                                 > 班次删除失败！\n");

	/*释放语句句柄*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void query_service(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*定义句柄和变量*/
	SQLHSTMT dbhstmt;       //语句句柄
	SQLRETURN ret;          //返回值
	long len;
	struct service_node service_temp;

	system("cls");
	title();
	/*创建语句句柄，并初始化语句句柄*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*预编译带参数的SQL语句，并进行参数绑定*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"SELECT * FROM Service;", SQL_NTS);
	ret = SQLBindCol(dbhstmt, 1, SQL_C_CHAR, service_temp.service_number, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 2, SQL_C_TYPE_TIMESTAMP, &service_temp.start_time, 0, &len);
	ret = SQLBindCol(dbhstmt, 3, SQL_C_TYPE_TIMESTAMP, &service_temp.end_time, 0, &len);
	ret = SQLBindCol(dbhstmt, 4, SQL_C_CHAR, service_temp.travel_standard, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 5, SQL_C_LONG, &service_temp.price, 0, &len);
	ret = SQLBindCol(dbhstmt, 6, SQL_C_SHORT, &service_temp.discount, 0, &len);

	/*执行语句句柄中的SQL语句*/
	ret = SQLExecute(dbhstmt);

	/*获取结果*/
	ret = SQLFetch(dbhstmt);
	while (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		printf("             --------------------------------------------------------------------------------------------\n\n");
		printf("             #%s\t", service_temp.service_number);
		printf("%d-%d-%d\t", service_temp.start_time.year, service_temp.start_time.month, service_temp.start_time.day);
		printf("%d-%d-%d\t", service_temp.end_time.year, service_temp.end_time.month, service_temp.end_time.day);
		printf("%s\t", service_temp.travel_standard);
		printf("%d\t", service_temp.price);
		printf("%d\n\n", service_temp.discount);
		ret = SQLFetch(dbhstmt);
	}

	/*释放语句句柄*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void service(){
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
		service_menu();
		if (choice >= 0 && choice <= 3)
			printf("                               -> 请选择要执行的功能: ");
		else
			printf("                               -> 输入有误，请正确选择要执行的功能: ");

		choice = write_choice();

		switch (choice){
		case 1:
			add_service(&dbhenv, &dbhdbc);
			break;
		case 2:
			delete_service(&dbhenv, &dbhdbc);
			break;
		case 3:
			query_service(&dbhenv, &dbhdbc);
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
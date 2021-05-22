#include "wrapper.h"

//申请旅游
void apply_for_travel(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
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
		SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, tourist_temp.tourist_number, 0, NULL);
		SQLBindParameter(dbhstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, tourist_temp.tourist_id, 0, NULL);
		SQLBindParameter(dbhstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, tourist_temp.tourist_name, 0, NULL);
		SQLBindParameter(dbhstmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, tourist_temp.tourist_sex, 0, NULL);
		SQLBindParameter(dbhstmt, 5, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 23, 3, &tourist_temp.tourist_birth, 0, NULL);
		SQLBindParameter(dbhstmt, 6, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, tourist_temp.tourist_addr, 0, NULL);
		SQLBindParameter(dbhstmt, 7, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, tourist_temp.tourist_tel, 0, NULL);
		SQLBindParameter(dbhstmt, 8, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, tourist_temp.route_number, 0, NULL);
		SQLBindParameter(dbhstmt, 9, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 23, 3, &tourist_temp.start_time, 0, NULL);
		SQLBindParameter(dbhstmt, 10, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 23, 3, &tourist_temp.end_time, 0, NULL);
		SQLBindParameter(dbhstmt, 11, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, tourist_temp.consumer_number, 0, NULL);
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

//申请结果
void apply_for_result(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*定义句柄和变量*/
	SQLHSTMT dbhstmt;      //语句句柄
	SQLRETURN ret;          //返回值
	struct tourist_node tourist_temp;
	char str[MAX_LENGTH];
	char errmsg[256];

	system("cls");
	title();
	/*创建语句句柄，并初始化语句句柄*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*预编译带参数的SQL语句，并进行参数绑定*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"SELECT * FROM Tourist WHERE consumer_id = ?;", SQL_NTS);
	SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, consumer_node.consumer_id, 0, NULL);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		ret = SQLBindCol(dbhstmt, 1, SQL_C_CHAR, tourist_temp.tourist_number, MAX_LENGTH, NULL);
		ret = SQLBindCol(dbhstmt, 2, SQL_C_CHAR, tourist_temp.tourist_id, MAX_LENGTH, NULL);
		ret = SQLBindCol(dbhstmt, 3, SQL_C_CHAR, tourist_temp.tourist_name, MAX_LENGTH, NULL);
		ret = SQLBindCol(dbhstmt, 4, SQL_C_CHAR, tourist_temp.tourist_sex, MAX_LENGTH, NULL);
		ret = SQLBindCol(dbhstmt, 5, SQL_C_TYPE_TIMESTAMP, &tourist_temp.tourist_birth, 0, NULL);
		ret = SQLBindCol(dbhstmt, 6, SQL_C_CHAR, tourist_temp.tourist_addr, MAX_LENGTH, NULL);
		ret = SQLBindCol(dbhstmt, 7, SQL_C_CHAR, tourist_temp.tourist_tel, MAX_LENGTH, NULL);
		ret = SQLBindCol(dbhstmt, 8, SQL_C_CHAR, tourist_temp.route_number, MAX_LENGTH, NULL);
		ret = SQLBindCol(dbhstmt, 9, SQL_C_TYPE_TIMESTAMP, &tourist_temp.start_time, 0, NULL);
		ret = SQLBindCol(dbhstmt, 10, SQL_C_TYPE_TIMESTAMP, &tourist_temp.end_time, 0, NULL);
		ret = SQLBindCol(dbhstmt, 11, SQL_C_CHAR, tourist_temp.consumer_number, MAX_LENGTH, NULL);
	}
	else{
		printf("参数绑定失败！\n");
		exit(0);
	}


	ret = SQLExecute(dbhstmt);
	ret = SQLFetch(dbhstmt);
	while (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		printf("-----------------------------------------------------------------------------------------------------------------------\n\n");
		printf(" #");
		printf("%s ", tourist_temp.tourist_number);
		printf("%s ", tourist_temp.tourist_id);
		printf("%s ", tourist_temp.tourist_name);
		printf("%s ", tourist_temp.tourist_sex);
		printf("%d-%d-%d\t", tourist_temp.tourist_birth.year, tourist_temp.tourist_birth.month, tourist_temp.tourist_birth.day);
		printf("%s ", tourist_temp.tourist_addr);
		printf("%s ", tourist_temp.tourist_tel);
		printf("%s ", tourist_temp.route_number);
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
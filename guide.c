#include "wrapper.h"

void add_guide(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*定义句柄和变量*/
	SQLHSTMT dbhstmt;       //语句句柄
	SQLRETURN ret;          //返回值
	struct guide_node guide_temp;
	char str[MAX_LENGTH];
	char errmsg[256];

	system("cls");
	title();
	printf("                                                     输入 E 退出\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                                  [导游编号6位数字]\n\n");

	//输入导游编号
	printf("\n                                                 > 导游编号：");
	fgets(guide_temp.guide_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(guide_temp.guide_number, MAX_LENGTH);

	if (strcmp(guide_temp.guide_number, "E") == 0)
		return;

	//输入身份证号
	printf("\n                                                 > 身份证号：");
	fgets(guide_temp.guide_id, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(guide_temp.guide_id, MAX_LENGTH);

	if (strcmp(guide_temp.guide_id, "E") == 0)
		return;

	//输入姓名
	printf("\n                                                 > 姓    名：");
	fgets(guide_temp.guide_name, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(guide_temp.guide_name, MAX_LENGTH);

	if (strcmp(guide_temp.guide_name, "E") == 0)
		return;

	//输入性别 
	printf("\n                                                 > 性    别：");
	fgets(guide_temp.guide_sex, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(guide_temp.guide_sex, MAX_LENGTH);

	if (strcmp(guide_temp.guide_sex, "E") == 0)
		return;

	//输入出生日期
	printf("\n                                                 > 出生日期：");
	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	process_date_string(str, &guide_temp.guide_birth);

	if (strcmp(str, "E") == 0)
		return;

	//输入住址
	printf("\n                                                 > 住    址：");
	fgets(guide_temp.guide_addr, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(guide_temp.guide_addr, MAX_LENGTH);

	if (strcmp(guide_temp.guide_addr, "E") == 0)
		return;

	//输入联系电话
	printf("\n                                                 > 联系电话：");
	fgets(guide_temp.guide_tel, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(guide_temp.guide_tel, MAX_LENGTH);

	if (strcmp(guide_temp.guide_tel, "E") == 0)
		return;

	//输入语种
	printf("\n                                                 > 语    种：");
	fgets(guide_temp.guide_language, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(guide_temp.guide_language, MAX_LENGTH);

	if (strcmp(guide_temp.guide_language, "E") == 0)
		return;

	//输入等级
	printf("\n                                                 > 等    级：");
	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	guide_temp.guide_level = calculate_string(str);

	if (strcmp(str, "E") == 0)
		return;

	/*创建语句句柄，并初始化语句句柄*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*预编译带参数的SQL语句，并进行参数绑定*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"INSERT INTO Guide VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?);", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		ret = SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, guide_temp.guide_number, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, guide_temp.guide_id, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, guide_temp.guide_name, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, guide_temp.guide_sex, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 5, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 23, 3, &guide_temp.guide_birth, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 6, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, guide_temp.guide_addr, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 7, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, guide_temp.guide_tel, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 8, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, guide_temp.guide_language, 0, NULL);
		ret = SQLBindParameter(dbhstmt, 9, SQL_PARAM_INPUT, SQL_C_SHORT, SQL_SMALLINT, 0, 0, &guide_temp.guide_level, 0, NULL);
	}
	else{
		printf("参数绑定失败！\n");
		exit(0);
	}
	/*执行语句句柄中的SQL语句*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > 导游添加成功！\n");
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
		printf("\n                                                 > 导游添加失败！\n");

	/*释放语句句柄*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void delete_guide(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*定义句柄和变量*/
	SQLHSTMT dbhstmt;       //语句句柄
	SQLRETURN ret;          //返回值
	struct guide_node guide_temp;

	system("cls");
	title();
	printf("                                                     输入 E 退出\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                                [导游编号6位数字]\n\n");

	//输入导游编号
	printf("\n                                                 > 导游编号：");
	fgets(guide_temp.guide_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(guide_temp.guide_number, MAX_LENGTH);

	if (strcmp(guide_temp.guide_number, "E") == 0)
		return;

	/*创建语句句柄，并初始化语句句柄*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*预编译带参数的SQL语句，并进行参数绑定*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"DELETE FROM Guide WHERE guide_number = ?;", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		ret = SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, guide_temp.guide_number, 0, NULL);
	}
	else{
		printf("参数绑定失败！\n");
		exit(0);
	}

	/*执行语句句柄中的SQL语句*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > 导游删除成功！\n");
	else
		printf("\n                                                 > 导游删除失败！\n");

	/*释放语句句柄*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void query_guide(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*定义句柄和变量*/
	SQLHSTMT dbhstmt;       //语句句柄
	SQLRETURN ret;          //返回值
	long len;
	struct guide_node guide_temp;

	system("cls");
	title();
	/*创建语句句柄，并初始化语句句柄*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*预编译带参数的SQL语句，并进行参数绑定*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"SELECT * FROM Guide;", SQL_NTS);
	ret = SQLBindCol(dbhstmt, 1, SQL_C_CHAR, guide_temp.guide_number, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 2, SQL_C_CHAR, guide_temp.guide_id, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 3, SQL_C_CHAR, guide_temp.guide_name, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 4, SQL_C_CHAR, guide_temp.guide_sex, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 5, SQL_C_TYPE_TIMESTAMP, &guide_temp.guide_birth, 0, &len);
	ret = SQLBindCol(dbhstmt, 6, SQL_C_CHAR, guide_temp.guide_addr, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 7, SQL_C_CHAR, guide_temp.guide_tel, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 8, SQL_C_CHAR, guide_temp.guide_language, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 9, SQL_C_SHORT, &guide_temp.guide_level, MAX_LENGTH, &len);

	/*执行语句句柄中的SQL语句*/
	ret = SQLExecute(dbhstmt);

	/*获取结果*/
	ret = SQLFetch(dbhstmt);
	while (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		printf("             --------------------------------------------------------------------------------------------\n\n");
		printf("             #%s  ", guide_temp.guide_number);
		printf("%s  ", guide_temp.guide_id);
		printf("%s  ", guide_temp.guide_name);
		printf("%s  ", guide_temp.guide_sex);
		printf("%d-%d-%d\t", guide_temp.guide_birth.year, guide_temp.guide_birth.month, guide_temp.guide_birth.day);
		printf("%s  ", guide_temp.guide_tel);
		printf("%s  ", guide_temp.guide_language);
		printf("%d    ", guide_temp.guide_level);
		printf("%s\n\n", guide_temp.guide_addr);
		ret = SQLFetch(dbhstmt);
	}

	/*释放语句句柄*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void guide(){
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
		guide_menu();
		if (choice >= 0 && choice <= 3)
			printf("                               -> 请选择要执行的功能: ");
		else
			printf("                               -> 输入有误，请正确选择要执行的功能: ");

		choice = write_choice();

		switch (choice){
		case 1:
			add_guide(&dbhenv, &dbhdbc);
			break;
		case 2:
			delete_guide(&dbhenv, &dbhdbc);
			break;
		case 3:
			query_guide(&dbhenv, &dbhdbc);
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
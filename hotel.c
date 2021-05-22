#include "wrapper.h"

void add_hotel(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*定义句柄和变量*/
	SQLHSTMT dbhstmt;       //语句句柄
	SQLRETURN ret;          //返回值
	struct hotel_node hotel_temp;
	char str[MAX_LENGTH];
	char errmsg[256];
	long len;

	system("cls");
	title();
	printf("                                                     输入 E 退出\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                                [宾馆编号3位数字]\n\n");

	//输入宾馆编号
	printf("\n                                                 > 宾馆编号：");
	fgets(hotel_temp.hotel_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(hotel_temp.hotel_number, MAX_LENGTH);

	if (strcmp(hotel_temp.hotel_number, "E") == 0)
		return;

	//输入宾馆名称
	printf("\n                                                 > 宾馆名称：");
	fgets(hotel_temp.hotel_name, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(hotel_temp.hotel_name, MAX_LENGTH);

	if (strcmp(hotel_temp.hotel_name, "E") == 0)
		return;

	//输入所在城市
	printf("\n                                                 > 所在城市：");
	fgets(hotel_temp.hotel_city, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(hotel_temp.hotel_city, MAX_LENGTH);

	if (strcmp(hotel_temp.hotel_city, "E") == 0)
		return;

	//输入星级
	printf("\n                                                 > 宾馆星级：");
	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	hotel_temp.hotel_level = calculate_string(str);

	if (strcmp(str, "E") == 0)
		return;

	//输入标准房价
	printf("\n                                                 > 标准房价：");
	fgets(str, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(str, MAX_LENGTH);
	hotel_temp.hotel_price = calculate_string(str);

	if (strcmp(str, "E") == 0)
		return;

	//输入联系人
	printf("\n                                                 > 联 系 人：");
	fgets(hotel_temp.hotel_contact, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(hotel_temp.hotel_contact, MAX_LENGTH);

	if (strcmp(hotel_temp.hotel_contact, "E") == 0)
		return;

	//输入联系人职务
	printf("\n                                                 > 职    务：");
	fgets(hotel_temp.contact_duty, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(hotel_temp.contact_duty, MAX_LENGTH);

	if (strcmp(hotel_temp.contact_duty, "E") == 0)
		return;

	//输入联系地址
	printf("\n                                                 > 联系地址：");
	fgets(hotel_temp.hotel_addr, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(hotel_temp.hotel_addr, MAX_LENGTH);

	if (strcmp(hotel_temp.hotel_addr, "E") == 0)
		return;

	//输入联系电话
	printf("\n                                                 > 联系电话：");
	fgets(hotel_temp.hotel_tel, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(hotel_temp.hotel_tel, MAX_LENGTH);

	if (strcmp(hotel_temp.hotel_tel, "E") == 0)
		return;

	//输入传真
	printf("\n                                                 > 传    真：");
	fgets(hotel_temp.hotel_fax, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(hotel_temp.hotel_fax, MAX_LENGTH);;

	if (strcmp(hotel_temp.hotel_fax, "E") == 0)
		return;

	/*创建语句句柄，并初始化语句句柄*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*预编译带参数的SQL语句，并进行参数绑定*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"INSERT INTO Hotel VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?);", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		SQLBindParameter(dbhstmt, 1,  SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR,     MAX_LENGTH, 0, hotel_temp.hotel_number,  0, NULL);
		SQLBindParameter(dbhstmt, 2,  SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR,     MAX_LENGTH, 0, hotel_temp.hotel_name,    0, NULL);
		SQLBindParameter(dbhstmt, 3,  SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR,     MAX_LENGTH, 0, hotel_temp.hotel_city,    0, NULL);
		SQLBindParameter(dbhstmt, 4,  SQL_PARAM_INPUT, SQL_C_SHORT, SQL_SMALLINT, 0,          0, &hotel_temp.hotel_level,  0, NULL);
		SQLBindParameter(dbhstmt, 5,  SQL_PARAM_INPUT, SQL_C_LONG,  SQL_INTEGER,  0,          0, &hotel_temp.hotel_price,  0, NULL);
		SQLBindParameter(dbhstmt, 6,  SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR,     MAX_LENGTH, 0, hotel_temp.hotel_contact, 0, NULL);
		SQLBindParameter(dbhstmt, 7,  SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR,     MAX_LENGTH, 0, hotel_temp.contact_duty,  0, NULL);
		SQLBindParameter(dbhstmt, 8,  SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR,     MAX_LENGTH, 0, hotel_temp.hotel_addr,    0, NULL);
		SQLBindParameter(dbhstmt, 9,  SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR,     MAX_LENGTH, 0, hotel_temp.hotel_tel,     0, NULL);
		SQLBindParameter(dbhstmt, 10, SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR,     MAX_LENGTH, 0, hotel_temp.hotel_fax,     0, NULL);
	}
	else{
		printf("参数绑定失败！\n");
		exit(0);
	}
	/*执行语句句柄中的SQL语句*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > 宾馆添加成功！\n");
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
		printf("\n                                                 > 宾馆添加失败！\n");

	/*释放语句句柄*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void delete_hotel(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*定义句柄和变量*/
	SQLHSTMT dbhstmt;       //语句句柄
	SQLRETURN ret;          //返回值
	struct hotel_node hotel_temp;

	system("cls");
	title();
	printf("                                                     输入 E 退出\n");
	printf("                           ----------------------------------------------------------------\n\n");
	printf("\n                                                [宾馆编号3位数字]\n\n");

	//输入宾馆编号
	printf("\n                                                 > 宾馆编号：");
	fgets(hotel_temp.hotel_number, MAX_LENGTH, stdin);
	fflush(stdin);
	process_string(hotel_temp.hotel_number, MAX_LENGTH);

	if (strcmp(hotel_temp.hotel_number, "E") == 0)
		return;

	/*创建语句句柄，并初始化语句句柄*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*预编译带参数的SQL语句，并进行参数绑定*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"DELETE FROM Hotel WHERE hotel_number = ?;", SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		ret = SQLBindParameter(dbhstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, MAX_LENGTH, 0, hotel_temp.hotel_number, 0, NULL);
	}
	else{
		printf("参数绑定失败！\n");
		exit(0);
	}

	/*执行语句句柄中的SQL语句*/
	ret = SQLExecute(dbhstmt);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		printf("\n                                                 > 宾馆删除成功！\n");
	else
		printf("\n                                                 > 宾馆删除失败！\n");

	/*释放语句句柄*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void query_hotel(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	/*定义句柄和变量*/
	SQLHSTMT dbhstmt;       //语句句柄
	SQLRETURN ret;          //返回值
	long len;
	struct hotel_node hotel_temp;

	system("cls");
	title();
	/*创建语句句柄，并初始化语句句柄*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, *dbhdbc, &dbhstmt);
	ret = SQLSetStmtAttr(dbhstmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER)SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

	/*预编译带参数的SQL语句，并进行参数绑定*/
	ret = SQLPrepare(dbhstmt, (SQLCHAR *)"SELECT * FROM Hotel;", SQL_NTS);
	ret = SQLBindCol(dbhstmt, 1, SQL_C_CHAR, hotel_temp.hotel_number, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 2, SQL_C_CHAR, hotel_temp.hotel_name, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 3, SQL_C_CHAR, hotel_temp.hotel_city, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 4, SQL_C_SHORT, &hotel_temp.hotel_level, 0, &len);
	ret = SQLBindCol(dbhstmt, 5, SQL_C_LONG, &hotel_temp.hotel_price, 0, &len);
	ret = SQLBindCol(dbhstmt, 6, SQL_C_CHAR, hotel_temp.hotel_contact, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 7, SQL_C_CHAR, hotel_temp.contact_duty, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 8, SQL_C_CHAR, hotel_temp.hotel_addr, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 9, SQL_C_CHAR, hotel_temp.hotel_tel, MAX_LENGTH, &len);
	ret = SQLBindCol(dbhstmt, 10, SQL_C_CHAR, hotel_temp.hotel_fax, MAX_LENGTH, &len);

	/*执行语句句柄中的SQL语句*/
	ret = SQLExecute(dbhstmt);

	/*获取结果*/
	ret = SQLFetch(dbhstmt);
	while (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO){
		printf("             --------------------------------------------------------------------------------------------\n\n");
		printf("             #%s  ", hotel_temp.hotel_number);
		printf("%s", hotel_temp.hotel_name);
		printf("%s", hotel_temp.hotel_city);
		printf("%d   ", hotel_temp.hotel_level);
		printf("%d   ", hotel_temp.hotel_price);
		printf("%s", hotel_temp.hotel_contact);
		printf("%s   ", hotel_temp.hotel_tel);
		printf("%s", hotel_temp.contact_duty);	
		printf("%s   ", hotel_temp.hotel_fax);
		printf("%s\n\n", hotel_temp.hotel_addr);
		ret = SQLFetch(dbhstmt);
	}

	/*释放语句句柄*/
	SQLFreeHandle(SQL_HANDLE_STMT, dbhstmt);

	printf("\n                                                 > ");
	system("pause");
}

void hotel(){
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
		hotel_menu();
		if (choice >= 0 && choice <= 3)
			printf("                               -> 请选择要执行的功能: ");
		else
			printf("                               -> 输入有误，请正确选择要执行的功能: ");

		choice = write_choice();

		switch (choice){
		case 1:
			add_hotel(&dbhenv, &dbhdbc);
			break;
		case 2:
			delete_hotel(&dbhenv, &dbhdbc);
			break;
		case 3:
			query_hotel(&dbhenv, &dbhdbc);
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
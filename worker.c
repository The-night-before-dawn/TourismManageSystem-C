#include "wrapper.h"

void worker(SQLHENV *dbhenv, SQLHDBC *dbhdbc){
	int choice = 0;

	do{
		worker_menu();
		if (choice >= 0 && choice <= 8)
			printf("                               -> 请选择要执行的功能: ");
		else
			printf("                               -> 输入有误，请正确选择要执行的功能: ");

		choice = write_choice();

		switch (choice){
			case 1:
				route();
				break;
			case 2:
				service();
				break;
			case 3:
				team();
				break;
			case 4:
				hotel();
				break;
			case 5:
				guide();
				break;
			case 6:
				tourist();
				break;
			case 7:
				insure();
				break;
			case 8:
				route_service();
				break;
			case 9:
				service_team();
				break;
			case 10:
				team_tourist();
				break;
			case 11:
				insure_team();
				break;
			case 12:
				service_guide();
				break;
			case 13:
				hotel_service();
				break;
			case 14:
				sign_up(dbhenv, dbhdbc, 1);
				break;
			case 0:
				break;
		}
	} while (choice);
}
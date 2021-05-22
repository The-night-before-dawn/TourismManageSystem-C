#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <string.h>
#include "Def.h"

//menu
void title();

void menu();

void worker_menu();

void user_menu();

void route_menu();

void service_menu();

void team_menu();

void tourist_menu();

void insure_menu();

void hotel_menu();

void guide_menu();

//insure
void add_insure(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void delete_insure(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void query_insure(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void insure();

//tourist
void add_tourist(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void delete_tourist(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void query_tourist(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void tourist();

//team
void add_team(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void delete_team(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void query_team(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void team();

//service
void add_service(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void delete_service(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void query_service(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void service();

//route
void add_route(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void delete_route(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void query_route(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void route();

//hotel
void add_hotel(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void delete_hotel(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void query_hotel(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void hotel();

//guide 
void add_guide(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void delete_guide(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void query_guide(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void guide();

//route_service
void add_route_service(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void delete_route_service(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void query_route_service(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void route_service();

//service_team
void add_service_team(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void delete_service_team(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void query_service_team(SQLHENV *dbhenv, SQLHDBC *dbhdbc, struct service_node *service_temp);

void service_team();

//team_tourist
void add_team_tourist(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void delete_team_tourist(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void query_team_tourist(SQLHENV *dbhenv, SQLHDBC *dbhdbc, struct team_node *team);

void team_tourist();

//insure_team
void add_insure_team(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void delete_insure_team(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void query_insure_team(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void insure_team();

//service_guide
void fine_service_time(SQLHENV *dbhenv, SQLHDBC *dbhdbc, char *service_number, TIMESTAMP_STRUCT *start_time, TIMESTAMP_STRUCT *end_time);

void add_service_guide(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void delete_service_guide(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void query_service_guide(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void service_guide();

//hotel_service
void add_hotel_service(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void delete_hotel_service(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void query_hotel_service(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void hotel_service();

//apply for
void apply_for_travel(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

void apply_for_result(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

//sign in
int sign_in(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

//sign up
int sign_up(SQLHENV *dbhenv, SQLHDBC *dbhdbc, long consumer_level);

//lib
void process_string(char *str, int length);

int calculate_string(char *str);

void process_date_string(char *str, TIMESTAMP_STRUCT *date);

void ending();

//worker
void worker(SQLHENV *dbhenv, SQLHDBC *dbhdbc);

//user
void user();
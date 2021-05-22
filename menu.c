#include "wrapper.h"

//图标
void title(){
	printf("\n\n");
	printf("             -----------------------------|--------------------------------|-----------------------------\n");
	printf("             ***                          | 某  旅  行  社  旅  游  系  统 |                          ***\n");
	printf("             -----------------------------|--------------------------------|-----------------------------\n\n\n\n");
}

//功能菜单
void menu(){
	system("cls");   //该函数是清屏函数，是标准库自带的

	title();
	printf("                               ******************************************************               \n\n");
	printf("                                                   【1】 用户登陆                                   \n\n");
	printf("                                                   【2】 用户注册                                   \n\n");
	printf("                                                   【0】 退出系统                                   \n\n");
	printf("                               ******************************************************               \n\n\n");
}

//后台工作人员的功能菜单
void worker_menu(){
	system("cls");   //该函数是清屏函数，是标准库自带的

	title();
	printf("                               ******************************************************               \n\n");
	printf("                                                 【01】 旅 游  路 线                                \n\n");
	printf("                                                 【02】 旅 游  班 次                                \n\n");
	printf("                                                 【03】 旅   游   团                                \n\n");
	printf("                                                 【04】 宾        馆                                \n\n");
	printf("                                                 【05】 导        游                                \n\n");
	printf("                                                 【06】 游        客                                \n\n");
	printf("                                                 【07】 保        险                                \n\n");
	printf("                                                 【08】 路线 -- 班次                                \n\n");
	printf("                                                 【09】 班次 -- 旅团                                \n\n");
	printf("                                                 【10】 旅团 -- 游客                                \n\n");
	printf("                                                 【11】 保险 -- 旅团                                \n\n");
	printf("                                                 【12】 班次 -- 导游                                \n\n");
	printf("                                                 【13】 宾馆 -- 班次                                \n\n");
	printf("                                                 【14】 注        册                                \n\n");
	printf("                                                 【0 】 退        出                                \n\n");
	printf("                               ******************************************************               \n\n");
}

//游客用户的功能菜单
void user_menu(){
	system("cls");   //该函数是清屏函数，是标准库自带的

	title();
	printf("                               ******************************************************               \n\n");
	printf("                                                   【1】 查看路线                                   \n\n");
	printf("                                                   【2】 申请旅游                                   \n\n");
	printf("                                                   【3】 申请结果                                   \n\n");
	printf("                                                   【0】 退    出                                   \n\n");
	printf("                               ******************************************************               \n\n\n");
}

//路线的功能菜单
void route_menu(){
	system("cls");   //该函数是清屏函数，是标准库自带的

	title();
	printf("                               ******************************************************               \n\n");
	printf("                                                【1】 添  加  路  线                                \n\n");
	printf("                                                【2】 删  除  路  线                                \n\n");
	printf("                                                【3】 查  看  路  线                                \n\n");
	printf("                                                【0】 退          出                                \n\n");
	printf("                               ******************************************************               \n\n\n");
}

//班次的功能菜单
void service_menu(){
	system("cls");   //该函数是清屏函数，是标准库自带的

	title();
	printf("                               ******************************************************               \n\n");
	printf("                                                【1】 添  加  班  次                                \n\n");
	printf("                                                【2】 删  除  班  次                                \n\n");
	printf("                                                【3】 查  看  班  次                                \n\n");
	printf("                                                【0】 退          出                                \n\n");
	printf("                               ******************************************************               \n\n\n");
}

//旅游团的功能菜单
void team_menu(){
	system("cls");   //该函数是清屏函数，是标准库自带的

	title();
	printf("                               ******************************************************               \n\n");
	printf("                                                【1】 添 加 旅 游 团                                \n\n");
	printf("                                                【2】 删 除 旅 游 团                                \n\n");
	printf("                                                【3】 查 看 旅 游 团                                \n\n");
	printf("                                                【0】 退          出                                \n\n");
	printf("                               ******************************************************               \n\n\n");
}

//游客的功能菜单
void tourist_menu(){
	system("cls");   //该函数是清屏函数，是标准库自带的

	title();
	printf("                               ******************************************************               \n\n");
	printf("                                                【1】 添  加  游  客                                \n\n");
	printf("                                                【2】 删  除  游  客                                \n\n");
	printf("                                                【3】 查  看  游  客                                \n\n");
	printf("                                                【0】 退          出                                \n\n");
	printf("                               ******************************************************               \n\n\n");
}

//保险单的功能菜单
void insure_menu(){
	system("cls");   //该函数是清屏函数，是标准库自带的

	title();
	printf("                               ******************************************************               \n\n");
	printf("                                                【1】 添 加 保 险 单                                \n\n");
	printf("                                                【2】 删 除 保 险 单                                \n\n");
	printf("                                                【3】 查 看 保 险 单                                \n\n");
	printf("                                                【0】 退          出                                \n\n");
	printf("                               ******************************************************               \n\n\n");
}

//宾馆的功能菜单
void hotel_menu(){
	system("cls");   //该函数是清屏函数，是标准库自带的

	title();
	printf("                               ******************************************************               \n\n");
	printf("                                                【1】 添  加  宾  馆                                \n\n");
	printf("                                                【2】 删  除  宾  馆                                \n\n");
	printf("                                                【3】 查  看  宾  馆                                \n\n");
	printf("                                                【0】 退          出                                \n\n");
	printf("                               ******************************************************               \n\n\n");
}

//导游的功能菜单
void guide_menu(){
	system("cls");   //该函数是清屏函数，是标准库自带的

	title();
	printf("                               ******************************************************               \n\n");
	printf("                                                【1】 添  加  导  游                                \n\n");
	printf("                                                【2】 删  除  导  游                                \n\n");
	printf("                                                【3】 查  看  导  游                                \n\n");
	printf("                                                【0】 退          出                                \n\n");
	printf("                               ******************************************************               \n\n\n");
}

//路线-班次的功能菜单
void route_service_menu(){
	system("cls");   //该函数是清屏函数，是标准库自带的

	title();
	printf("                               ******************************************************               \n\n");
	printf("                                                【1】 添加 路线-班次                                \n\n");
	printf("                                                【2】 删除 路线-班次                                \n\n");
	printf("                                                【3】 查看 路线-班次                                \n\n");
	printf("                                                【0】 退          出                                \n\n");
	printf("                               ******************************************************               \n\n\n");
}

//班次-旅游团的功能菜单
void service_team_menu(){
	system("cls");   //该函数是清屏函数，是标准库自带的

	title();
	printf("                               ******************************************************               \n\n");
	printf("                                               【1】 添加 班次-旅游团                               \n\n");
	printf("                                               【2】 删除 班次-旅游团                               \n\n");
	printf("                                               【3】 查看 班次-旅游团                               \n\n");
	printf("                                               【0】 退            出                               \n\n");
	printf("                               ******************************************************               \n\n\n");
}

//旅游团-游客的功能菜单
void team_tourist_menu(){
	system("cls");   //该函数是清屏函数，是标准库自带的

	title();
	printf("                               ******************************************************               \n\n");
	printf("                                               【1】 添加 旅游团-游客                               \n\n");
	printf("                                               【2】 删除 旅游团-游客                               \n\n");
	printf("                                               【3】 查看 旅游团-游客                               \n\n");
	printf("                                               【0】 退            出                               \n\n");
	printf("                               ******************************************************               \n\n\n");
}

//保险单-旅游团 的功能菜单
void insure_team_menu(){
	system("cls");   //该函数是清屏函数，是标准库自带的

	title();
	printf("                               ******************************************************               \n\n");
	printf("                                              【1】 添加 保险单-旅游团                              \n\n");
	printf("                                              【2】 删除 保险单-旅游团                              \n\n");
	printf("                                              【3】 查看 保险单-旅游团                              \n\n");
	printf("                                              【0】 退              出                              \n\n");
	printf("                               ******************************************************               \n\n\n");
}

//班次-导游 的功能菜单
void service_guide_menu(){
	system("cls");   //该函数是清屏函数，是标准库自带的

	title();
	printf("                               ******************************************************               \n\n");
	printf("                                                【1】 添加 班次-导游                                \n\n");
	printf("                                                【2】 删除 班次-导游                                \n\n");
	printf("                                                【3】 查看 班次-导游                                \n\n");
	printf("                                                【0】 退          出                                \n\n");
	printf("                               ******************************************************               \n\n\n");
}

//宾馆-班次 的功能菜单
void hotel_service_menu(){
	system("cls");   //该函数是清屏函数，是标准库自带的

	title();
	printf("                               ******************************************************               \n\n");
	printf("                                                【1】 添加 宾馆-班次                                \n\n");
	printf("                                                【2】 删除 宾馆-班次                                \n\n");
	printf("                                                【3】 查看 宾馆-班次                                \n\n");
	printf("                                                【0】 退          出                                \n\n");
	printf("                               ******************************************************               \n\n\n");
}

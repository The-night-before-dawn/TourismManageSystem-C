#define MAX_LENGTH 100
struct consumer{
	char consumer_id[MAX_LENGTH];
	char pass_word[MAX_LENGTH];
};
struct consumer consumer_node;

struct route_node{
	char route_number[MAX_LENGTH];    //路线编号
	char start_addr[MAX_LENGTH];      //起点
	char end_addr[MAX_LENGTH];        //终点
	short days_count;                 //旅游天数
	char main_attraction[MAX_LENGTH]; //主要景点
};

struct service_node{
	char service_number[MAX_LENGTH];     //班次编号
	TIMESTAMP_STRUCT start_time;         //出发日期
	TIMESTAMP_STRUCT end_time;           //回程日期
	char travel_standard[MAX_LENGTH];    //旅游标准, 可选：会员、钻石、皇冠
	long price;                          //报价
	short discount;                      //折扣率
};

struct team_node{
	char team_number[MAX_LENGTH];    //团号
	char team_name[MAX_LENGTH];      //团名	
	short people_count;              //实际人数
	char team_contact[MAX_LENGTH];   //联系人
	char contact_addr[MAX_LENGTH];   //住址
	char contact_tel[MAX_LENGTH];    //联系电话
};

struct tourist_node{
	char tourist_number[MAX_LENGTH];     //游客编号
	char tourist_id[MAX_LENGTH];         //身份证号
	char tourist_name[MAX_LENGTH];       //姓名
	char tourist_sex[MAX_LENGTH];        //性别
	TIMESTAMP_STRUCT tourist_birth;      //出生日期
	char tourist_addr[MAX_LENGTH];       //住址
	char tourist_tel[MAX_LENGTH];        //联系电话
	char route_number[MAX_LENGTH];       //旅游路线, 允许空值
	TIMESTAMP_STRUCT start_time;         //出发时间
	TIMESTAMP_STRUCT end_time;           //回程时间
	char consumer_number[MAX_LENGTH];    //所属用户
};

struct insure_node{
	char insure_number[MAX_LENGTH];         //保险单号
	long avg_price;             //人均保险费
	TIMESTAMP_STRUCT deadline;  //保险期限
};

struct hotel_node{
	char hotel_number[MAX_LENGTH];      //宾馆编号
	char hotel_name[MAX_LENGTH];        //宾馆名称
	char hotel_city[MAX_LENGTH];        //所在城市
	short hotel_level;                  //星级
	long hotel_price;                   //标准房价
	char hotel_contact[MAX_LENGTH];     //联系人
	char contact_duty[MAX_LENGTH];      //联系人职务
	char hotel_addr[MAX_LENGTH];        //联系地址
	char hotel_tel[MAX_LENGTH];         //联系电话
	char hotel_fax[MAX_LENGTH];         //传真

};

struct guide_node{
	char guide_number[MAX_LENGTH];          //导游编号
	char guide_id[MAX_LENGTH];              //身份证号
	char guide_name[MAX_LENGTH];            //姓名
	char guide_sex[MAX_LENGTH];             //性别
	TIMESTAMP_STRUCT guide_birth;           //出生日期
	char guide_addr[MAX_LENGTH];            //住址
	char guide_tel[MAX_LENGTH];             //联系电话
	char guide_language[MAX_LENGTH];        //语种
	short guide_level;                      //等级
};
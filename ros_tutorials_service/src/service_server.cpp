#include "ros/ros.h" // ROS的基本头文件
#include "ros_tutorials_service/SrvTutorial.h" // SrvTutorial服务头文件
#define PLUS 1 // 加
#define MINUS 2 // 减
#define MULTIPLICATION 3 // 乘
#define DIVISION 4 // 除
int g_operator = PLUS;
// 当有服务请求时，会处理以下内容。
// 服务请求设置为req，服务响应设置为res。
bool calculation(ros_tutorials_service::SrvTutorial::Request &req, 
ros_tutorials_service::SrvTutorial::Response &res) {
	 // 根据g_operator参数值进行a和b的运算
	 // 计算后将结果保存到服务响应值中。
	switch(g_operator)
	 {
		case PLUS: 
			res.result = req.a + req.b; break; 
		case MINUS: 
			res.result = req.a - req.b; break; 
		case MULTIPLICATION: 
			res.result = req.a * req.b; break; 
		case DIVISION: 
			if(req.b == 0)
			 {
				res.result = 0; break; 
			 } 
			else
			 {
				res.result = req.a / req.b; break; 
			 } 
		default: 
			res.result = req.a + req.b; break;
	 } 
	 // 显示服务请求中使用的a和b值，以及相当于服务响应的result值。
	ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
	ROS_INFO("sending back response: [%ld]", (long int)res.result); 
	return true; 
} 
int main(int argc, char **argv) // 节点主函数
{
	ros::init(argc, argv, "service_server"); // 初始化节点名称
	ros::NodeHandle nh; // 声明节点句柄
	nh.setParam("calculation_method", PLUS); // 初始化参数
	 // 声明服务服务器，创建使用ros_tutorials_service功能包中的SrvTutorial服务文件的 
	 // 服务服务器service_server。服务名称是"ros_tutorial_srv" ， 
	 // 此服务器当收到服务请求时，会执行一个叫做calculation的函数。
	ros::ServiceServer ros_tutorial_service_server = nh.advertiseService("ros_tutorial_srv", 
	calculation); 
	ROS_INFO("ready srv server!");
	ros::Rate r(10); // 10hz
	while (1) 
	 { 
		 // 将运算符改为通过参数收到的值。
		nh.getParam("calculation_method", g_operator);
		ros::spinOnce(); // 后台函数处理进程
		r.sleep(); // 为了反复进入进程而添加的sleep（暂歇）函数
	 } 
	return 0; 
}

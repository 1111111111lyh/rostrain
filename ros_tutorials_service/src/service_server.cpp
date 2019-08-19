#include "ros/ros.h" // ROS的基本头文件
#include "ros_tutorials_service/SrvTutorial.h" // SrvTutorial服务头文件（构建后自动生成）
// 如果有服务请求，将执行以下处理
// 将服务请求设置为req，服务响应则设置为res。
bool calculation(ros_tutorials_service::SrvTutorial::Request &req,
ros_tutorials_service::SrvTutorial::Response &res) 
{
	 // 在收到服务请求时，将a和b的和保存在服务响应值中
	res.result = req.a + req.b;
	 // 显示服务请求中用到的a和b的值以及服务响应result值
	ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
	ROS_INFO("sending back response: %ld", (long int)res.result);
	return true; 
}
int main(int argc, char **argv) // 节点主函数
{
	ros::init(argc, argv, "service_server"); // 初始化节点名称
	ros::NodeHandle nh; // 声明节点句柄
	 // 声明服务服务器
	 // 声明利用ros_tutorials_service功能包的SrvTutorial服务文件的
	 // 服务服务器ros_tutorials_service_server
	 // 服务名称是ros_tutorial_srv，且当有服务请求时，执行calculation函数。
	ros::ServiceServer ros_tutorials_service_server = nh.advertiseService("ros_tutorial_srv", 
	calculation);
	ROS_INFO("ready srv server!");
	ros::spin(); // 等待服务请求
	return 0; 
}

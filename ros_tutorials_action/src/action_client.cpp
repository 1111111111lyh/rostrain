#include <ros/ros.h> // ROS的基本头文件
#include <actionlib/client/simple_action_client.h> // 动作库头文件
#include <actionlib/client/terminal_state.h> // 动作目标状态头文件
#include <ros_tutorials_action/FibonacciAction.h> // FibonacciAction动作头文件（构建后自动生成）
int main (int argc, char **argv) // 节点主函数
{
	ros::init(argc, argv, "action_client"); // 初始化节点名称
	 // 声明动作客户端（动作名称：ros_tutorial_action）
	actionlib::SimpleActionClient<ros_tutorials_action::FibonacciAction> ac("ros_tutorial_action", true);
	ROS_INFO("Waiting for action server to start.");
	ac.waitForServer(); // 等待动作服务器启动
	ROS_INFO("Action server started, sending goal.");
	ros_tutorials_action::FibonacciGoal goal; // 声明动作目标
	goal.order = 20; // 指定动作目标（进行20次斐波那契运算）
	ac.sendGoal(goal); // 发送动作目标
	 // 设置动作完成时间限制（这里设置为30秒）
	bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0));
	 // 在动作完成时限内收到动作结果值时
	if (finished_before_timeout)
	 {
		 // 获取动作目标状态值并将其显示在屏幕上
		actionlib::SimpleClientGoalState state = ac.getState();
		ROS_INFO("Action finished: %s",state.toString().c_str());
	 }
	else
	{
		ROS_INFO("Action did not finish before the time out."); // 超过了动作完成时限的情况
	}
	 //exit
	return 0; 
}

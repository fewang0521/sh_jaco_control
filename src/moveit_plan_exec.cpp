#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

#include <moveit_visual_tools/moveit_visual_tools.h>

int main(int argc, char** argv){
    
    ros::init(argc, argv, "moveit_plan_exec_node");
    //ros::NodeHandle node_handle("jaco");
    ros::AsyncSpinner spinner(1);
    spinner.start();

    
    static const std::string PLANNING_GROUP = "Arm";
    //moveit::planning_interface::MoveGroupInterface::Options option(PLANNING_GROUP);
    //option.node_handle_=node_handle;
    moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);
    
    moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
    ROS_INFO("Before get joint state");
    const robot_state::JointModelGroup* joint_model_group = move_group.
    getCurrentState()->getJointModelGroup(PLANNING_GROUP);
    ROS_INFO("After get joint state");
    namespace rvt =rviz_visual_tools;
    moveit_visual_tools::MoveItVisualTools visual_tools("jaco_0_baseA");
    visual_tools.deleteAllMarkers();

    visual_tools.loadRemoteControl();


    ROS_INFO_NAMED("tutorial", "Planning frame: %s", move_group.getPlanningFrame().c_str());
    ROS_INFO_NAMED("tutorial", "End effector link: %s", move_group.getEndEffectorLink().c_str());
    ROS_INFO_NAMED("tutorial", "Available Planning Groups:");
    std::copy(move_group.getJointModelGroupNames().begin(), move_group.getJointModelGroupNames().end(),
            std::ostream_iterator<std::string>(std::cout, ", "));

    geometry_msgs::Pose target_pose1;
    
    target_pose1.orientation.x = -0.458;
    target_pose1.orientation.y = -0.607;
    target_pose1.orientation.z = -0.161;
    target_pose1.orientation.w = 0.629;

    target_pose1.position.x = 0.404;
    target_pose1.position.y = 0.021;
    target_pose1.position.z = 0.483;
    move_group.setPoseTarget(target_pose1);
    move_group.setPlanningTime(10.0);
    move_group.setGoalPositionTolerance(10);
    move_group.setGoalOrientationTolerance(10);
    moveit::planning_interface::MoveGroupInterface::Plan my_plan;
    moveit::core::RobotStatePtr current_state = move_group.getCurrentState();
    std::vector<double> joint_group_positions;
    current_state->copyJointGroupPositions(joint_model_group, joint_group_positions);
    //for (std::vector<double>::iterator iter_=joint_group_positions.begin(); iter_!=joint_group_positions.end();++iter_){
     //   ROS_INFO("%d",*iter_);
    //}
    bool success = (move_group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);

    ROS_INFO_NAMED("tutorial", "Visualizing plan 1 (pose goal) %s", success ? "" : "FAILED");
    ROS_INFO_NAMED("tutorial", "Visualizing plan 1 as trajectory line");
    visual_tools.publishAxisLabeled(target_pose1, "pose1");
    visual_tools.publishTrajectoryLine(my_plan.trajectory_, joint_model_group);
    visual_tools.trigger();
    if (success){
        ROS_INFO("plan executed");
        move_group.execute(my_plan);
    }


}
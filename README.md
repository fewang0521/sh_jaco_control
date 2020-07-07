# sh_jaco_control
Package 설명 : KINOVA에서 제작한 Jaco Arm (6-DOF)을 Gazebo 환경에서의 제어하기 위해 제작한 controll package, https://github.com/JenniferBuehler/jaco-arm-pkgs/wiki 에서 이미 세팅된 gazebo 환경과 moveit, rviz를 이용

Project
1. Gripper controller
Moveit에서 제공하는 Grasp MSG를 사용하려면,  gripper interface를 로봇이 제공해야한다.
Gazebo에서는 gripper action용 controller를 따로 제공하지 않아서, controller를 제작하거나 Grasp msg를 사용하지 않고, 즉 moveit을 사용하지 않고 position controller등으로 구현을 해야한다.
후자를 선택하였고, 각 finger joint들이 제공하는 controller command interface에 한번에 msg를 전달하기 위해서,  새로운 msg를 정의하고 이를 받아서 각 command interface에 전달하도록 하는 publisher node를 제작하려고 한다.

user --->interface_topic ---> [target_node] ----> each controllers topic
각 축의 reference value를 담는 JacoGripperCommand라는 새로운 message를 정의하고, 이를 interface_topic에 전달하여 각각의 controller의 topic에 분배하는 node를 생성하는 concept으로 구현


2. End effector Move (Moveit API 사용)
moveit cpp interface를 이용하여, end effect의 coordinate와 orientation 정보를 입력하면 moveit에서 planning하고 execution하는 cpp를 구현



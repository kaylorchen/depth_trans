add_executable(depth_trans main.cpp)
ament_target_dependencies(depth_trans sensor_msgs rclcpp)
install(TARGETS
	depth_trans
	DESTINATION lib/${PROJECT_NAME}
)
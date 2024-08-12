project(tcp_server_main)

add_executable( ${PROJECT_NAME} 
	src/server_class_main.cpp
)

target_link_libraries(${PROJECT_NAME} tcp_server)



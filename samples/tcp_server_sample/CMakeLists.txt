cmake_minimum_required(VERSION  3.10)

project(tcp_server_sample)

add_executable( ${PROJECT_NAME} 
	src/server_main.cpp
)

target_link_libraries( ${PROJECT_NAME}
	ws2_32
)
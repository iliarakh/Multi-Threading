project(tcp_server_main)

add_library(${PROJECT_NAME} 
	"include/server.hpp"
	"src/server.cpp"
)

target_link_libraries( ${PROJECT_NAME}
	modules/tcp_server
)

add_executable( ${PROJECT_NAME} 
	src/server_class_main.cpp
)


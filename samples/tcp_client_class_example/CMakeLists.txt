project(tcp_client_main)

add_library(${PROJECT_NAME} 
	"include/client.hpp"
	"src/client.cpp"
)

target_link_libraries( ${PROJECT_NAME}
	modules/tcp_client
)

add_executable( ${PROJECT_NAME} 
	src/client_class_main.cpp
)


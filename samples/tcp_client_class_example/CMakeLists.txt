project(tcp_client_main)

add_executable( ${PROJECT_NAME} 
	src/client_class_main.cpp
)

target_link_libraries(${PROJECT_NAME} tcp_client)


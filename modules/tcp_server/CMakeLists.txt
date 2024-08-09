project(tcp_server)

add_library(${PROJECT_NAME} 
	"include/server.hpp"
	"src/server.cpp"
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries( ${PROJECT_NAME}
	ws2_32
)
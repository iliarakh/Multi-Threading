project(tcp_client)

add_library(${PROJECT_NAME} 
	"include/client.hpp"
	"src/client.cpp"
)

target_link_libraries( ${PROJECT_NAME}
	ws2_32
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


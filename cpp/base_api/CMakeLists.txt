project(base_api)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${LUAJIT_LINK_LIBRARIES})
project(sol)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${LUAJIT_LINK_LIBRARIES})
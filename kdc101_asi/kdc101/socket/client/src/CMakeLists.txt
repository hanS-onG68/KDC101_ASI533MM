# # 指定最低版本要求
# cmake_minimum_required(VERSION 3.10)

# # 设置项目名称
# project(client_src)

# 创建静态库而不是可执行文件
add_library(SOCKET_CLIENT STATIC ${CMAKE_CURRENT_SOURCE_DIR}/client.cpp)

target_include_directories(SOCKET_CLIENT PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include 
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../api/tlmc_func.h
)  # 使用 PUBLIC 让包含目录可传递

target_link_libraries(SOCKET_CLIENT  ws2_32)

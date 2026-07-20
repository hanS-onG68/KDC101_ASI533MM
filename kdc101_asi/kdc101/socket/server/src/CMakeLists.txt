# # 指定最低版本要求
# cmake_minimum_required(VERSION 3.10)

# # 设置项目名称
# project(server_src)

# 创建静态库而不是可执行文件
add_library(SOCKET_SERVER STATIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/server.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../api/src/tlmc_func.cpp
)

target_link_libraries(SOCKET_SERVER 
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../sdk/libs/tlmc_xa_native.dll
    ws2_32
    ZWO_SRC
)

target_include_directories(SOCKET_SERVER PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../sdk/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../api/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../asi/sdk/inclde
)  # 使用 PUBLIC 让包含目录可传递

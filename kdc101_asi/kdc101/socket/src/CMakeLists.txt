cmake_minimum_required(VERSION 3.10)
project(KDC101_SRC)

add_library(KDC101_SOCKET STATIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/socket.cpp  
    ${CMAKE_CURRENT_SOURCE_DIR}/../client/src/client.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../server/src/server.cpp 
)

target_link_libraries(KDC101_SOCKET
    SOCKET_SERVER
    SOCKET_CLIENT    
    ws2_32
)

target_include_directories(KDC101_SOCKET PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../client/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../server/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../sdk/include
)  # 使用 PUBLIC 让包含目录可传递

target_link_options(KDC101_SOCKET PUBLIC "LINKER:-subsystem,console")

install(TARGETS KDC101_SOCKET DESTINATION build)
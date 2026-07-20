cmake_minimum_required(VERSION 3.10)
project(ZWO_src)

set(OpenCV_DIR "E:/software/HS/opencv455/x64/mingw/lib") # 使用你的实际路径
find_package(OpenCV REQUIRED)

message("OpenCV include directories: ${OpenCV_INCLUDE_DIRS}")

include_directories(
    ${OpenCV_INCLUDE_DIRS}
)

# old plan: add_executable、add_library
add_library(ZWO_SRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/old_method/asi_func.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asi_opencv.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asi_convert.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/asi_find_center.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../log/log.cpp
)

message("OpenCV_LIBS: ${OpenCV_LIBS}")

# add_library(ZWO_SRC
#     ${CMAKE_CURRENT_SOURCE_DIR}/camera_main.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/camera.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/camera_mode.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/camera_init.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/camera_exposure.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/camera_process.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/asi_opencv.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/asi_convert.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../../log/log.cpp
# )

target_link_libraries(ZWO_SRC  
    ws2_32
    ${OpenCV_LIBS} 
)

target_include_directories(ZWO_SRC PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../sdk/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../log
    ${OpenCV_INCLUDE_DIRS}
)  # 使用 PUBLIC 让包含目录可传递

install(TARGETS ZWO_SRC DESTINATION build)
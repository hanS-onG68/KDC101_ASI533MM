cmake_minimum_required(VERSION 3.10)
project(kdc101_qt)

set(OpenCV_DIR "E:/software/HS/opencv455/x64/mingw/lib") # 使用你的实际路径
find_package(OpenCV REQUIRED)

message("OpenCV include directories: ${OpenCV_INCLUDE_DIRS}")

include_directories(
    ${OpenCV_INCLUDE_DIRS}
)

message("OpenCV_LIBS: ${OpenCV_LIBS}")

add_executable(KDC101_QT
    asi_func.cpp
    asi_opencv.cpp
    asi_convert.cpp
    tlmc_func.cpp
    asi_check_aligned.cpp
    main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/log/log.cpp
)

message("Qt6Widgets_INCLUDE_DIRS: ${Qt6Widgets_INCLUDE_DIRS}")

target_include_directories(KDC101_QT PUBLIC 
    ${Qt6Widgets_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/log
)

find_package(Qt6 REQUIRED COMPONENTS Gui Core Widgets)

target_link_libraries(KDC101_QT
    Qt6::Widgets
    Qt6::Core
    Qt6::Gui
    ws2_32
    ${OpenCV_LIBS}
    # ${CMAKE_CURRENT_SOURCE_DIR}/sdk/tlmc_xa_native.dll
    ${CMAKE_CURRENT_SOURCE_DIR}/sdk/tlmc_xa_native.lib
    # ${CMAKE_CURRENT_SOURCE_DIR}/sdk/tlmc_xa_native_static.lib
    # ${CMAKE_CURRENT_SOURCE_DIR}/sdk/ASICamera2.dll
)

add_compile_options(-fexec-charset=UTF-8 -finput-charset=UTF-8)
target_link_options(KDC101_QT PRIVATE "LINKER:-subsystem,console")
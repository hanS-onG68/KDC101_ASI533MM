cmake_minimum_required(VERSION 3.10)
project(kdc101_qt)

add_executable(KDC101_QT
    main.cpp
)

message("Qt6Widgets_INCLUDE_DIRS: ${Qt6Widgets_INCLUDE_DIRS}")

target_include_directories(KDC101_QT PUBLIC 
    ${Qt6Widgets_INCLUDE_DIRS}
)


# set(CMAKE_PREFIX_PATH "D:/Soft/QT/6.5.3/mingw_64")
find_package(Qt6 REQUIRED COMPONENTS Gui Core Widgets)
# set(QT_PLUGIN_PATH "D:/Soft/QT/6.5.3/mingw_64/plugins")

target_link_libraries(KDC101_QT
    Qt6::Widgets
    Qt6::Core
    Qt6::Gui
    KDC101_SOCKET
)

target_link_options(KDC101_QT PRIVATE "LINKER:-subsystem,console")
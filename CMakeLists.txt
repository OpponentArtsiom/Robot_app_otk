cmake_minimum_required(VERSION 3.5)
project(RobotOtkApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets Sql)

add_executable(RobotOtkApp
    main.cpp
    mainwindow.cpp
    mainwindow.h
    database.cpp
    database.h
    addrobotdialog.h
    addrobotdialog.cpp
    editrobotdialog.h
    editrobotdialog.cpp
    migrations.h
    migrations.cpp
)

target_link_libraries(RobotOtkApp Qt5::Widgets Qt5::Sql)

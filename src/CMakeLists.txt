cmake_minimum_required(VERSION 3.5)

project(verkkosimu VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        Network.h
        Node.h
        Link.h
        Packet.h
        Application.h
        EndHost.h
        Router.h
        Router.cpp
        Packet.cpp
        Link.cpp
        Node.cpp
        Network.cpp
        EndHost.cpp
        Application.cpp
        RoutingEndHost.h
        RoutingEndHost.cpp
        resources.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_library(verkkosimu
        SHARED
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_library(verkkosimu
        SHARED
        ${PROJECT_SOURCES}
    )
endif()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_target(verkkosimu)
endif()


if(QT_VERSION_MAJOR EQUAL 6)
    qt_add_executable(verkkosimuapp MANUAL_FINALIZATION main.cpp)
else()
    add_executable(verkkosimuapp main.cpp)
endif()


target_link_libraries(verkkosimu PRIVATE Qt::Widgets Qt::Core Qt::Gui)


target_link_libraries(verkkosimuapp PRIVATE Qt::Widgets verkkosimu)


set_target_properties(verkkosimuapp PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS verkkosimu
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(verkkosimuapp)
endif()

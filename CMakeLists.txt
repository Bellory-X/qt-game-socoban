cmake_minimum_required(VERSION 3.5)

project(Sokoban VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        loader.h loader.cpp
        blockpixmapitem.h blockpixmapitem.cpp
        gamescene.h gamescene.cpp
        tablerecordsmodel.h tablerecordsmodel.cpp
        mainwindow.h mainwindow.cpp mainwindow.ui
        saverecorddialog.h saverecorddialog.cpp saverecorddialog.ui
        resources.qrc
        main.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Sokoban
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Sokoban SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Sokoban
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Sokoban PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Sokoban PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Sokoban
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Sokoban)
endif()

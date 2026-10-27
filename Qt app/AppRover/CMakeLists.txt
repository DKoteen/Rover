cmake_minimum_required(VERSION 3.16)

project(AppRover VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick SerialPort Quick3D)

qt_standard_project_setup(REQUIRES 6.10)

# Content of downloaded design from Figma to Qt or similar
if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/importedcontent/CMakeLists.txt")
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/importedcontent)
endif()

qt_add_executable(appAppRover
    main.cpp
)

qt_add_qml_module(appAppRover
    URI AppRover
    QML_FILES
        Main.qml
        SOURCES roverstate.h
        SOURCES rovercontroller.h rovercontroller.cpp
        SOURCES telemetryparser.h telemetryparser.cpp
        QML_FILES RoverModel.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appAppRover PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appAppRover
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appAppRover
    PRIVATE Qt6::Quick Qt6::SerialPort Qt6::Quick3D

)

install(TARGETS appAppRover
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

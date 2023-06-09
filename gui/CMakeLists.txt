cmake_minimum_required(VERSION 3.16)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick QuickControls2)

######################################################
#include(FetchContent)

#FetchContent_Declare(qanava
#        GIT_REPOSITORY https://github.com/cneben/QuickQanava.git
#        GIT_TAG origin/master)

#FetchContent_GetProperties(qanava)
#if(NOT qanava_POPULATED)
#    FetchContent_Populate(qanava)
#    add_subdirectory(${qanava_SOURCE_DIR} ${qanava_BINARY_DIR} EXCLUDE_FROM_ALL)
#endif()


#FetchContent_Declare(fmt
#        GIT_REPOSITORY https://github.com/fmtlib/fmt
#        GIT_TAG origin/master)

#FetchContent_GetProperties(fmt)
#if(NOT fmt_POPULATED)
#    FetchContent_Populate(fmt)
#    add_subdirectory(${fmt_SOURCE_DIR} ${fmt_BINARY_DIR} EXCLUDE_FROM_ALL)
#endif()
######################################################

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appzadnji
    main.cpp
    theme.qrc
)

qt_add_qml_module(appzadnji
    URI zadnji
    VERSION 1.0
    QML_FILES
        Main.qml
        CustomNode.qml
    SOURCES
        menu.cpp
        menu.h
        graph.cpp
        graph.h
)

set_target_properties(appzadnji PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)


target_link_libraries(appzadnji
    PRIVATE Qt6::QuickControls2 Qt6::Quick nn_moj
    PUBLIC QuickQanava
)

target_include_directories(appzadnji
    PUBLIC ${PROJECT_SOURCE_DIR}/nn_moj/
)

install(TARGETS appzadnji
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

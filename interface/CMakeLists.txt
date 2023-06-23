cmake_minimum_required(VERSION 3.16)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Quick QuickControls2)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(interface
    main.cpp
    custom_nodes.qrc
)


qt_add_qml_module(interface
    URI zadnji
    VERSION 1.0
    QML_FILES
        Main.qml
    SOURCES
        network_builder.cpp
        network_builder.h
        custom_node.h
        custom_node.cpp
)

set_target_properties(interface PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)


target_link_libraries(interface
    PRIVATE Qt6::QuickControls2 Qt6::Quick Qt6::Core
    PUBLIC QuickQanava neural_network
)

target_include_directories(interface
    PUBLIC ${PROJECT_SOURCE_DIR}/neural_network/
)

install(TARGETS interface
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

cmake_minimum_required(VERSION 3.21)  # Qt 6.9 推荐版本

project(YuntuGUI VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 Qt6 组件 (优先 6.9，兼容 6.5+)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Gui)

# Qt 6.9 兼容性设置
if(Qt6_VERSION VERSION_GREATER_EQUAL "6.9.0")
    message(STATUS "使用 Qt ${Qt6_VERSION} (6.9+ 优化)")
    set_property(GLOBAL PROPERTY QT_DISABLE_DEPRECATED_UP_TO 0x060900)
else()
    message(STATUS "使用 Qt ${Qt6_VERSION} (兼容模式)")
endif()

# 设置 Qt 自动处理
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 源文件
set(SOURCES
    main.cpp
    login_window.cpp
    register_window.cpp
)

# 头文件
set(HEADERS
    login_window.h
    register_window.h
)

# 资源文件
set(RESOURCES
    resources.qrc
)

# 创建可执行文件
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${RESOURCES}
)

# 链接 Qt 库
target_link_libraries(${PROJECT_NAME} 
    Qt6::Core 
    Qt6::Widgets 
    Qt6::Gui
)

# Windows 特定设置
if(WIN32)
    # 设置 Windows 图标和版本信息
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
        OUTPUT_NAME "YuntuGUI"
    )
    
    # 如果是 Release 模式，隐藏控制台窗口
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        set_target_properties(${PROJECT_NAME} PROPERTIES
            LINK_FLAGS "/SUBSYSTEM:WINDOWS"
        )
    endif()
endif()

# 安装规则
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# 复制 Qt 运行时库 (Windows)
if(WIN32)
    if(Qt6_FOUND)
        find_program(QT_WINDEPLOYQT_EXECUTABLE windeployqt HINTS ${Qt6_DIR}/../../../bin)
    else()
        find_program(QT_WINDEPLOYQT_EXECUTABLE windeployqt HINTS ${Qt5_DIR}/../../../bin)
    endif()
    
    if(QT_WINDEPLOYQT_EXECUTABLE)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${QT_WINDEPLOYQT_EXECUTABLE} $<TARGET_FILE:${PROJECT_NAME}>
            COMMENT "Deploying Qt libraries"
        )
    endif()
endif()

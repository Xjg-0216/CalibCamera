cmake_minimum_required(VERSION 3.16)
project(StereoCalibration)

set(CMAKE_CXX_STANDARD 11)

# 01 包含头文件目录
include_directories(include)
# 02 导入OpenCV包
find_package(OpenCV REQUIRED)
find_package(yaml-cpp REQUIRED)
# 03 包含头文件搜索路径
include_directories(${OpenCV_INCLUDE_DIRS})


# 04 源文件列表
set(SOURCES
    src/Camera.cpp
    src/CheckBoard.cpp
    src/Utils.cpp
    src/Config.cpp
    main.cpp
)

# 05 生成可执行文件
add_executable(CalibCamera ${SOURCES})

# 06 链接 OpenCV
target_link_libraries(CalibCamera ${OpenCV_LIBS} yaml-cpp)
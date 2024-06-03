# 指定最小版本
cmake_minimum_required(VERSION 3.15)

# 设定项目名称，可以指定项目版本号
project(fje VERSION 1.0.0)

# 设置c++版本，默认是c++14
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置可执行文件输出路径为根目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

# 添加源文件
file(GLOB SRC_LIST *.cpp *.hpp *.c *.h)
aux_source_directory(src SRC_LIST)
aux_source_directory(src/JsonParser SRC_LIST)
aux_source_directory(src/Style SRC_LIST)
aux_source_directory(src/Utils SRC_LIST)

# 指定搜索头文件路径
include_directories(include)

# 添加调试参数
add_compile_options(-O2)

add_executable(${PROJECT_NAME} ${SRC_LIST})

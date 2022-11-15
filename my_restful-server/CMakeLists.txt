cmake_minimum_required(VERSION 2.6)
project(pro)

option(CUDA_USE_STATIC_CUDA_RUNTIME OFF)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/workspace)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # 生成compile_commands.json文件



include_directories(
    ${PROJECT_SOURCE_DIR}/src
)


set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  -Wall -O0 -Wfatal-errors -pthread -w -g")
file(GLOB_RECURSE cpp_srcs ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE c_srcs ${PROJECT_SOURCE_DIR}/src/*.c)

add_executable(pro ${cpp_srcs} ${c_srcs})

# 如果提示插件找不到，请使用dlopen(xxx.so, NOW)的方式手动加载可以解决插件找不到问题


add_custom_target(
    run
    DEPENDS pro
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/workspace
    COMMAND ./pro
)
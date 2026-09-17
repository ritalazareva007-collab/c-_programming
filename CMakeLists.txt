cmake_minimum_required(VERSION 3.26)
project(git_clion LANGUAGES CXX)

# Стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ГЛАВНОЕ: все exe складываются в <папка сборки>/bin,
# а НЕ рядом с исходниками
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Автоматически находим все .cpp в нужных папках
file(GLOB_RECURSE PROGRAM_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_SOURCE_DIR}/algorithms/*.cpp"
        "${CMAKE_SOURCE_DIR}/datastructures/*.cpp"
)

# Для каждого .cpp создаём отдельную цель (и отдельную конфигурацию запуска)
foreach(SOURCE_FILE IN LISTS PROGRAM_SOURCES)
    get_filename_component(TARGET_NAME "${SOURCE_FILE}" NAME_WE)
    add_executable("${TARGET_NAME}" "${SOURCE_FILE}")
endforeach()
cmake_minimum_required(VERSION 3.23.2)

project(MoviesToWatch)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp)

add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

include(cmake/CPM.cmake)

CPMAddPackage(
    NAME drogon
    VERSION 1.7.5
    GITHUB_REPOSITORY drogonframework/drogon
    GIT_TAG v1.7.5
)

target_include_directories(${PROJECT_NAME} PUBLIC ${DROGON_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE drogon)

add_subdirectory(src)

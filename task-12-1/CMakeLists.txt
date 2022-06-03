cmake_minimum_required(VERSION 3.0.0)
project(graph)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES Graph/src/*.cc
                  )

file(GLOB INCLUDE_DIRS  Graph/inc
                        )                     

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})

set(GRAPH_LIBRARIES ${PROJECT_NAME})
set(GRAPH_INCLUDE_DIRS ${INCLUDE_DIRS})

add_executable(12-1 12-1.cc)
target_include_directories(12-1 PUBLIC ${GRAPH_INCLUDE_DIRS})
target_link_libraries(12-1 PRIVATE ${GRAPH_LIBRARIES})
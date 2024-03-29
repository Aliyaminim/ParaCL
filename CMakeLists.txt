cmake_minimum_required(VERSION 3.13)
project(ParaCL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
    message(FATAL_ERROR "In-source build is forbidden")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -O0 -D DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O2 -DNDEBUG")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(Threads REQUIRED)
find_package(BISON 3.7.6)
find_package(FLEX REQUIRED)

set(TREE_INCLUDE_DIR ./ast_tree)
set(VIS_INCLUDE_DIR ./ast_tree/observer)
set(INCLUDE_DIR ./parsing/include)
set(PARSER ./parsing/parser.y)
set(LEXER ./parsing/flex.l)
set(SOURCES ./src/main.cc)

flex_target(scanner
  ${LEXER}
  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cc
)

bison_target(parser
  ${PARSER}
  ${CMAKE_CURRENT_BINARY_DIR}/parser.cc
  COMPILE_FLAGS "--defines=${CMAKE_CURRENT_BINARY_DIR}/parser.tab.hh -Wcounterexamples"
)

add_flex_bison_dependency(scanner parser)

include_directories(${PROJECT_NAME} PUBLIC ${TREE_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_NAME} PUBLIC ${VIS_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME}
  ${SOURCES}
  ${BISON_parser_OUTPUTS}
  ${FLEX_scanner_OUTPUTS}
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

#enable e2e testing
set(BASH_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/test/testing.sh)

add_custom_command(
    OUTPUT output_file
    COMMAND bash ${BASH_SCRIPT}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test
)

add_custom_target(test DEPENDS output_file)

#make -C ./build test

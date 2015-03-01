project(GameOfLife)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(./Classes ./Classes/GUI)
set(SRC_LIST ./main.cpp ./Classes/Gol.cpp ./Classes/GolDrawField.cpp ./Classes/GUI/TextBox.cpp ./Classes/GUI/TextButton.cpp ./Classes/GUI/ImageButton.cpp ./Classes/GUI/UiLayout.cpp)
add_executable(${PROJECT_NAME} ${SRC_LIST})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

if (MINGW)
    set(SFML_ROOT "./SFML")
    set(SFML_STATIC_LIBRARIES ON)
endif()

find_package(SFML 2 REQUIRED graphics window network audio system)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
    target_link_libraries(${PROJECT_NAME} ${SFML_DEPENDENCIES})
else()
    message(SEND_ERROR "SFML not found. Please set SFML_ROOT.")
endif()

file(COPY "${CMAKE_SOURCE_DIR}/Resources" DESTINATION ".")

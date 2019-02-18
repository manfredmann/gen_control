cmake_minimum_required(VERSION 2.8)

project(Gen_33210A)

include_directories("inc/")

set(SOURCES
    src/main.cpp
    src/gen.cpp
    src/packet.cpp
    src/amplitude.cpp
    src/waveform.cpp)
set(HEADERS
    inc/errors.h
    inc/gen.h
    inc/packet.h
    inc/amplitude.h
    inc/waveform.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} usb-1.0)

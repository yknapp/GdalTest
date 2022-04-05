cmake_minimum_required(VERSION 3.19.0)

project(gdalTest LANGUAGES CXX)

set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.h
    OsmDataProvider.cpp)
	
set(HEADER
    main.cpp
    OsmDataProvider.h)

find_package(GDAL
    REQUIRED)

add_executable(${PROJECT_NAME} main.h ${HEADER} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(
    ${PROJECT_NAME}
    ${GDAL_LIBRARIES})

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE .
    ${GDAL_LIBRARIES})

cmake_minimum_required(VERSION 3.0.0)

project(PS4freetype2)

if (NOT TARGET freetype)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/freetype2
		${CMAKE_CURRENT_BINARY_DIR}/freetype2
	)
endif()


add_library(PS4freetype2
	src/PS4freetype2.c
	src/PS4freetype2.cpp
)

target_link_libraries(PS4freetype2 PUBLIC PS4::HEADERS freetype)
target_include_directories(PS4freetype2 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_BINARY_DIR}/freetype2/include" "${CMAKE_CURRENT_SOURCE_DIR}/freetype2/include")

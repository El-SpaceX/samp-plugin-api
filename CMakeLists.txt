cmake_minimum_required(VERSION 3.10)

project(samp-plugin-api)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

include(AddSAMPPlugin)

add_samp_plugin(${PROJECT_NAME}
	plugin.def


	src/main.hpp
	src/main.cpp
	src/plugin.hpp
	src/plugin.cpp
	src/script.hpp
	src/script.cpp
	src/api.hpp
	src/api.cpp

	
	lib/cpp-httplib/httplib.h
	lib/samp-ptl/ptl.h
)

target_include_directories(${PROJECT_NAME} PRIVATE lib)

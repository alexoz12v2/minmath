cmake_minimum_required(VERSION 3.23.2)
project(minmath)

add_library(minmath_lib STATIC  "src/common.cpp"
				"src/fnumber.cpp"
				"src/fpowlog.cpp"
				"src/ftrig.cpp")

target_include_directories(minmath_lib PUBLIC 
		"${PROJECT_SOURCE_DIR}/include"
		"${PROJECT_SOURCE_DIR}/src")

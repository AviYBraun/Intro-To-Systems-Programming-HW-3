cmake_minimum_required(VERSION 3.28.3)
project(HW3_2425B)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(HW3_2425B
		main.cpp
		Person.h
		Person.cpp
		Task.cpp
		Task.h
		TaskManager.h
    SortedList.h
		TaskManager.cpp
)

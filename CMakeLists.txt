cmake_minimum_required (VERSION 2.6)


project(parallel_algorithms)
add_executable(for_each for_each.cpp)
add_executable(sort sort.cpp)

IF(WIN32)
ELSE(WIN32)
  find_package (Threads)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
  target_link_libraries (for_each ${CMAKE_THREAD_LIBS_INIT})
  target_link_libraries (sort ${CMAKE_THREAD_LIBS_INIT})
ENDIF(WIN32)




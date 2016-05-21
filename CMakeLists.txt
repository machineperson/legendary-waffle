cmake_minimum_required (VERSION 2.6)
project (LegendaryWaffle)
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()


include_directories (lib/)
add_executable (${PROJECT_NAME} src/client.cpp)
INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(NCURSES REQUIRED ncurses)

INCLUDE_DIRECTORIES(${NCURSES_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${NCURSES_LIBRARIES})

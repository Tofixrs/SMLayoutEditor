cmake_minimum_required(VERSION 3.8.2)

project(SMLayoutEditor-ConfigGen VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


if(CMAKE_BUILD_TYPE MATCHES Debug OR CMAKE_BUILD_TYPE MATCHES DEBUG)
    message(STATUS "Configuring guessing_game in Debug with CMake")
else()
    add_compile_options(-O3)
    message(STATUS "Configuring guessing_game in Release with CMake")
endif()

include_directories(
	.
)

set(CMAKE_CXX_STANDARD 23)
add_compile_options(-Wall -Wextra -Wno-unused-parameter -Wno-unused-value
	-Wno-missing-field-initializers -Wno-narrowing)

# dependencies
message(STATUS "Checking deps...")
find_package(PkgConfig REQUIRED)
pkg_check_modules(TinyXML2 REQUIRED tinyxml2)
include_directories(${TinyXML2_INCLUDE_DIRS})

file(GLOB_RECURSE SRCFILES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(SMLayoutEditor-ConfigGen ${SRCFILES})
target_link_libraries(SMLayoutEditor-ConfigGen PUBLIC ${TinyXML2_LIBRARIES})

install(TARGETS SMLayoutEditor-ConfigGen)

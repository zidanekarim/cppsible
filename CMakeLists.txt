cmake_minimum_required(VERSION 3.10.0)
project(cppsible VERSION 0.1.0 LANGUAGES C CXX)


file(GLOB SOURCES "src/*.cpp")
add_executable(cppsible ${SOURCES})

include(CTest)
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBSSH REQUIRED libssh)

include_directories(${CMAKE_SOURCE_DIR}/include)

target_include_directories(cppsible PRIVATE ${LIBSSH_INCLUDE_DIRS})
target_link_libraries(cppsible PRIVATE ${LIBSSH_LIBRARIES})

enable_testing()


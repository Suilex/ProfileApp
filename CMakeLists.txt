cmake_minimum_required(VERSION 3.14)
project(ProfileApp)

set(CMAKE_CXX_STANDARD 17)

set(DROGON_ROOT "${CMAKE_SOURCE_DIR}/drogon/install")

find_package(Drogon REQUIRED PATHS ${DROGON_ROOT}/lib/cmake)

add_executable(server src/main.cpp)
target_link_libraries(server PRIVATE Drogon::Drogon)
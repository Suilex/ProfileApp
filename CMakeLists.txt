cmake_minimum_required(VERSION 3.14)
project(ProfileApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(DROGON_ROOT "${CMAKE_SOURCE_DIR}/drogon/install")

find_package(Drogon REQUIRED PATHS ${DROGON_ROOT}/lib/cmake)

# Установка конфигурации Debug по умолчанию
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Добавление символов отладки
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

add_executable(server 
    main.cpp 
    src/controller/ProfileController.cpp
    src/repository/UserRepository.cpp)

target_include_directories(server PRIVATE ${PROJECT_SOURCE_DIR}/src/controllers)

target_link_libraries(server PRIVATE Drogon::Drogon)
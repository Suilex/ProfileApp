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
    src/controller/AuthController.cpp
    src/repository/UserRepository.cpp
    src/service/AuthService.cpp
    )

target_include_directories(server PRIVATE ${PROJECT_SOURCE_DIR}/src/controllers)

target_link_libraries(server PRIVATE Drogon::Drogon)

include(FetchContent)
FetchContent_Declare(
  jwt-cpp
  GIT_REPOSITORY https://github.com/Thalhammer/jwt-cpp.git
  GIT_TAG v0.7.0
)
set(JWT_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(JWT_BUILD_TESTS OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(jwt-cpp)
target_link_libraries(server PRIVATE jwt-cpp)
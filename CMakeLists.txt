cmake_minimum_required(VERSION 3.18)

project(workshop_inventory_management_system)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# download asio for crow from the GitHub repository
FetchContent_Declare(
    asio
        GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
        GIT_TAG 147f7225a96d45a2807a64e443177f621844e51c
)
FetchContent_MakeAvailable(asio)

# download Crow from the GitHub repository
FetchContent_Declare(
    Crow
        GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
        GIT_TAG edf12f699ec3bf6f751cf73cb97f32919e48ca6e
)
FetchContent_MakeAvailable(Crow)

find_package(SQLite3 REQUIRED)

# Add include directory
include_directories(
    PRIVATE
        include/
)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
        Crow::Crow
        SQLite::SQLite3
)

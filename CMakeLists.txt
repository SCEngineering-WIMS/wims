cmake_minimum_required(VERSION 3.18)

project(workshop_inventory_management_system)

include_directories(include/)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
)

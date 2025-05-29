cmake_minimum_required(VERSION 3.10)
project(HomeEnergyTracker)

# MongoDB C++ Driver
find_package(mongocxx REQUIRED)
find_package(bsoncxx REQUIRED)

# Qt
set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(HomeEnergyTracker main.cpp EnergyTracker.cpp UserAuth.cpp GUI.cpp)
target_link_libraries(HomeEnergyTracker PRIVATE Qt5::Widgets mongocxx bsoncxx)

find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)
target_link_libraries(HomeEnergyTracker PRIVATE Qt5::Widgets Qt5::Charts mongocxx bsoncxx)

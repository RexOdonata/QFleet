cmake_minimum_required(VERSION 3.14)

project(QFT_Components LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(QFT_Components SHARED
  qft_component.h
  qft_enum.h
  qfleet_tonnage.h qfleet_tonnage.cpp
  qfleet_armor.h qfleet_armor.cpp
  qfleet_lock.h qfleet_lock.cpp
  qfleet_launchprofile.h qfleet_launchprofile.cpp
  qfleet_weapon.h qfleet_weapon.cpp
  qfleet_arc.h qfleet_arc.cpp
  qfleet_option.h qfleet_option.cpp
  qfleet_opttype.h qfleet_opttype.cpp
)

target_link_libraries(QFT_Components PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(QFT_Components PRIVATE QFT_COMPONENTS_LIBRARY)

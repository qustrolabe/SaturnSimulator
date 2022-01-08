cmake_minimum_required(VERSION 3.13.0)
project(SaturnSimulator VERSION 0.0.3)

set(CMAKE_CXX_STANDARD 17)

include(cmake/CPM.cmake)


CPMAddPackage("gh:SFML/SFML#2.5.1")
CPMAddPackage("gh:ocornut/imgui#docking")
CPMAddPackage(
    GITHUB_REPOSITORY "eliasdaler/imgui-sfml"
    VERSION "2.5"
    OPTIONS "IMGUI_DIR ${imgui_SOURCE_DIR}"
)
add_compile_definitions(IMGUI_DISABLE_DEMO_WINDOWS) # imgui-sfml doesn't compile demo by default

CPMAddPackage(
  NAME EnTT
  VERSION 3.9.0
  GITHUB_REPOSITORY skypjack/entt
  # EnTT's CMakeLists screws with configuration options
  DOWNLOAD_ONLY True
)

if(EnTT_ADDED)
add_library(EnTT INTERFACE)
target_include_directories(EnTT SYSTEM INTERFACE ${EnTT_SOURCE_DIR}/src)
endif()

add_executable(${PROJECT_NAME}
				src/main.cpp
				src/Simulation/Simulation.cpp
				src/Simulation/Scene.cpp
				src/Simulation/Factories.cpp
				src/Simulation/Utils.cpp
				)

target_link_libraries(${PROJECT_NAME} PRIVATE ImGui-SFML::ImGui-SFML EnTT)

target_include_directories(
	${PROJECT_NAME} PRIVATE
	${imgui_SOURCE_DIR}
	${imgui-sfml_SOURCE_DIR}
	src/Simulation
)

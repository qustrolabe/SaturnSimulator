cmake_minimum_required(VERSION 3.13.0)
project(SaturnSimulator VERSION 0.1)

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


add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ImGui-SFML::ImGui-SFML)

target_include_directories(
	${PROJECT_NAME} PRIVATE
	${imgui_SOURCE_DIR}
	${imgui-sfml_SOURCE_DIR}
)

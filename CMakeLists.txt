cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)

FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG v5.0.0
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
    FetchContent_Populate(ftxui)
    add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

FetchContent_MakeAvailable(ftxui)

project(ChaxTUI LANGUAGES CXX VERSION 0.0.1)

add_executable(ChaxTUI main.cpp)

target_link_libraries(ChaxTUI
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
)


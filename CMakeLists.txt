cmake_minimum_required(VERSION 3.28)
project(MonJeu LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
    GIT_SHALLOW ON)
FetchContent_MakeAvailable(json)

add_executable(MonJeu
    src/main.cpp
    src/Game.cpp
    src/Player.cpp
    src/Camera.cpp
    src/Map.cpp
    src/Ennemies.cpp)

target_include_directories(MonJeu PRIVATE include)
target_link_libraries(MonJeu PRIVATE SFML::Graphics nlohmann_json::nlohmann_json)
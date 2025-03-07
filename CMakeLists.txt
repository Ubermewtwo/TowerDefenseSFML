cmake_minimum_required(VERSION 3.23)
project(GameTemplate LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)

# Download and add SFML as a dependency
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Librer�a Json for Modern C++ (header-only, no necesita compilaci�n)
FetchContent_Declare(
    Json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(Json)

# Librer�a TGUI (para interfaces gr�ficas con SFML)
FetchContent_Declare(
    TGUI
    GIT_REPOSITORY https://github.com/texus/TGUI.git
    GIT_TAG v1.7.0
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(TGUI)

# Download and add tmxlite (tiled editor loader) as a dependency
FetchContent_Declare(
    TMXLITE
    GIT_REPOSITORY https://github.com/fallahn/tmxlite.git
    GIT_TAG v1.4.4
    SOURCE_SUBDIR tmxlite)
FetchContent_MakeAvailable(TMXLITE)


set(PROJECT_HEADERS 
    include/Utils/Constants.h

    include/Core/AssetManager.h
    include/Core/Game.h
    include/Core/World.h
    include/Core/EnemySpawner.h
    include/Core/EnemyFactory.h
    include/Core/ScreenInputManager.h
    include/Core/TowerManager.h
    include/Core/TowerFactory.h
    include/Core/SoundManager.h

    include/Gameplay/GameObject.h
    include/Gameplay/AnimatedEntity.h
    include/Gameplay/Enemy.h
    include/Gameplay/Tower.h
    include/Gameplay/TowerUnit.h
    include/Gameplay/TowerProjectile.h

    include/Render/SFMLOrthogonalLayer.h

    include/UI/UIScreenMainMenu.h
)

set(PROJECT_SOURCES 

    src/Core/AssetManager.cpp
    src/Core/Game.cpp
    src/Core/World.cpp
    src/Core/EnemySpawner.cpp
    src/Core/EnemyFactory.cpp
    src/Core/ScreenInputManager.cpp
    src/Core/TowerManager.cpp
    src/Core/TowerFactory.cpp
    src/Core/SoundManager.cpp

    src/Gameplay/AnimatedEntity.cpp
    src/Gameplay/Enemy.cpp
    src/Gameplay/Tower.cpp
    src/Gameplay/TowerUnit.cpp
    src/Gameplay/TowerProjectile.cpp

    src/main.cpp
)

set(PROJECT_FILES 
  ${PROJECT_HEADERS} 
  ${PROJECT_SOURCES}
)

include_directories(${PROJECT_NAME} PRIVATE ${tmxlite_INCLUDE_DIR} include)

add_executable(${PROJECT_NAME} ${PROJECT_FILES})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set Debugger Working Directory
set_property(TARGET ${PROJECT_NAME} PROPERTY 
    VS_DEBUGGER_WORKING_DIRECTORY 
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>")

# Copy the data directory after building
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/data" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data"
)

# Debug messages
message(STATUS "Source directory: ${CMAKE_SOURCE_DIR}/data")
message(STATUS "Destination directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data")

target_link_libraries(${PROJECT_NAME} PRIVATE 
    sfml-graphics 
    sfml-audio
    tgui
    nlohmann_json::nlohmann_json
    tmxlite
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_compile_definitions(${PROJECT_NAME} PUBLIC DEBUG_MODE=0)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
endif()

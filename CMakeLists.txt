cmake_minimum_required(VERSION 3.31)

project(game VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED true)
set(BUILD_SHARED_LIBS OFF)

################
# Dependencies #
################

include(FetchContent)

#Set the dependencies ouput directory
set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/dependencies/) 
#Ensures that find_package is called first for every FetchContent instead of downloading the dependency
set(FETCHCONTENT_TRY_FIND_PACKAGE_MODE ALWAYS)

# Vulkan - Must be installed in the system
find_package(Vulkan REQUIRED)

# GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    SOURCE_DIR "${CMAKE_SOURCE_DIR}/dependencies/src/glfw"
    BINARY_DIR "${CMAKE_SOURCE_DIR}/dependencies/${PRESET_BUILD_TYPE_DIR}/glfw"
)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_VULKAN_STATIC  ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# Assimp
FetchContent_Declare(
    assimp
    GIT_REPOSITORY https://github.com/assimp/assimp.git
    SOURCE_DIR "${CMAKE_SOURCE_DIR}/dependencies/src/assimp"
    BINARY_DIR "${CMAKE_SOURCE_DIR}/dependencies/${PRESET_BUILD_TYPE_DIR}/assimp"
)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL_PDB OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_VIEW OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(assimp)

# Nlohmann json
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    SOURCE_DIR "${CMAKE_SOURCE_DIR}/dependencies/src/nlohmann"
    BINARY_DIR "${CMAKE_SOURCE_DIR}/dependencies/${PRESET_BUILD_TYPE_DIR}/nlohmann"
)
FetchContent_MakeAvailable(nlohmann_json)

##################
# Subdirectories #
##################

add_subdirectory(engine)
add_subdirectory(tools/assetparser)
add_subdirectory(game)

#Parse assets
#Create a custom target to ensure that the asset parser gets executed every time the project is built
add_custom_target(
    parse_assets_target ALL
    DEPENDS game assetparser parse_assets_target 
)

add_custom_command(
    TARGET parse_assets_target POST_BUILD
    COMMAND assetparser ARGS -d ${CMAKE_CURRENT_SOURCE_DIR}/game/assets -o ${CMAKE_CURRENT_BINARY_DIR}/game/assets
    COMMENT "Parsing game assets..."
)


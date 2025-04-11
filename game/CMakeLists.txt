file(GLOB_RECURSE game_sources CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c" 
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h" 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")

add_executable(game ${game_sources})

target_link_libraries(game PUBLIC engine)

#Parse assets
#Create a custom target to ensure that the asset parser gets executed every time the project is built
add_custom_target(
    parse_assets_target ALL
)

add_custom_command(
    TARGET parse_assets_target POST_BUILD
    COMMAND assetparser ARGS -d ${CMAKE_CURRENT_SOURCE_DIR}/assets -o ${CMAKE_CURRENT_BINARY_DIR}/assets
    COMMENT "Parsing game assets..."
)
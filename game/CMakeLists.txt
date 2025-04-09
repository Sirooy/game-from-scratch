file(GLOB_RECURSE game_sources CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c" 
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h" 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")

add_executable(game ${game_sources})

target_link_options(game PRIVATE -static)
target_link_libraries(game PUBLIC engine)
file(GLOB_RECURSE engine_sources CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c" 
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h" 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")

add_library(engine STATIC ${engine_sources})

target_compile_definitions(engine PRIVATE -DGLFW_INCLUDE_NONE)

target_link_options(engine PRIVATE -static)
target_link_libraries(engine PUBLIC Vulkan::Vulkan)
target_link_libraries(engine PUBLIC glfw)

target_include_directories(engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
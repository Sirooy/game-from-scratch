file(GLOB_RECURSE tools_assetparser_sources CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c" 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")

add_executable(assetparser ${tools_assetparser_sources})

target_link_libraries(assetparser PUBLIC Vulkan::shaderc_combined)
target_link_libraries(assetparser PUBLIC Vulkan::glslang)
target_link_libraries(assetparser PUBLIC SPIRV-Tools-opt)
target_link_libraries(assetparser PUBLIC Vulkan::SPIRV-Tools)
target_link_libraries(assetparser PUBLIC assimp)
target_link_libraries(assetparser PUBLIC nlohmann_json)
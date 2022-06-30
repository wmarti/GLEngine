add_library(World STATIC
    block_data.cpp
    block_data.h
    chunk.cpp
    chunk.h
 "world.cpp" "world.h")
target_include_directories(World PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../")
target_include_directories(World PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../Shaders")

target_link_libraries(World PUBLIC glm glad stb)
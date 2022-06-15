add_library(Shaders STATIC
    shader.cpp
    shader.h
)
target_include_directories(Shaders PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../")
target_link_libraries(Shaders PUBLIC glad stb glm)
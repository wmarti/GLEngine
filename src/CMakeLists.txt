add_executable(GLEngine
    block_data.cpp
    block_data.h
    camera.h
    common.h
    main.cpp
    chunk.cpp
    chunk.h
    gl_engine.cpp
    gl_engine.h
    shader.cpp
    shader.h
    texture.cpp
    texture.h
    texture_atlas.cpp
    texture_atlas.h
    timer.h
)

find_package(glfw3)
target_link_libraries(GLEngine PUBLIC glfw glad stb glm ${CMAKE_DL_LIBS})
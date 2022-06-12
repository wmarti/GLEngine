add_executable(GLEngine
    block_data.cpp
    block_data.h
    main.cpp
    gen_chunk.cpp
    gen_chunk.h
    gl_engine.cpp
    gl_engine.h
    shader.cpp
    shader.h
    texture.cpp
    texture.h)

target_include_directories(GLEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(glfw3)
target_link_libraries(GLEngine glfw glad stb glm ${CMAKE_DL_LIBS})
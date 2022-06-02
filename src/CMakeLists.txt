add_executable(GLEngine
    main.cpp
    gl_engine.cpp
    gl_engine.h
    shader.h
    texture.h
)

target_include_directories(GLEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(glfw3)
target_link_libraries(GLEngine glfw glad stb glm ${CMAKE_DL_LIBS})
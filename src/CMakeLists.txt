add_executable(GLEngine
    camera.h
    common.h
    main.cpp
    gl_engine.cpp
    gl_engine.h
    texture.cpp
    texture.h
    texture_atlas.cpp
    texture_atlas.h
    timer.h
 "common.cpp")

target_include_directories(GLEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Shaders")
target_include_directories(GLEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/World")

add_subdirectory(Shaders)
add_subdirectory(World)

find_package(glfw3)
target_link_libraries(GLEngine PUBLIC glfw glad stb glm ${CMAKE_DL_LIBS} Shaders World)
add_library(glad STATIC)
target_sources(glad PRIVATE
    glad/include/glad/glad.h
    glad/src/glad.c
    glad/include/KHR/khrplatform.h
)

target_include_directories(glad PUBLIC glad/include/)
target_include_directories(glad PUBLIC glad)

add_library(stb STATIC)
target_sources(stb PRIVATE
    stb/stb_image.cpp
    stb/stb_image.h)

target_include_directories(stb PUBLIC stb)
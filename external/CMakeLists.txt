add_library(glad STATIC)
target_sources(glad PRIVATE
    glad/include/glad/glad.h
    glad/src/glad.c
    glad/include/KHR/khrplatform.h
)

target_include_directories(glad PUBLIC glad/include/)
target_include_directories(glad PUBLIC glad)

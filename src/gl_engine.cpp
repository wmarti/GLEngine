#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "gl_engine.h"
#include "shader.h"
#include <cmath>
#include "stb_image.h"

void GLEngine::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    _window = glfwCreateWindow(800, 600, "GLWindow", nullptr, nullptr);
    if (_window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    int bufWidth = 0;
    int bufHeight = 0;
    glfwGetFramebufferSize(_window, &bufWidth, &bufHeight);
    glViewport(0, 0, bufWidth, bufHeight);

    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
}

void GLEngine::run() {
    Shader shaders("../shaders/shader.vs", "../shaders/shader.fs");
    Shader shaders_yellow("../shaders/shader.vs", "../shaders/shader_yellow.fs");
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices1[] = {
        -0.5f,  0.5, 0.0f,  // top right
        -0.75f, 0.f, 0.0f,  // bottom right
        -0.25f, 0.f, 0.0f,  // bottom left
    };
    float vertices2[] = {
         0.5f,  0.5, 0.0f, 0.0f, 1.0f, 0.0f,
         0.75f, 0.f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.25f, 0.f, 0.0f, 0.0f, 0.0f, 1.0f,
    };
    float texCoords[] = {
        0.0f, 0.0f,  // lower-left corner  
        1.0f, 0.0f,  // lower-right corner
        0.5f, 1.0f   // top-center corner
    };
    // unsigned int indices[] = {  // note that we start from 0!
    //     0, 1, 2,   // first triangle
    //     3, 4, 5    // second triangle
    // }; 
    unsigned int VBOs[2], VAOs[2]; // EBO;
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    // glGenBuffers(1, &EBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s), 
    // and then configure vertex attributes(s)
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribte
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    shaders.setFloat("offset",0.5f);

    while(!glfwWindowShouldClose(_window)) {
        process_input(_window);
        // render
        // -----
        // draw();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        shaders.use();
        shaders.setFloat("offset",-0.2f);

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue)+1.0f)/2.0f;
        int vertexColorLocation = glGetUniformLocation(shaders.ID, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        glBindVertexArray(VAOs[0]); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);
        shaders_yellow.use();
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
}

void GLEngine::cleanup() {
    glfwTerminate();
}

void GLEngine::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void GLEngine::process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        if (!_wireframe) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            _wireframe = true;
        }
        else if (_wireframe) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            _wireframe = false;
        }
    }
}

void GLEngine::draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
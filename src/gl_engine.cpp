#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>

#include <iostream>
#include <cmath>

#include "gl_engine.h"
#include "shader.h"
#include "texture.h"
#include "gen_chunk.h"
#include "timer.h"
#include "camera.h"

glm::vec3 X_AXIS = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 Y_AXIS = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 Z_AXIS = glm::vec3(0.0f, 0.0f, 1.0f);

// settings
int width = 1920, height = 1080;
#ifdef __APPLE__
width = 1280, height = 720;
#endif

// camera
Camera camera(glm::vec3(0.0f, 3.0f, 10.0f));
float lastX = width / 2.0f;
float lastY = height / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

void GLEngine::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    _window = glfwCreateWindow(width, height, "GLWindow", nullptr, nullptr);
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

    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(_window, mouse_callback);
    glfwSetScrollCallback(_window, scroll_callback);
}

void GLEngine::run() {
    Shader _shaders("../shaders/shader.vert", "../shaders/shader.frag");
    Chunk chunk;
    chunk.build_face_data();
    glm::mat4 model = glm::mat4(1.0f);
    std::vector<std::vector<glm::mat4>> modelTransforms;
    modelTransforms.resize(6);
    //glm::mat4** modelMatrices = new glm::mat4 * [6];
    //for (int i = 0; i < 6; i++) {
    //    modelMatrices[i] = new glm::mat4[chunk.direction[i].size()];
    //}
    //int size = 0;
    //for (int i = 0; i < 6; i++)
    //    size += chunk.direction[i].size();
    //
    //glm::mat4* modelMatrices = new glm::mat4[size];
    //int offset = 0;
    //for (int i = 0; i < 6; i++) {
    //    for (int j = 0; j < chunk.direction[i].size(); j++) {
    //        model = glm::mat4(1.0f);
    //        model = glm::translate(model, chunk.direction[i][j]);
    //        /*modelMatrices[i][j] = model;*/
    //        modelTransforms[i].emplace_back(model);
    //        //modelMatrices[offset] = model;
    //        offset++;
    //    }
    //}

    std::vector<size_t> offsets = {
        {0},
        {chunk.direction[0].size()},
        {chunk.direction[0].size() + chunk.direction[1].size()},
        {chunk.direction[0].size() + chunk.direction[1].size() + chunk.direction[2].size()},
        {chunk.direction[0].size() + chunk.direction[1].size() + chunk.direction[2].size() + chunk.direction[3].size()},
        {chunk.direction[0].size() + chunk.direction[1].size() + chunk.direction[2].size() + chunk.direction[3].size() + chunk.direction[4].size()},
        //{chunk.direction[0].size() + chunk.direction[1].size() + chunk.direction[2].size() + chunk.direction[3].size() + chunk.direction[4].size() + chunk.direction[5].size()}
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(face_triangles), face_triangles, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);


    // texture coord attribute
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);


    // configure instanced array
    // -------------------------
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, chunk.direction[0].size() * sizeof(glm::vec3), &chunk.direction[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glVertexAttribDivisor(2, 1);
    //glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
    // vertex attributes
    //std::size_t vec4Size = sizeof(glm::vec4);
    //glEnableVertexAttribArray(3);
    //glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
    //glEnableVertexAttribArray(4);
    //glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
    //glEnableVertexAttribArray(5);
    //glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
    //glEnableVertexAttribArray(6);
    //glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

    //glVertexAttribDivisor(3, 1);
    //glVertexAttribDivisor(4, 1);
    //glVertexAttribDivisor(5, 1);
    //glVertexAttribDivisor(6, 1);

    glBindVertexArray(0);

    Texture grass_side("../assets/mc_grass.jpeg");
    Texture grass_top("../assets/mc_grass_top.jpeg");
    Texture dirt("../assets/mc_dirt.jpeg");

    Block grass(&grass_top, &grass_side, &dirt);

    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);


    while (!glfwWindowShouldClose(_window)) {
        glCullFace(GL_BACK);
        glFrontFace(GL_CW);
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Timer timer("Draw call");
        process_input(_window);
        // render
        // -----
        // draw();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glClear(GL_COLOR_BUFFER_BIT);
        
        // draw our first triangle
        _shaders.use();

        glm::mat4 trans = glm::mat4(1.0f);

        // Camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);

        _shaders.setMat4("transform", trans);
        _shaders.setMat4("view", view);
        _shaders.setMat4("projection", projection);

        glBindVertexArray(VAO);

        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        chunk.draw_mesh(grass, _shaders);

        for (int i = 0; i < 6; i++) {
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
            //glBufferSubData(GL_ARRAY_BUFFER, 0, chunk.direction[i].size() * sizeof(glm::mat4), &chunk.direction[i]);
            glBufferData(GL_ARRAY_BUFFER, chunk.direction[i].size() * sizeof(glm::vec3), &chunk.direction[i][0], GL_STATIC_DRAW);
            glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * 6 * i), chunk.direction[i].size());
        }

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

void GLEngine::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void GLEngine::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
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

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void GLEngine::draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
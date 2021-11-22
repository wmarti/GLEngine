#pragma once

class GLEngine {
public:
    void init();
    void run();
    void cleanup();
private:
    static void framebuffer_size_callback(struct GLFWwindow* window, int width, int height);
    void process_input(struct GLFWwindow* window);
    void draw();

private:
    struct GLFWwindow* _window;
    bool _wireframe = false;
};
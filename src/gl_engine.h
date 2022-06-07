#pragma once

class GLEngine {
public:
    void init();
    void run();
    void cleanup();
private:
    static void framebuffer_size_callback(struct GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void process_input(struct GLFWwindow* window);
    void draw();

private:
    struct GLFWwindow* _window;
    bool _wireframe = false;
};
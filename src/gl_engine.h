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
    void compile_shaders();
    void build_chunks();
    void setup_glfw_window();
    void load_texture_atlas();
    void load_gpu_data();

private:
    struct GLFWwindow* _window;
    struct TextureAtlas* _textureAtlas;
    struct Chunk* _chunk;
    struct Shader* _shaders;
    bool _wireframe = false;
};
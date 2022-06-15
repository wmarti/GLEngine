#pragma once
#include "common.h"

class Shader {
public: 
    // The program ID
    unsigned int ID;

    // Constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // Use the active shader
    void use();
    // Utility uniform functions
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string& name, glm::mat4& value) const;
    void setVec2(const std::string& name, glm::vec2& value) const;
};
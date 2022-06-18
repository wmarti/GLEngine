#pragma once

// Standard Library Includes
#include <assert.h>
#include <array>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>


// 3rd Party Library Includes
// 
// this is to force the formatter to keep the order, because glad must be included first
#if 1
#include <glad/glad.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>

// Block Vertex and Face orientation/positioning information
static float vertices[40] = {
    // x     y     z      u     v
      //   back
     -0.5, -0.5, -0.5,   0.0f, 0.0f, // bottom-left  0
     -0.5,  0.5, -0.5,   0.0f, 1.0f, // top-left     1
      0.5, -0.5, -0.5,   1.0f, 0.0f, // bottom-right 2
      0.5,  0.5, -0.5,   1.0f, 1.0f, // top-right    3
      //   front         
     -0.5, -0.5,  0.5,   0.0f, 0.0f, // bottom-left  4
     -0.5,  0.5,  0.5,   0.0f, 1.0f, // top-left     5
      0.5, -0.5,  0.5,   1.0f, 0.0f, // bottom-right 6
      0.5,  0.5,  0.5,   1.0f, 1.0f, // top-right    7
};

static unsigned int face_triangles[36] = {
    // North
      2, 3, 1, // CW
      2, 1, 0, // CW
    // East
      6, 7, 3, // CW
      6, 3, 2, // CW
    // South
      4, 5, 7, // CW
      4, 7, 6, // CW
    // West
      0, 1, 5, // CW
      0, 5, 4, // CW
    //  Up
      5, 1, 3, // CW
      5, 3, 7, // CW
    // Down
      0, 4, 6, // CW
      0, 6, 2, // CW
};


static float cubeVertices[] = {
    // Back face
      0.5, -0.5, -0.5,   1.0f, 0.0f, // bottom-right 2
      0.5,  0.5, -0.5,   1.0f, 1.0f, // top-right    3   
     -0.5,  0.5, -0.5,   0.0f, 1.0f, // top-left     1
      0.5, -0.5, -0.5,   1.0f, 0.0f, // bottom-right 2
     -0.5,  0.5, -0.5,   0.0f, 1.0f, // top-left     1
     -0.5, -0.5, -0.5,   0.0f, 0.0f, // bottom-left  0
    // Right face
      0.5, -0.5,  0.5,   0.0f, 0.0f, // bottom-right 6
      0.5,  0.5,  0.5,   0.0f, 1.0f, // top-right    7
      0.5,  0.5, -0.5,   1.0f, 1.0f, // top-right    3
      0.5, -0.5,  0.5,   0.0f, 0.0f, // bottom-right 6
      0.5,  0.5, -0.5,   1.0f, 1.0f, // top-right    3
      0.5, -0.5, -0.5,   1.0f, 0.0f, // bottom-right 2
    // Front face
     -0.5, -0.5,  0.5,   0.0f, 0.0f, // bottom-left  4
     -0.5,  0.5,  0.5,   0.0f, 1.0f, // top-left     5
      0.5,  0.5,  0.5,   1.0f, 1.0f, // top-right    7
     -0.5, -0.5,  0.5,   0.0f, 0.0f, // bottom-left  4
      0.5,  0.5,  0.5,   1.0f, 1.0f, // top-right    7
      0.5, -0.5,  0.5,   1.0f, 0.0f, // bottom-right 6
    // Left face
     -0.5, -0.5, -0.5,   0.0f, 0.0f, // bottom-left  0
     -0.5,  0.5, -0.5,   0.0f, 1.0f, // top-left     1
     -0.5,  0.5,  0.5,   1.0f, 1.0f, // top-left     5
     -0.5, -0.5, -0.5,   0.0f, 0.0f, // bottom-left  0
     -0.5,  0.5,  0.5,   1.0f, 1.0f, // top-left     5
     -0.5, -0.5,  0.5,   1.0f, 0.0f, // bottom-left  4
    // Top face
     -0.5,  0.5,  0.5,   0.0f, 0.0f, // top-left     5
     -0.5,  0.5, -0.5,   0.0f, 1.0f, // top-left     1
      0.5,  0.5, -0.5,   1.0f, 1.0f, // top-right    3
     -0.5,  0.5,  0.5,   0.0f, 0.0f, // top-left     5
      0.5,  0.5, -0.5,   1.0f, 1.0f, // top-right    3
      0.5,  0.5,  0.5,   1.0f, 0.0f, // top-right    7
    // Bottom face          
     -0.5, -0.5, -0.5,   0.0f, 0.0f, // bottom-left  0
     -0.5, -0.5,  0.5,   0.0f, 1.0f, // bottom-left  4
      0.5, -0.5,  0.5,   1.0f, 1.0f, // bottom-right 6
     -0.5, -0.5, -0.5,   0.0f, 0.0f, // bottom-left  0
      0.5, -0.5,  0.5,   1.0f, 1.0f, // bottom-right 6
      0.5, -0.5, -0.5,   1.0f, 0.0f, // bottom-right 2
};


static float uv_coords[8] = {
    0.0f, 0.0f, // bottom-left  0
    0.0f, 1.0f, // top-left     1
    1.0f, 0.0f, // bottom-right 2
    1.0f, 1.0f, // top-right    3
};

static unsigned int uv_indices[24] = {
    2,
};
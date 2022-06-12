#pragma once
#include <array>
#include <vector>

#include <glm/glm.hpp>


static float vertices[24] = {
  // x     y     z
    //   back
   -0.5, -0.5, -0.5, // bottom-left  0
   -0.5,  0.5, -0.5, // top-left     1
    0.5, -0.5, -0.5, // bottom-right 2
    0.5,  0.5, -0.5, // top-right    3
    //   front
   -0.5, -0.5,  0.5, // bottom-left  4
   -0.5,  0.5,  0.5, // top-left     5
    0.5, -0.5,  0.5, // bottom-right 6
    0.5,  0.5,  0.5, // top-right    7
};
/*
static unsigned int face_triangles[36] = {
  // North
    0, 1, 3,
    0, 2, 3,
  // East
    6, 7, 3,
    6, 2, 3,
  // South
    4, 5, 7,
    4, 6, 7,
  // West
    0, 1, 5,
    0, 4, 5,
  //  Up
    5, 1, 3,
    5, 7, 3,
  // Down
    4, 0, 2,
    4, 6, 2
};
*/
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

/*
static unsigned int face_triangles[36] = {
    // North
      0, 1, 3, // CW
      0, 3, 2, // CW
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
*/
//static float triangle_vertices[] = {
//     0.5f,  0.5f, 0.0f,  // top right
//     0.5f, -0.5f, 0.0f,  // bottom right
//    -0.5f, -0.5f, 0.0f,  // bottom left
//    -0.5f,  0.5f, 0.0f   // top left 
//};
//
//static unsigned int indices[] = {  // note that we start from 0!
//    0, 1, 3,   // first triangle
//    1, 2, 3    // second triangle
//};
//
//static float vertices[] = {
//    // North Face
//    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-Left
//     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // Bottom-Right
//
//     
//};
//
//static float vertices[] = {
//    // Back face
//    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
//     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right    
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right              
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
//    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
//    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left                
//    // Front face
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
//     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
//     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right        
//     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
//    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left        
//    // Left face
//    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
//    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left       
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
//    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
//    // Right face
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right      
//     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right          
//     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
//     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
//    // Bottom face          
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
//     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
//     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left        
//     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
//    // Top face
//    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right                 
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
//    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // bottom-left  
//    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f  // top-left              
//};

/* Also make sure to add a call to OpenGL to specify that triangles defined by a clockwise ordering
   are now 'front-facing' triangles so the cube is rendered as normal:
   glFrontFace(GL_CW);
*/
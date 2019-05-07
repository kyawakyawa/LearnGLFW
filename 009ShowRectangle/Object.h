#pragma once
#include <GL/glew.h>

class Object {
  // Vertex Array Object
  GLuint vao;
  // Vertex buffer Object
  GLuint vbo;

public:

  Object(const Object &o) = delete;
  Object &operator=(const Object &o) = delete;

  struct Vertex  {
    GLfloat position[2];
  };

  Object(GLint size, GLsizei vertexcount, const Vertex *vertex);
  virtual ~Object();

  void bind() const;
};
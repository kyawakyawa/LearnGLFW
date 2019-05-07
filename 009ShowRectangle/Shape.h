#pragma once
#include <memory>

#include "Object.h"

class Shape {
  std::shared_ptr<const Object> object;

protected:
  const GLsizei vertexcount;

public:
  Shape(GLint size, GLsizei vertexcount, const Object:: Vertex *vertex) ;
  virtual ~Shape();

  void draw() const;

  virtual void execute() const;
};
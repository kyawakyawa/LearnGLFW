#include "Shape.h"


Shape::Shape(GLint size, GLsizei vertexcount, const Object:: Vertex *vertex) 
  : object(new Object(size, vertexcount, vertex)),
    vertexcount(vertexcount) {};

Shape::~Shape(){};

void Shape::draw() const {
  object->bind();
  execute();
}

void Shape::execute() const {
  glDrawArrays(GL_LINE_LOOP, 0, vertexcount);
}

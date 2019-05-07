#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <memory>
#include <GL/glew.h> // include before glfw3.h
#include <GLFW/glfw3.h>
#include "Shape.h"

// print shader object compiler output
GLboolean PrintShaderObjectCompilerOutput(
    GLuint shader_obj,
    const char *shader_name// str which teaches where compile error occur
    ) {

  // fecth the result of compile
  GLint status;
  glGetShaderiv(shader_obj, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) fprintf(stderr, "Compile Error in %s\n",shader_name);

  // fetch the length of the log of shader compiler
  GLsizei buf_size;
  glGetShaderiv(shader_obj, GL_INFO_LOG_LENGTH, &buf_size);

  if (buf_size >= 1) {
    // fetch the log
    std::unique_ptr<GLchar> info_log(new GLchar[buf_size]);
    GLsizei length;
    glGetShaderInfoLog(shader_obj, buf_size, &length, info_log.get());
    fprintf(stderr, "%s\n", info_log.get());
  }

  if (status) fprintf(stderr, "success compiling shader object %s\n", shader_name);

  return static_cast<GLboolean>(status);
}

// print program object linker output
GLboolean PrintProgramObjectLinkerOutput(GLuint program_object) {

  // fetch the result of link
  GLint status;
  glGetProgramiv(program_object, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) fprintf(stderr, "Link Error\n");

  // fetch the length of the log of program linker
  GLsizei buf_size;
  glGetProgramiv(program_object, GL_INFO_LOG_LENGTH, &buf_size);

  if (buf_size > 0) {
    // fetch the log
    std::unique_ptr<GLchar> info_log(new GLchar[buf_size]);
    GLsizei length;
    glGetProgramInfoLog(program_object, buf_size, &length, info_log.get());
    fprintf(stderr, "%s\n", info_log.get());
  }

  if (status) fprintf(stderr, "success linking program object\n");

  return static_cast<GLboolean>(status);
}

GLuint CreateProgramObject(const GLchar* vertex_shader_source,  // Str of vertex shader source
                           const GLchar* fragment_shader_source // Str of fragment shader source
    ) {

  // create a empty program object
  const GLuint program_obj(glCreateProgram());

  bool error_flag = false;

  if (vertex_shader_source != NULL) {
    // Create a vertex shader object
    const GLuint vertex_shader_obj(glCreateShader(GL_VERTEX_SHADER));
    glShaderSource(vertex_shader_obj, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader_obj);

    // TODO : comment
    if (PrintShaderObjectCompilerOutput(vertex_shader_obj, "vertex shader")) {
      glAttachShader(program_obj, vertex_shader_obj);
    } else {
      error_flag = true;
    }
    glDeleteShader(vertex_shader_obj);
  }

  if (fragment_shader_source != NULL) {
    const GLuint fragment_shader_obj(glCreateShader(GL_FRAGMENT_SHADER));
    glShaderSource(fragment_shader_obj, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader_obj);

    // TODO : comment
    if (PrintShaderObjectCompilerOutput(fragment_shader_obj, "fragment shader")) {
      glAttachShader(program_obj, fragment_shader_obj);
    } else {
      error_flag = true;
    }
    glDeleteShader(fragment_shader_obj);
  }

  if (error_flag) {
    glDeleteProgram(program_obj);
    return 0;
  }

  // link program object 
  glBindAttribLocation  (program_obj, 0, "position");
  glBindFragDataLocation(program_obj, 0, "fragment");
  glLinkProgram(program_obj);

  if (PrintProgramObjectLinkerOutput(program_obj)) {
    return program_obj;
  }

  // return 0 if failed creating proram object
  glDeleteProgram(program_obj);
  return 0;
}

bool ReadShaderSource(const char *source_filename,
                      const uint64_t max_source_size, char *source) {
  if (source_filename == NULL) return false;

  // open source file
  std::ifstream file(source_filename, std::ios::binary);
  if (file.fail()) {
    fprintf(stderr, "failed openning a shader source file: %s\n", source_filename);
    return false;
  }

  file.seekg(0L, std::ios::end); // move to end of the file
  GLsizei length = static_cast<GLsizei>(file.tellg()/*present locaton*/);

  if (length >= max_source_size) {
    fprintf(stderr, "failed read a shader source file. the source file is too long: %s\n",source_filename);
    file.close();
    return false;
  }

  file.seekg(0L, std::ios::beg/*begin*/);
  file.read(source, length);
  source[length] = '\0';

  if (file.fail()) {
    fprintf(stderr, "failed read a shader source file: %s\n",source_filename);
    file.close();
    return false;
  }

  fprintf(stderr, "success reading shader source: %s\n", source_filename);

  file.close();
  return true;
}

GLuint LoadProgram(const char *vertex_source_filename,
                   const char *fragment_source_filename,
                   const uint64_t max_source_size = 100000) {

  char vertex_source[max_source_size];
  char fragment_source[max_source_size];

  const bool vret = ReadShaderSource(vertex_source_filename, max_source_size, vertex_source);
  const bool fret = ReadShaderSource(fragment_source_filename, max_source_size, fragment_source);

  return (vret && fret) ? CreateProgramObject(vertex_source, fragment_source) : 0; 
}

// Rectangle's vertices place
constexpr Object::Vertex rectangleVertices[] =
{
  { -0.5f, -0.5f },
  {  0.5f, -0.5f },
  {  0.5f,  0.5f },
  { -0.5f,  0.5f }
};

int main() {
  if (glfwInit() == GL_FALSE) {
    fprintf(stderr, "failed initializing GLFW.\n");
    return 1;
  }

  fprintf(stderr, "success initializing GLFW.\n");

  // register terminating process 
  atexit(glfwTerminate);

  // Select OpenGL Version 3.2 Core Profile before Create Window
  // If you want to use default setting , you should use glfwDefaultWindowHints() function.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  //Create Window
  GLFWwindow *const window(glfwCreateWindow(640, 480, "Test Window", NULL, NULL));
  if (window == NULL) {
    fprintf(stderr, "failed creating GLFW window.\n");
    return 1;
  }

  fprintf(stderr, "success openning GLFW.\n");

  // Target window
  glfwMakeContextCurrent(window);

  // Init GLEW after making glfw's window
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "failed initializing GLEW.\n");
  }
  fprintf(stderr, "success initializing GLEW.\n");

  // Set Buffer Swap Timing
  glfwSwapInterval(1);

  // Select Background Color
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

  // Set Viewport
  glViewport(100, 50, 300, 300);

  // create program object 
  const GLuint program_obj(LoadProgram("../point.vert", "../point.frag"));

  if (program_obj == 0) {
    fprintf(stderr ,"faild load program object\n");
    return -1;
  }

  // Make Shape Data
  std::unique_ptr<const Shape> shape(new Shape(2, 4, rectangleVertices));

  // When the window is open
  while (glfwWindowShouldClose(window) == GL_FALSE) {
    // Clear Buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // start shader program
    glUseProgram(program_obj);

    // Draw Shape
    shape->draw();

    //
    // writing process
    //
    // exchange color buffer
    glfwSwapBuffers(window);
    // Fetch Event
    glfwWaitEvents();
  }

  fprintf(stderr, "reaching the end of the main function\n");

  return 0;
}

#include <stdio.h>
#include <stdlib.h>

#include "Window.h"

static void Resize(GLFWwindow *const window, int width, int height); 

Window::Window(int width, int height, const char *title)
: window(glfwCreateWindow(width, height, title, nullptr, nullptr)) {
  //Create Window
  if (window == nullptr) {
    fprintf(stderr, "failed creating GLFW window.\n");
    exit(1);
  }
  fprintf(stderr, "success openning GLFW.\n");

  // make this window target
  glfwMakeContextCurrent(window);

  // Init GLEW after making glfw's window
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "failed initializing GLEW.\n");
  }
  fprintf(stderr, "success initializing GLEW.\n");

  // Set Buffer Swap Timing
  glfwSwapInterval(1);

  // register "this" pointer in this instance
  glfwSetWindowUserPointer(window, this);

  // Register Callback funtion that is called when window size is changed
  glfwSetWindowSizeCallback(window, Resize);

  // initial setting of window
  Resize(window, width, height);
} 
Window::~Window() {
  glfwDestroyWindow(window);
}
  // Determine if the window should be closed
int Window::ShouldClose() const {
  return glfwWindowShouldClose(window);
}
// Fetch event with swapping color buffer
void Window::SwapBuffers() {
  // swap color buffer
  glfwSwapBuffers(window);
  // Fetch event
  glfwWaitEvents();
}

GLfloat Window::GetAspect() const {return aspect;}
GLfloat& Window::GetRefAspect() {return aspect;}

// this function called when window size is changed
static void Resize(GLFWwindow *const window, int width, int height) {
  // Set the entire window as a viewport
  glViewport(0, 0, width, height);

  // Fetch "this" pointer int this instance
  Window *const instance(static_cast<Window *>(glfwGetWindowUserPointer(window)));

  if (instance != nullptr) {
    // update aspect
    instance->GetRefAspect() = static_cast<GLfloat>(width) / static_cast<GLfloat>(height);
  }
}
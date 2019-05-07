#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
  // handle(pointer) of window
  GLFWwindow *const window;
public:
  Window() = delete;
  Window(int width, int height, const char *title);

  virtual ~Window();
  // Determine if the window should be closed
  int ShouldClose() const;
  // Fetch event with swapping color buffer
  void SwapBuffers();
};
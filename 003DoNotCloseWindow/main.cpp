#include <stdio.h>
#include <GLFW/glfw3.h>
int main() {
  if (glfwInit() == GL_FALSE) {
    printf("failed initializing GLFW.\n");
    return 1;
  }

  printf("success initializing GLFW.\n");

  GLFWwindow *const window(glfwCreateWindow(640, 480, "Test Window", NULL, NULL));
  if (window == NULL) {
    printf("failed creating GLFW window.\n");
    return 1;
  }

  printf("success openning GLFW.\n");

  // Target window
  glfwMakeContextCurrent(window);
  // Select Background Color
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  // When the window is open
  while (glfwWindowShouldClose(window) == GL_FALSE) {
    // Clear Buffer
    glClear(GL_COLOR_BUFFER_BIT);
    //
    // writing process
    //
    // exchange color buffer
    glfwSwapBuffers(window);
    // Fetch Event
    glfwWaitEvents();
  }

  return 0;
}

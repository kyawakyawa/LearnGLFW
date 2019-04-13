#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h> // include before glfw3.h
#include <GLFW/glfw3.h>
int main() {
  if (glfwInit() == GL_FALSE) {
    printf("failed initializing GLFW.\n");
    return 1;
  }

  printf("success initializing GLFW.\n");

  // register terminating process 
  atexit(glfwTerminate);

  //Create Window
  GLFWwindow *const window(glfwCreateWindow(640, 480, "Test Window", NULL, NULL));
  if (window == NULL) {
    printf("failed creating GLFW window.");
    return 1;
  }

  printf("success openning GLFW.\n");

  // Target window
  glfwMakeContextCurrent(window);

  // Init GLEW after making glfw's window
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    printf("failed initializing GLEW.\n");
  }
  printf("success initializing GLEW.\n");

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

  printf("reaching the end of the main function\n");

  return 0;
}

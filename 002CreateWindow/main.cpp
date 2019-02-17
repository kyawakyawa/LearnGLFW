#include <stdio.h>
#include <GLFW/glfw3.h>
int main() {
  if (glfwInit() == GL_FALSE) {
    printf("failed initializing GLFW.\n");
    return 1;
  }

  printf("success initializing GLFW.\n");

  GLFWwindow *const window(glfwCreateWindow(640, 480, "Hello!", NULL, NULL));
  if (window == NULL) {
    printf("failed creating GLFW window.");
    return 1;
  }

  printf("success openning GLFW.\n");

  return 0;
}

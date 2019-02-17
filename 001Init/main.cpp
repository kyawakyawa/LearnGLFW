#include <iostream>
#include <GLFW/glfw3.h>
int main() {
 if (glfwInit() == GL_FALSE) {
   printf("failed initializing GLFW\n");
   return 1;
 }

 printf("success initializing GLFW\n");

 return 0;
}

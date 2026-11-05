#include <iostream>

#include <GLFW/glfw3.h>

int main(int, char **)
{
    GLFWwindow *window;

    if (!glfwInit())
    {
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(640, 480, "Learn OpenGL", NULL, NULL);
    if (!window)
    {
        std::cerr << "Window can't be created" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window))
    {
        std::cout << "Running our window" << std::endl;

        glfwPollEvents();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "render.h"
#include "shader.h"

#define WIDTH 512
#define HEIGHT 512

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void loop(GLFWwindow* window);


void init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Algorithm Visualizer", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        
        }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }   
 
    Shader shade("src/rect.vs", "src/rect.fs");

    loop(window);
} 

void loop(GLFWwindow* window) {
    int elements[] = {1, 3, 2};
    Shader rect("src/rect.vs", "src/rect.fs");

    while(!glfwWindowShouldClose(window)) {
        //The classic functions
        glfwSwapBuffers(window);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        rect.use();
        renderArray(elements);
        
        glfwPollEvents();  

    }
    glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    
}

void renderArray(int elements[]) {
    unsigned int VBO, VAO;

    float vertices[10];
    vertices[0] = 4.0f;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);



}
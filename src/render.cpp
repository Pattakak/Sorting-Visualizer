#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "render.h"
#include "shader.h"

#define WIDTH 1024
#define HEIGHT 1024

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void loop(GLFWwindow* window);
void shitSort(int* elements, int arrLength);

GLFWwindow  *window; 
unsigned int VBO, VAO;

void init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Algorithm Visualizer", NULL, NULL);
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

} 

void loop(int array[], int arrLength) {
    int elements[] = {1, 3, 2};
    Shader rect("src/rect.vs", "src/rect.fs");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    while(!glfwWindowShouldClose(window)) {
        //The classic functions
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        shitSort(array, arrLength);
        //VAO = 
        renderArray(array, arrLength); //Update VAO Graphics
        rect.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6 * arrLength); //The last number is the number of elements times 6 because each rectangle has 6 vertices
        
        glfwSwapBuffers(window);
        glfwPollEvents();  

    }
    glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    
}

unsigned int renderArray(int elements[], int arrLength) {
    //int testElement[] = {1, 3, 2, 0, 4};
    //int arrLength = sizeof(elements) / sizeof(int);
    float vertices[arrLength * 2 * 6]; // 2 dimensional point, 6 points for each 2 triangles (1 rectangle)

    float xLeft, xRight, height; //Temporary variables that change each loop

    for (int i = 0; i < arrLength; i++){
        xLeft = -1.0f + 2.0f * ((float) i) / ((float) arrLength);
        xRight = xLeft + 2.0f / (float) arrLength;
        height = -1.0f + 2.0f * (float) elements[i] / (float) arrLength;

        vertices[12 * i + 0] = xLeft; //Bottom Left
        vertices[12 * i + 1] = -1.0f;
        vertices[12 * i + 2] = xRight; //Bottom Right
        vertices[12 * i + 3] = -1.0f;
        vertices[12 * i + 4] = xLeft; //Top Left
        vertices[12 * i + 5] = height;
        vertices[12 * i + 6] = xRight; //Top Right
        vertices[12 * i + 7] = height;
        vertices[12 * i + 8] = xLeft; //Top Left
        vertices[12 * i + 9] = height;
        vertices[12 * i + 10] = xRight; //Bottom Right
        vertices[12 * i + 11] = -1.0f;
    }

    for (int i = 0; i < arrLength *2 * 6; i++) {
        //std::cout << vertices[i] << std::endl;
    }
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindVertexArray(VAO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    return VAO;

}

//This method should not be kept, but I know that it will stay for a while
//This is a quick implementation that will not show all of the steps
//More work should be done to actually show more algorithms
void shitSort(int *elements, int arrLength) {
    for (int i = 0; i < arrLength - 1; i++) {
        if (elements[i] > elements[i + 1]) {
            int p = elements[i+1]; //Placeholder
            elements[i+1] = elements[i];
            elements[i] = p;
        }
    }
}
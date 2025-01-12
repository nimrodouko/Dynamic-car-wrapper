#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"


void change_bordersize(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);




int main(void)

{

    /* Initialize the library */

    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window;



    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "car wrapper project", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, change_bordersize);
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        std::cout<<"failed to initialize glad"<<std::endl;
        return -1;
    };

    Shader shader("./vertexshader.txt","./fragmentshader.txt");




    float vertices[] = {
       
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    
    };
    unsigned int VBO,VAO;
    glGenVertexArrays(1, &VAO);
    

    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

   


    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
  
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0, 3);
        shader.use();



        
        
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        processInput(window);
        glfwPollEvents();


    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    

  

    glfwTerminate();
    return 0;
}
void change_bordersize(GLFWwindow* window, int width, int height) {

    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
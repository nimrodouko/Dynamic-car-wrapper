#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void change_bordersize(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xposition, double yposition);
void scroll_back(GLFWwindow* window, double xoffset, double yoffset);


glm::vec3 cameraposition = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 camerafront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraup = glm::vec3(0.0f, 1.0f, 0.0f);

float deltatime = 0.0f;
float lastframe = 0.0f;

float yaw = -90.0f;
float pitch = 0.0f;
float fov = 45.0f;


double lastx = 400.0f;
double lasty = 300.0f;

bool mouseentry{ true };

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
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_back);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  
   
    glm::vec3 cameratarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameradirection = glm::normalize(cameraposition - cameratarget);
    //right axis
 
    glm::vec3 cameraright = glm::cross(cameraup, cameradirection);




    Shader shader("./vertexshader.txt","./fragmentshader.txt");



    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,1.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,1.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f,
    };

   
    glm::vec3 cubepositions[] = {
            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(2.0f,  2.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f,  2.0f, -2.5f),
            glm::vec3(1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    float lightvertices[] = {
        -0.5f, -1.0f, -0.5f,  1.0f, 1.0f,1.0f,
         0.5f,  -1.0f, -0.5f,   1.0f, 1.0f,1.0f,
         0.5f,   1.0f, -0.5f,   1.0f, 1.0f,1.0f,
         0.5f,   1.0f, -0.5f,   1.0f, 1.0f,1.0f,
        -0.5f,   1.0f, -0.5f,  1.0f, 1.0f,1.0f,
        -0.5f,  -0.0f, -0.5f,   1.0f, 1.0f,1.0f,

        -0.5f,  -1.0f,  0.5f,   1.0f, 1.0f,1.0f,
         0.5f,  -1.0f,  0.5f,   1.0f, 1.0f,1.0f,
         0.5f,   1.0f,  0.5f,  1.0f, 1.0f,1.0f,
         0.5f,   1.0f,  0.5f,  1.0f, 1.0f,1.0f,
        -0.5f,   1.0f,  0.5f,   1.0f, 1.0f,1.0f,
        -0.5f,  -1.0f,  0.5f,  1.0f, 1.0f,1.0f,

        -0.5f,   1.0f,  0.5f,   1.0f, 1.0f,1.0f,
        -0.5f,   1.0f, -0.5f,  1.0f, 1.0f,1.0f,
        -0.5f,  -1.0f, -0.5f, 1.0f, 1.0f,1.0f,
        -0.5f,  -1.0f, -0.5f,  1.0f, 1.0f,1.0f,
        -0.5f,  -1.0f,  0.5f, 1.0f, 1.0f,1.0f,
        -0.5f,   1.0f,  0.5f,  1.0f, 1.0f,1.0f,

         0.5f,   1.0f,  0.5f,  1.0f, 1.0f,1.0f,
         0.5f,   1.0f, -0.5f,  1.0f, 1.0f,1.0f,
         0.5f,  -1.0f, -0.5f,  1.0f, 1.0f,1.0f,
         0.5f,  -1.0f, -0.5f,   1.0f, 1.0f,1.0f,
         0.5f,  -1.0f,  0.5f,   1.0f, 1.0f,1.0f,
         0.5f,   1.0f,  0.5f,  1.0f, 1.0f,1.0f,

        -0.5f,  -1.0f, -0.5f, 1.0f, 1.0f,1.0f,
         0.5f,  -1.0f, -0.5f,  1.0f, 1.0f,1.0f,
         0.5f,  -1.0f,  0.5f,   1.0f, 1.0f,1.0f,
         0.5f,  -1.0f,  0.5f,   1.0f, 1.0f,1.0f,
        -0.5f,  -1.0f,  0.5f,   1.0f, 1.0f,1.0f,
        -0.5f,  -1.0f, -0.5f,  1.0f, 1.0f,1.0f,

        -0.5f,   1.0f, -0.5f,  1.0f, 1.0f,1.0f,
         0.5f,   1.0f, -0.5f,  1.0f, 1.0f,1.0f,
         0.5f,   1.0f,  0.5f,  1.0f, 1.0f,1.0f,
         0.5f,   1.0f,  0.5f,   1.0f, 1.0f,1.0f,
        -0.5f,   1.0f,  0.5f,  1.0f, 1.0f,1.0f,
        -0.5f,   1.0f, -0.5f,  1.0f, 1.0f,1.0f,
    
    };

    unsigned int VBO,VAO, lightVAO, lightVBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glGenBuffers(1, &lightVBO);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lightvertices), lightvertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    
    glm::vec4 telephone(1.0f, 2.0f, 2.0f, 1.0f);
    glm::mat4 trans(1.0f);
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    telephone = trans * telephone;
    std::cout << telephone.x << telephone.y << telephone.z << std::endl;

    std::cout << "-------------------" << std::endl;

    
    

    while (!glfwWindowShouldClose(window))
    {
        float currentframe = glfwGetTime();
        deltatime = currentframe - lastframe;
        lastframe = currentframe;

        glEnable(GL_DEPTH_TEST);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  
   

        
        shader.use();
      

        glm::mat4 view;
        view = glm::lookAt(cameraposition, cameraposition + camerafront, cameraup);


        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);

       


        unsigned int viewloc = glGetUniformLocation(shader.ID, "view");
        glUniformMatrix4fv(viewloc, 1, GL_FALSE, glm::value_ptr(view));


        unsigned int projectionloc = glGetUniformLocation(shader.ID, "projection");
        glUniformMatrix4fv(projectionloc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
     
        
        for (unsigned int i = 0; i < 10;i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubepositions[i]);
            float angle = 20.0f * i;
            if (i % 3 == 0) {
                angle = glfwGetTime() * 25.0f;
            }
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
           
            unsigned int modelloc = glGetUniformLocation(shader.ID, "model");
            glUniformMatrix4fv(modelloc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);

        }
        glBindVertexArray(lightVAO);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model , glm::vec3(0.0f, 5.0f,0.0f));
        unsigned int modellocation = glGetUniformLocation(shader.ID, "model");
        glUniformMatrix4fv(modellocation, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
       

        


        

        
        
        
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

    const float cameraspeed = 5.5f * deltatime;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraposition -= cameraspeed * camerafront;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraposition += cameraspeed * camerafront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraposition -= cameraspeed * glm::normalize(glm::cross(camerafront, cameraup));
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraposition += cameraspeed * glm::normalize(glm::cross(camerafront, cameraup));

}
void mouse_callback(GLFWwindow* window, double xposition, double yposition) {

    if (mouseentry) {
        lastx = xposition;
        lasty = yposition;
        mouseentry = false;
    }
 

    float xoffset = xposition - lastx;
    float yoffset = lasty - yposition;
    const float sensitivity =0.04f;
    xoffset = xoffset * sensitivity;
    yoffset = yoffset * sensitivity;

    yaw = yaw + xoffset;
    pitch = pitch + yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw));
    direction.z = sin(glm::radians(yaw));

    direction.y = sin(glm::radians(pitch));
    camerafront = glm::normalize(direction);

}

void scroll_back(GLFWwindow* window, double xoffset, double yoffset) {
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}


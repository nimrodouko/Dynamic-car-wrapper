#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>

void change_bordersize(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
const char* vertexshadersource = "#version 330 core\n"
"layout (location =0) in vec3 apos; \n"
"void main()\n"
"{\n"
"gl_Position = vec4(apos.x, apos.y, apos.z, 1.0);\n"
"}\0";

const char* fragmentshadersource = "#version 330 core\n"
"out vec4 fragcolor;\n"
"void main()\n"
"{\n"
"fragcolor = vec4(1.0f,0.5f,0.2f, 1.0f);\n"
"}\0";


const char* danger = "#version 330 core\n"
"out vec4 fragcolor;\n"
"void main()\n"
"{\n"
"fragcolor = vec4(0.4f,0.5f,0.2f, 1.0f);\n"
"}\0";

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

    unsigned int vertexshader;
    vertexshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexshader, 1, &vertexshadersource, NULL);
    glCompileShader(vertexshader);

    unsigned int fragmentshader;
    fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentshader, 1, &fragmentshadersource, NULL);
    glCompileShader(fragmentshader);

    unsigned int secondfragmentshader;
    secondfragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(secondfragmentshader, 1 ,&danger, NULL);
    glCompileShader(secondfragmentshader);

    unsigned int shaderprogram;
    shaderprogram = glCreateProgram();
    glAttachShader(shaderprogram, vertexshader);
    glAttachShader(shaderprogram, fragmentshader);
    glLinkProgram(shaderprogram);

    unsigned int shaderprogram1;
    shaderprogram1 = glCreateProgram();
    glAttachShader(shaderprogram1, vertexshader);
    glAttachShader(shaderprogram1, secondfragmentshader);
    glLinkProgram(shaderprogram1);


    float vertices[] = {
        // first triangle
        -0.9f, -0.5f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top 
       
    
    };
    float second[] = {
         0.0f, -0.5f, 0.0f,  // left
         0.9f, -0.5f, 0.0f,  // right
         0.45f, 0.5f, 0.0f   // top 
    };
   
    unsigned int VBO,VBO1,VAO, VAO1;
    glGenVertexArrays(1, &VAO);
    glGenVertexArrays(1, &VAO1);

    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

   
    glBindVertexArray(VAO1);
    glGenBuffers(1, &VBO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(second), second, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    int nr;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nr);
    std::cout << nr << std::endl;


    

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderprogram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0, 3);
       


        glUseProgram(shaderprogram1);
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        processInput(window);
        glfwPollEvents();


    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    

    glDeleteProgram(shaderprogram);

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
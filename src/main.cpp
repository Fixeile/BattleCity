#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "Renderer/ShaderProgram.h"
#include "Resources/ResourcesManager.h"
#include "Renderer/Texture2D.h"

using namespace std;
using namespace glm;

GLfloat point[] = {
    0.0f, 50.f, 0.0f,
    50.f, -50.f, 0.0f,
   -50.f, -50.f, 0.0f
};

GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

GLfloat TextureColors[] = {
    0.5f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f
};

glm::vec2 g_windowSize(640, 480);

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    g_windowSize.x = width;
    g_windowSize.y = height;
    glViewport(0, 0, g_windowSize.x, g_windowSize.y);
}

void glfwKeyCallback(GLFWwindow* pWindow, int Key, int scancode, int action, int mode)
{
    if (Key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}

int main(int argc, char** argv)
{

    if (!glfwInit())
    {
        cout << "glfwInit failed!" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    
    GLFWwindow* pWindow = glfwCreateWindow(g_windowSize.x, g_windowSize.y, "Battle-City", nullptr, nullptr);
    if (!pWindow)
    {
        cout << "glfwCreateWindow failed!" << endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL()) {
        cout << "Cant load GLAD!" << endl;
        return -1;
    }

    cout << "Rendere: " << glGetString(GL_RENDERER) << endl;
    cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;

    glClearColor(1, 1, 0, 1);

    {
        ResourcesManager resourcesManager(argv[0]);
        auto pDefaultShaderProgram = resourcesManager.loadShaders("DefoultShader", "ressurs/Shaders/vertex.txt", "ressurs/Shaders/fragment.txt");
        if (!pDefaultShaderProgram)
        {
            cerr << "Can`t create Shader program: " << "DefoultShader" << endl;
            return -1;
        }

        auto tex = resourcesManager.loadTexture("DefouldTexture", "ressurs/Textures/map_16x16.png");

        GLuint points_vbo = 0;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

        GLuint colors_vbo = 0;
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        GLuint TextureColors_vbo = 0;
        glGenBuffers(1, &TextureColors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, TextureColors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(TextureColors), TextureColors, GL_STATIC_DRAW);

        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, TextureColors_vbo);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        pDefaultShaderProgram->use();
        pDefaultShaderProgram->setInt("tex", 0);

        mat4 modeMatrix_1 = mat4(1.f);
        modeMatrix_1 = translate(modeMatrix_1, vec3(100.f, 50.f, 0.f ));

        mat4 modeMatrix_2 = mat4(1.f);
        modeMatrix_2 = translate(modeMatrix_2, vec3(590.f, 50.f, 0.f));

        mat4 projectivMatrix = ortho(0.f, static_cast<float>(g_windowSize.x), 0.f, static_cast<float>(g_windowSize.y), -100.f, 100.f);

        pDefaultShaderProgram->setMatrix4("projectionMat", projectivMatrix);

        while (!glfwWindowShouldClose(pWindow))
        {

            glClear(GL_COLOR_BUFFER_BIT);

            pDefaultShaderProgram->use();
            glBindVertexArray(vao);
            tex->bind();

            pDefaultShaderProgram->setMatrix4("modelMat", modeMatrix_1);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            pDefaultShaderProgram->setMatrix4("modelMat", modeMatrix_2);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(pWindow);



            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}
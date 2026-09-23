#include "Renderer.h"
#include "Window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

 static ShaderProgramSource ParseShader(const std::string& filepath)
{
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::ifstream stream(filepath);

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss [(int)type] << line << '\n';
        }
    }
    return { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int lenght;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
        char* message = (char*)alloca(lenght * sizeof(char));

        glGetShaderInfoLog(id, lenght, &lenght, message);
        std::cout <<"failed to compile "<< (type == GL_VERTEX_SHADER ? "vertex" : "fragment" ) << " shader!" << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}


static unsigned int  CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);

    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

bool Renderer::Init(Window* window) 
{

    // 1. Vincular el contexto de OpenGL al hilo actual
    glfwMakeContextCurrent(window->GetHandle());

    // 2. Inicializar GLEW para cargar los punteros de funciones de OpenGL
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) 
    {
        std::cout << "Error al inicializar GLEW\n";
        return false;
    }

    // 3. Configurar el Viewport
    int width, height;
    glfwGetFramebufferSize(window->GetHandle(), &width, &height);
    glViewport(0, 0, width, height);

    return true;
}

void Renderer::Clear(float r, float g, float b, float a) 
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::SwapBuffers(Window* window) 
{
    glfwSwapBuffers(window->GetHandle());
}

void Renderer::DrawBufferTriangle()
{
    unsigned int buffer;

    float positions[6] =
    {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    ShaderProgramSource source = ParseShader("res/shaders/Shader.shader");

    shader = CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);


    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDeleteProgram(shader);
  
}

void Renderer::DestroyShaderProgram()
{
    //Todo: Apply DeleteShader on close program call
    glDeleteProgram(shader);
}


//Legacy Versions ================================================================


void Renderer::DrawLegacyTriangle()
{
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    glEnd();
}
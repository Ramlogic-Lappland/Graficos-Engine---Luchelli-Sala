#include "Renderer.h"
#include "Window.h"
#include "Shape.h"
#include "Camera2D.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>



namespace
{
    struct ShaderProgramSource
    {
        std::string VertexSource;
        std::string FragmentSource;
    };

    ShaderProgramSource ParseShader(const std::string& filepath)
    {
        enum class ShaderType
        {
            NONE = -1,
            VERTEX = 0,
            FRAGMENT = 1
        };

        std::ifstream stream(filepath);

        if (!stream.is_open())
        {
            std::cerr << "Failed to open shader: "
                << filepath << std::endl;
            return {};
        }

        std::string line;
        std::stringstream ss[2];

        ShaderType type = ShaderType::NONE;

        while (std::getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                    type = ShaderType::VERTEX;
                else if (line.find("fragment") != std::string::npos)
                    type = ShaderType::FRAGMENT;
                else
                    type = ShaderType::NONE;
            }
            else if (type != ShaderType::NONE) // Cherno - "Evade epossible issues of invalid memory access"
            {
                ss[static_cast<int>(type)] << line << '\n';
            }
        }

        return { ss[0].str(), ss[1].str() };
    }

    unsigned int CompileShader(unsigned int type, const std::string& source)
    {
        unsigned int id = glCreateShader(type);

        if (id == 0)
            return 0;

        const char* src = source.c_str();

        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result = GL_FALSE;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);

        if (result == GL_FALSE)
        {
            int length = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

            if (length > 0)
            {
                std::vector<char> message(length);
                glGetShaderInfoLog(
                    id, length, nullptr, message.data());

                std::cerr << message.data() << std::endl;
            }

            std::cerr << "Failed to compile "
                << (type == GL_VERTEX_SHADER
                    ? "vertex" : "fragment")
                << " shader!" << std::endl;

            glDeleteShader(id);
            return 0;
        }

        return id;
    }

    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
    {
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);

        if (vs == 0)
            return 0;

        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

        if (fs == 0)
        {
            glDeleteShader(vs);
            return 0;
        }

        unsigned int program = glCreateProgram();

        if (program == 0)
        {
            glDeleteShader(vs);
            glDeleteShader(fs);
            return 0;
        }

        glAttachShader(program, vs);
        glAttachShader(program, fs);

        glLinkProgram(program);

        int result = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &result);

        if (result == GL_FALSE)
        {
            int length = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

            if (length > 0)
            {
                std::vector<char> message(length);
                glGetProgramInfoLog(program, length, nullptr, message.data());

                std::cerr << message.data() << std::endl;
            }

            std::cerr << "Failed to link shader program!"
                << std::endl;

            glDeleteProgram(program);
            program = 0;
        }

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }
}

// Renderer INIT
bool Renderer::Init(Window* window)
{
    if (window == nullptr || window->GetHandle() == nullptr)
    {
        std::cerr << "Invalid window!" << std::endl;
        return false;
    }

    // (OpenGL context must exist before initializing) GLEW IF U PUT THIS IN ANOTHER ORDER IT BREAKS !!!!!! - spent too many hours fixing it...  
    glfwMakeContextCurrent(window->GetHandle());
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;

    GLenum glewError = glewInit();

    if (glewError != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW: "
            << glewGetErrorString(glewError)
            << std::endl;
        return false;
    }

    int width, height;

    glfwGetFramebufferSize(window->GetHandle(), &width, &height);

    glViewport(0, 0, width, height);

    // Update viewport when the window is resized
    glfwSetFramebufferSizeCallback(window->GetHandle(), [](GLFWwindow*, int w, int h)
        {
            glViewport(0, 0, w, h);
        }
    );

    // Compile and link the shader
    std::cout << "Working Directory: " << std::filesystem::current_path() << std::endl;
    ShaderProgramSource source = ParseShader("res/shaders/Shader.shader");

    if (source.VertexSource.empty() || source.FragmentSource.empty())
    {
        std::cerr << "Shader source is empty!"
            << std::endl;
        return false;
    }

    shader = CreateShader(source.VertexSource, source.FragmentSource);

    if (shader == 0)
    {
        std::cerr << "Failed to create shader program!"
            << std::endl;
        return false;
    }

    colorLocation = glGetUniformLocation(shader, "u_Color");
    modelLocation = glGetUniformLocation(shader, "u_Model");
    viewLocation = glGetUniformLocation(shader, "u_View");
    projectionLocation = glGetUniformLocation(shader, "u_Projection");

    if (colorLocation == -1)
    {
        std::cerr << "Warning: u_Color not found!"
            << std::endl;
    }

    return true;
}

// Clear framebuffer
void Renderer::Clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::ApplyCamera(const Camera2D& camera)
{
    if (shader == 0)
        return;

    const glm::mat4 view = camera.GetViewMatrix();
    const glm::mat4 projection = camera.GetProjectionMatrix();

    glUseProgram(shader);

    if (viewLocation != -1)
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

    if (projectionLocation != -1)
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

    glUseProgram(0);
}

// Draw an already defined SHAPE
void Renderer::Draw(const Shape& shape)
{
    if (shader == 0)
        return;

    glUseProgram(shader);

    const Color& color = shape.GetColor();

    if (colorLocation != -1)
    {
        glUniform4f
        (
            colorLocation,
            color.r,
            color.g,
            color.b,
            color.a
        );
    }

    // Upload this shape's model matrix before issuing its draw call.
    if (modelLocation != -1)
    {
        const glm::mat4 model = shape.GetModelMatrix();
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
    }

    shape.GetVertexArray().Bind();

    glDrawElements
    (
        GL_TRIANGLES,
        static_cast<GLsizei>(
            shape.GetIndexBuffer().GetCount()),
        GL_UNSIGNED_INT,
        nullptr
    );

    shape.GetVertexArray().Unbind();

    glUseProgram(0);
}

// Unbind Shader
void Renderer::Shutdown()
{
    if (shader != 0)
    {
        glDeleteProgram(shader);
        shader = 0;
    }

    colorLocation = -1;
    modelLocation = -1;
    viewLocation = -1;
    projectionLocation = -1;
}

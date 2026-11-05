#include <iostream>

#include <glad/glad.h>

static const auto vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 pos;

void main()
{
    gl_Position = vec4(pos, 0.0, 1.0);
}
)";

static const auto fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";

static inline void checkShaderCompileStatus(unsigned int shader)
{
    int success;
    char infolog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) [[unlikely]]
    {
        glGetShaderInfoLog(shader, sizeof(infolog), nullptr, infolog);
        std::cerr << infolog << std::endl;
        exit(EXIT_FAILURE);
    }
}

static inline void checkProgramLinkStatus(unsigned int program)
{
    int success;
    char infolog[512];

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) [[unlikely]]
    {
        glGetProgramInfoLog(program, sizeof(infolog), nullptr, infolog);
        std::cerr << infolog << std::endl;
        exit(EXIT_FAILURE);
    }
}

void draw()
{
    const float vertices[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.0f, 0.5f};

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int vao;
    constexpr auto location = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(location);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    checkShaderCompileStatus(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    checkShaderCompileStatus(fragmentShader);

    unsigned int program;
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    checkProgramLinkStatus(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glUseProgram(program);

    // draw
    glBindVertexArray(vao);

    glDrawArrays(
        GL_TRIANGLES,
        0, // index
        3  // size
    );

    // cleanup
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(program);
}
#include <iostream>

#include <glad/glad.h>

static const auto vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 pos;
layout (location = 1) in float times;

void main()
{
    gl_Position = vec4(pos * times, 0.0, 1.0);
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

    const float times[] = {
        2.0f,
        2.0f,
        2.0f};

    constexpr auto posLocation = 0;
    constexpr auto timesLocation = 1;

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(posLocation);
    glEnableVertexAttribArray(timesLocation);

    unsigned int vbo[2];
    glGenBuffers(2, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(posLocation, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(times), times, GL_STATIC_DRAW);
    glVertexAttribPointer(timesLocation, 1, GL_FLOAT, GL_FALSE, 0, nullptr);

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
    glDeleteBuffers(2, vbo);
    glDeleteProgram(program);
}
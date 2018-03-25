#include "Render.hpp"

#include <fstream>
#include <string>
#include <iostream>

GLuint Render::program;

GLint Render::vertexAttribLoc;
GLint Render::texCoordAttribLoc;

GLint Render::texUniformLoc;
GLint Render::mvpUniformLoc;
GLint Render::viewUniformLoc;

GLuint Render::vbo;
GLuint Render::ibo;
GLuint Render::tbo;

void loadShaderFromFile(std::string file, GLuint shader)
{
    std::string content;
    std::ifstream fileStream(file, std::ios::in);

    if(!fileStream.is_open())
    {
        std::cout << "Could not read file " << file << std::endl;
        return;
    }

    std::string line = "";

    while(!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();

    const char* source = content.c_str();

    glShaderSource(shader, 1, &source, nullptr);
}

void printShaderError(GLuint shader)
{
    int infoLogLength = 0;
    int maxLength = infoLogLength;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength );

    char* infoLog = new char[maxLength];

    glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
    if (infoLogLength > 0)
    {
        printf( "%s\n", infoLog );
    }

    delete[] infoLog;
}

void Render::initOpenGL()
{
    program = glCreateProgram();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    loadShaderFromFile("res/shader/vertex.vs", vertexShader);
    glCompileShader(vertexShader);

    GLint vertexShaderCompiled = GL_FALSE;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderCompiled);
    if (vertexShaderCompiled != GL_TRUE)
    {
        std::cout << "Unable to compile vertex shader " << std::endl;
        printShaderError(vertexShader);
        return;
    }
    glAttachShader(program, vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    loadShaderFromFile("res/shader/fragment.fs", fragmentShader);
    glCompileShader(fragmentShader);

    GLint fragmentShaderCompiled = GL_FALSE;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderCompiled);
    if (fragmentShaderCompiled != GL_TRUE)
    {
        std::cout << "Unable to compile fragment shader " << std::endl;
        printShaderError(fragmentShader);
        return;
    }
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    GLint programSuccess = GL_TRUE;
    glGetProgramiv(program, GL_LINK_STATUS, &programSuccess);
    if( programSuccess != GL_TRUE )
    {
        std::cout << "Error linking program " << program << std::endl;
        return;
    }

    vertexAttribLoc = glGetAttribLocation(program, "position");
    if(vertexAttribLoc == -1)
    {
        std::cout << "Can't find position attribute" << std::endl;
        return;
    }

    texCoordAttribLoc = glGetAttribLocation(program, "texCoord");
    if(texCoordAttribLoc == -1)
    {
        std::cout << "Can't find texture attribute" << std::endl;
        return;
    }

    texUniformLoc = glGetUniformLocation(program, "tex");
    if(texUniformLoc == -1)
    {
        std::cout << "Can't find texture uniform" << std::endl;
        return;
    }

    mvpUniformLoc = glGetUniformLocation(program, "mvp");
    if(mvpUniformLoc == -1)
    {
        std::cout << "Can't find mvp uniform" << std::endl;
        return;
    }

    viewUniformLoc = glGetUniformLocation(program, "view");
    if(viewUniformLoc == -1)
    {
        std::cout << "Can't find view uniform" << std::endl;
        return;
    }

    GLfloat vertexData[] =
    {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    GLfloat texCoordData[] =
    {
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f
    };

    GLuint indexData[] = {0, 1, 2, 3};

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

    glGenBuffers(1, &tbo);
    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), texCoordData, GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);

    glClearColor(1.0, 1.0, 1.0, 1.0);

    GLfloat projectionMatrix[4][4];

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            projectionMatrix[i][j] = 0;

    projectionMatrix[0][0] = 1;
    projectionMatrix[1][1] = 1;
    projectionMatrix[2][2] = 1;
    projectionMatrix[3][3] = 1;

    glUseProgram(program);
    glUniformMatrix4fv(viewUniformLoc, 1, GL_FALSE, projectionMatrix[0]);

    projectionMatrix[1][1] = 800.0 / 600.0;

    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, projectionMatrix[0]);

    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

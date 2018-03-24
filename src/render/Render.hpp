#ifndef Render_hpp
#define Render_hpp

#include <GL/glew.h>

class Render
{
private:
    static GLuint program;
    static GLint vertexAttribLoc;
    static GLint texCoordAttribLoc;

    static GLuint vbo;
    static GLuint tbo;
    static GLuint ibo;
public:
    static GLint texUniformLoc;

    static void initOpenGL();

    static void renderQuad()
    {
        glUseProgram(program);

        glEnableVertexAttribArray(vertexAttribLoc);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(vertexAttribLoc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);

        glEnableVertexAttribArray(texCoordAttribLoc);
        glBindBuffer(GL_ARRAY_BUFFER, tbo);
        glVertexAttribPointer(texCoordAttribLoc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);

        glDisableVertexAttribArray(vertexAttribLoc);
        glDisableVertexAttribArray(texCoordAttribLoc);
        glUseProgram(0);
    };
};

#endif

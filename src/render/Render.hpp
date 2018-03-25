#ifndef Render_hpp
#define Render_hpp

#include <GL/glew.h>

#include <iostream>

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
    static GLint mvpUniformLoc;
    static GLint viewUniformLoc;

    static void initOpenGL();

    static void updateProjection(float* view)
    {
        glUseProgram(program);
        glUniformMatrix4fv(viewUniformLoc, 1, GL_FALSE, view);
        glUseProgram(0);
    }

    static void renderQuad(float* mvp, GLuint texture, GLuint textureBuffer = tbo)
    {
        glUseProgram(program);

        glUniformMatrix4fv(mvpUniformLoc, 1, GL_FALSE, mvp);

        glBindTexture(GL_TEXTURE_2D, texture);

        glEnableVertexAttribArray(vertexAttribLoc);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(vertexAttribLoc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);

        glEnableVertexAttribArray(texCoordAttribLoc);
        glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
        glVertexAttribPointer(texCoordAttribLoc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);

        glDisableVertexAttribArray(vertexAttribLoc);
        glDisableVertexAttribArray(texCoordAttribLoc);
        glUseProgram(0);
    };
};

#endif

#include "DebugUtilities.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] - " << error << ": " << function << " " << file << " at " << line << std::endl;
        return false;
    }

    //LOG("No more error...");
    return true;
}

bool isEqual(float a, float b) {
    return fabs(a - b) < epsilon;
}
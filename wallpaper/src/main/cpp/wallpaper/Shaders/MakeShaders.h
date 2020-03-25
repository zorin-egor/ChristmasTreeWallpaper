#ifndef MAKE_SHADERS_H
#define MAKE_SHADERS_H

#include <GLES2/gl2.h>
#include <string>


class MakeShaders {

    public :
        // Shaders for draw star points
        const static char * F_STAR_SHADER;
        const static char * V_STAR_SHADER;

        // Shader for draw ellipse points
        const static char * F_ELLIPSE_SHADER;
        const static char * V_ELLIPSE_SHADER;

        // Shader for draw snow points
        const static char * F_SNOW_SHADER;
        const static char * V_SNOW_SHADER;

        // For compiling shader program
        static GLuint compileShader(GLenum shaderType, const char* pSource);

        // For create shader program
        static GLuint createProgram(const char* pVertexSource, const char* pFragmentSource);
};

#endif //LIFEWALLPAPERTREE_MAKESHADERS_H

#ifndef SNOW_DRIFT_H
#define SNOW_DRIFT_H

#include <GLES2/gl2.h>
#include <vector>

#include "../AbstractClasses/Render.h"
#include "../Ellipse/Ellipse.h"
#include "../Snowdrift/Snowdrift.h"


class Snowdrift : public Render {

    private:

        // Init values
        static const GLfloat INIT_COUNT;
        static const GLfloat INIT_TRANSPARENCY;
        static const GLfloat DRADIUS_STEP;

        const GLfloat CENTER_X;
        const GLfloat CENTER_Y;
        const GLuint WIDTH;


    private:

        // Change values
        GLfloat m_fBottomRadiusX;
        GLfloat m_fBottomRadiusY;
        GLfloat m_fStartPointRadius;
        GLuint m_nOuterCount;
        bool m_bIsVisible;

        // Container for all ellipse objects
        std::vector<Render *> m_oEllipses;

        // For ellipse program
        GLuint m_nProgramId;
        GLuint m_nTextureId;
        GLuint m_nPositionAttr;
        GLuint m_nSpeedAttr;
        GLuint m_nRadiusAttr;
        GLuint m_nDeltaAttr;
        GLuint m_nColorStartAttr;
        GLuint m_nColorEndAttr;
        GLuint m_nSizeUniform;
        GLuint m_nTotalDeltaSpeedUniform;


    public:

        Snowdrift(GLuint width,
                  GLfloat radiusX,
                  GLfloat radiusY,
                  GLfloat pointRadius,
                  GLfloat centerX,
                  GLfloat centerY,
                  GLuint programID,
                  GLuint textureID,
                  GLuint positionAttr,
                  GLuint speedAttr,
                  GLuint radiusAttr,
                  GLuint deltaAttr,
                  GLuint colorStartAttr,
                  GLuint colorEndAttr,
                  GLuint sizeUniform,
                  GLuint totalDeltaSpeedUniform );

        virtual ~Snowdrift();


    public:

        void setVisible(bool isVisible) {
            m_bIsVisible = isVisible;
        }

        bool getVisible() {
            return m_bIsVisible;
        }

        void render();


    private:

        void init();

};


#endif

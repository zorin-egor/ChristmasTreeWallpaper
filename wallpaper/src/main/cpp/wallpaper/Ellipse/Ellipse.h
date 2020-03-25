#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <GLES2/gl2.h>
#include <math.h>
#include <string.h>

#include "../AbstractClasses/Render.h"
#include "../Common/Methods.h"
#include "../Common/LogGL.h"


class Ellipse : public Render {

    public:

        static const enum COLOR_TYPE {
            RANDOM = 0,
            RED = 1,
            GREEN = 2,
            BLUE = 3,
            WHITE = 4
        };

        static const enum FLICKER_FREQUENCY {
            NONE = 0,
            LOW = 1,
            MIDDLE = 2,
            HIGH = 3
        };


    private:

        const GLfloat pointSize;

        COLOR_TYPE m_oColorType;
        FLICKER_FREQUENCY m_oFrequency;
        GLfloat m_fTransparency;
        GLuint m_nFrequencyInterval;
        bool m_bIsResetTransparency;
        bool m_bIsMove;

        GLuint m_nTextureId;
        GLuint m_nProgramId;

        GLuint m_nPositionUniform;
        GLuint m_nSpeedAttr;
        GLuint m_nRadiusUniform;
        GLuint m_nTotalDeltaSpeedUniform;
        GLint m_nDeltaAttr;
        GLint m_nColorStartAttr;
        GLint m_nColorEndAttr;
        GLint m_nSizeUniform;

        GLfloat * m_pColorStartArray;
        GLfloat * m_pColorEndArray;
        GLfloat * m_pArrayPosition;
        GLfloat * m_pArrayDelta;

        GLfloat m_fCenterCoords[2];
        GLfloat m_fRadius[2];
        GLfloat m_fSizeUniformArray[2];

        unsigned int m_nCount;
        GLfloat m_fCenterX;
        GLfloat m_fCenterY;
        GLfloat m_fRadiusX;
        GLfloat m_fRadiusY;
        bool m_bIsVisible;

        float m_fTotalDeltaSpeed;
        float m_fDeltaSpeed;


    public:

        Ellipse(unsigned int count,
                GLfloat radiusX,
                GLfloat radiusY,
                GLfloat centerX,
                GLfloat centerY,
                GLfloat pointSize,
                COLOR_TYPE colorType,
                FLICKER_FREQUENCY frequency,
                GLfloat transparency,
                bool isMove,
                GLuint programID,
                GLuint textureID,
                GLuint positionUniform,
                GLuint speedAttr,
                GLuint radiusAttr,
                GLuint deltaAttr,
                GLuint colorStartAttr,
                GLuint colorEndAttr,
                GLuint sizeUniform,
                GLuint totalDeltaSpeedUniform);

        virtual ~Ellipse();


    public:

        void render();

        void setVisible(bool isVisible) {
            m_bIsVisible = isVisible;
        }

        bool getVisible() {
            return m_bIsVisible;
        }

        void changeDirection(bool isLeftOrRight);


    private:

        void init();

        void setValues();
};

#endif

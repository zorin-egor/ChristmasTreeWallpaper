#ifndef SNOW_H
#define SNOW_H

#include <GLES2/gl2.h>

#include "../AbstractClasses/Render.h"
#include "../Common/Methods.h"
#include "../Common/LogGL.h"
#include "../Snow/Snow.h"


class Snow : public Render {

    public:

        static const enum COLOR_TYPE {
            RANDOM = 0,
            WHITE = 1,
            BLUE = 2,
            GREY = 3
        };

        static const enum WIND_POWER {
            SLOW = 0,
            MIDDLE = 1,
            FAST = 2
        };

    private:

        // For visibility
        bool m_bIsVisible;

        // Color for objects
        COLOR_TYPE m_oColorType;

        // For fall speed
        WIND_POWER m_oWindType;

        // Fall angle in radians
        GLfloat m_fRadianAngleFall;
        GLfloat m_fNewRadianAngleFall;

        // Snow ends fall
        GLfloat m_fSnowEnds;

        // For amplitude strict
        GLuint m_nAmplitudeStrict;
        bool m_bIsChangeAmplitude;

        // Objects parameters
        GLuint m_nCount;
        GLuint m_nMaxSize;

        // Shader parameters
        GLuint m_nProgramId;
        GLuint m_nTextureId;
        GLuint m_nAttrStartPosition;
        GLuint m_nAttrFallSpeed;
        GLuint m_nAttrSnowSize;
        GLuint m_nAttrSnowShift;
        GLuint m_nAttrSnowColor;
        GLuint m_nUniformAngle;
        GLuint m_nAttrFreq;
        GLuint m_nAttrAmplitude;

        // Data for shader
        GLfloat * m_pArrayStartPosition;
        GLfloat * m_pArrayFallSpeed;
        GLfloat * m_pArrayFallSpeedSteps;
        GLfloat * m_pArraySnowSize;
        GLfloat * m_pArraySnowShift;
        GLfloat * m_pArraySnowColor;
        GLfloat * m_pArraySnowFreq;
        GLfloat * m_pArraySnowAmplitude;
        GLfloat m_fAngle;


    public:

        Snow(GLuint count,
             GLuint maxSize,
             COLOR_TYPE colorType,
             WIND_POWER windType,
             GLfloat angleFall,
             GLfloat snowEnds,
             GLuint programID,
             GLuint textureID,
             GLuint attrStartPosition,
             GLuint attrFallSpeed,
             GLuint attrSnowSize,
             GLuint attrSnowShift,
             GLuint attrSnowColor,
             GLuint uniformAngle,
             GLuint attrFreq,
             GLuint attrAmplitude);

        virtual ~Snow();


    public:

        void render();

        void setVisible(bool isVisible) {
            m_bIsVisible = isVisible;
        }

        bool getVisible() {
            return m_bIsVisible;
        }

        void setDegrees(GLfloat angle);

        void setPower(WIND_POWER power);


    private:

        void init();

        void setValues();

};

#endif

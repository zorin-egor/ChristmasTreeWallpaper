#ifndef STAR_H
#define STAR_H

#include <GLES2/gl2.h>

#include "../AbstractClasses/Render.h"
#include "../Common/Methods.h"
#include "../Common/LogGL.h"


class Star : public Render {

    public:

        static const enum FUNCTION_TYPE {
            DYNAMIC_UNIFORM = 0,
            DYNAMIC_RANDOM = 1,
            HYPOCYCLOID = 2,
            EPICYCLOID = 3,
            STATIC_RANDOM = 4
        };

        static const enum COLOR_TYPE {
            RANDOM = 0,
            RED = 1,
            GREEN = 2,
            BLUE = 3,
            BROWN = 4
        };


    private:

        // For type of function for output
        const FUNCTION_TYPE m_oType;
        // For figure color
        const COLOR_TYPE m_oColor;

        // For shader
        GLuint m_nTextureId;
        GLuint m_nProgramId;
        GLuint m_nStarsAngle;
        GLuint m_nStarColor;
        GLuint m_nStarCenter;
        GLuint m_nStarRadius;
        GLuint m_nStarArgumentsX;
        GLuint m_nStarArgumentsY;
        GLuint m_nStarSize;
        GLuint m_nStarTotalDeltaSpeed;

        // For data
        GLuint m_nCount;
        GLfloat m_fCenterX;
        GLfloat m_fCenterY;
        GLfloat m_fRadiusX;
        GLfloat m_fRadiusY;
        GLfloat m_fRadiusXMax;
        GLfloat m_fRadiusYMax;
        GLfloat m_fRadiusStep;
        GLfloat m_fArgumentsX[2];
        GLfloat m_fStrictArgumentX[2];
        GLfloat m_fArgumentsY[2];
        GLfloat m_fStrictArgumentY[2];
        GLfloat m_fDeltaArgument;
        GLfloat m_fDeltaArgumentX[2];
        GLfloat m_fDeltaArgumentY[2];
        GLfloat * m_pArrayPosition;
        GLfloat * m_pArrayColor;
        GLfloat m_fTotalDeltaSpeed;
        GLfloat m_fDeltaSpeed;
        GLfloat m_fSizePoint;

        // For visibility
        bool m_bIsVisible;


    public:

        Star(FUNCTION_TYPE type,
             COLOR_TYPE color,
             GLuint count,
             GLfloat centerX,
             GLfloat centerY,
             GLfloat radiusX,
             GLfloat radiusY,
             GLuint programID,
             GLuint textureID,
             GLuint starsAngle,
             GLuint starColor,
             GLuint starCenter,
             GLuint starRadius,
             GLuint starArgumentsX,
             GLuint starArgumentsY,
             GLuint starSize,
             GLuint starTotalDeltaSpeed);

        virtual ~Star();


    public:

        void render();

        void setVisible(bool isVisible) {
            isVisible = isVisible;
        }

        bool getVisible() {
            return m_bIsVisible;
        }


    private:

        void init();

        void setValues();
};

#endif

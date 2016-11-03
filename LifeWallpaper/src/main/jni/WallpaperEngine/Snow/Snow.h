#ifndef LIFEWALLPAPERTREE_SNOW_H
#define LIFEWALLPAPERTREE_SNOW_H

#include <GLES2/gl2.h>
#include <WallpaperEngine/AbstractClasses/Render.h>
#include <WallpaperEngine/Common/Methods.h>
#include <WallpaperEngine/Snow/Snow.h>
#include <LogGL.h>

class Snow : public Render {

    public:
        static const enum COLOR_TYPE { RANDOM = 0, WHITE = 1, BLUE = 2, GREY = 3};
        static const enum WIND_POWER { SLOW = 0, MIDDLE = 1, FAST = 2};

        Snow( GLuint _count,
              GLuint _maxSize,
              COLOR_TYPE _colorType,
              WIND_POWER _windType,
              GLfloat _angleFall,
              GLfloat _snowEnds,
              GLuint _programID,
              GLuint _textureID,
              GLuint _attrStartPosition,
              GLuint _attrFallSpeed,
              GLuint _attrSnowSize,
              GLuint _attrSnowShift,
              GLuint _attrSnowColor,
              GLuint _uniformAngle,
              GLuint _attrFreq,
              GLuint _attrAmplitude) : count(_count),
                                       maxSize(_maxSize),
                                       colorType(_colorType),
                                       windType(_windType),
                                       snowEnds(_snowEnds),
                                       programID(_programID),
                                       textureID(_textureID),
                                       attrStartPosition(_attrStartPosition),
                                       attrFallSpeed(_attrFallSpeed),
                                       attrSnowSize(_attrSnowSize),
                                       attrSnowShift(_attrSnowShift),
                                       attrSnowColor(_attrSnowColor),
                                       uniformAngle(_uniformAngle),
                                       attrFreq(_attrFreq),
                                       attrAmplitude(_attrAmplitude),
                                       amplitudeStrict(50),
                                       isChangeAmplitude(false)
        {
            LOGI("Snow::Snow()");
            isVisible = true;
            radianAngleFall = newRadianAngleFall = Methods::degreesToRadians(_angleFall);
            init();
        }

        virtual ~Snow(){
            LOGI("~Snow");
            // Off attributes
//            glDisableVertexAttribArray(attrStartPosition);
//            glDisableVertexAttribArray(attrFallSpeed);
//            glDisableVertexAttribArray(attrSnowSize);
//            glDisableVertexAttribArray(attrSnowShift);
//            glDisableVertexAttribArray(attrSnowColor);
//            glDisableVertexAttribArray(attrFreq);
//            glDisableVertexAttribArray(attrAmplitude);

            delete [] arrayStartPosition;
            delete [] arrayFallSpeed;
            delete [] arrayFallSpeedSteps;
            delete [] arraySnowSize;
            delete [] arraySnowShift;
            delete [] arraySnowColor;
            delete [] arraySnowFreq;
            delete [] arraySnowAmplitude;
        }

        void render();

        void setVisible(bool _isVisible){
            isVisible = _isVisible;
        }

        bool getVisible(){
            return isVisible;
        }

        void setDegrees(GLfloat _angle);
        void setPower(WIND_POWER _power);

    private:
        void init();
        void setValues();

        // For visibility
        bool isVisible;
        // Color for objects
        COLOR_TYPE colorType;
        // For fall speed
        WIND_POWER windType;
        // Fall angle in radians
        GLfloat radianAngleFall;
        GLfloat newRadianAngleFall;
        // Snow ends fall
        GLfloat snowEnds;
        // For amplitude strict
        GLuint amplitudeStrict;
        bool isChangeAmplitude;

        // Objects parameters
        GLuint count;
        GLuint maxSize;

        // Shader parameters
        GLuint programID;
        GLuint textureID;
        GLuint attrStartPosition;
        GLuint attrFallSpeed;
        GLuint attrSnowSize;
        GLuint attrSnowShift;
        GLuint attrSnowColor;
        GLuint uniformAngle;
        GLuint attrFreq;
        GLuint attrAmplitude;

        // Data for shader
        GLfloat * arrayStartPosition;
        GLfloat * arrayFallSpeed;
        GLfloat * arrayFallSpeedSteps;
        GLfloat * arraySnowSize;
        GLfloat * arraySnowShift;
        GLfloat * arraySnowColor;
        GLfloat angle;
        GLfloat * arraySnowFreq;
        GLfloat * arraySnowAmplitude;
};

#endif

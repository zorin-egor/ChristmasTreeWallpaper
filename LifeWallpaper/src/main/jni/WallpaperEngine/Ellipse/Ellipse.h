#ifndef LIFEWALLPAPERTREE_ELLIPSE_H
#define LIFEWALLPAPERTREE_ELLIPSE_H

#include <GLES2/gl2.h>
#include <math.h>
#include <string.h>
#include <WallpaperEngine/AbstractClasses/Render.h>
#include <WallpaperEngine/Common/Methods.h>
#include <LogGL.h>


class Ellipse : public Render {

    public:
        static const enum COLOR_TYPE { RANDOM = 0, RED = 1, GREEN = 2, BLUE = 3, WHITE = 4 };
        static const enum FLICKER_FREQUENCY { NONE = 0, LOW = 1, MIDDLE = 2, HIGH = 3 };

        Ellipse(  unsigned int _count,
                  GLfloat _radiusX,
                  GLfloat _radiusY,
                  GLfloat _centerX,
                  GLfloat _centerY,
                  GLfloat _pointSize,
                  COLOR_TYPE _colorType,
                  FLICKER_FREQUENCY _frequency,
                  GLfloat _transparancy,
                  bool _isMove,
                  GLuint _programID,
                  GLuint _textureID,
                  GLuint _positionUniform,
                  GLuint _speedAttr,
                  GLuint _radiusAttr,
                  GLuint _deltaAttr,
                  GLuint _colorStartAttr,
                  GLuint _colorEndAttr,
                  GLuint _sizeUniform,
                  GLuint _totalDeltaSpeedUniform) : count(_count),
                                                    radiusX(_radiusX),
                                                    radiusY(_radiusY),
                                                    centerX(_centerX),
                                                    centerY(_centerY),
                                                    pointSize(_pointSize),
                                                    colorType(_colorType),
                                                    frequency(_frequency),
                                                    transparancy(_transparancy),
                                                    isMove(_isMove),
                                                    programID(_programID),
                                                    textureID(_textureID),
                                                    positionUniform(_positionUniform),
                                                    speedAttr(_speedAttr),
                                                    radiusUniform(_radiusAttr),
                                                    deltaAttr(_deltaAttr),
                                                    colorStartAttr(_colorStartAttr),
                                                    colorEndAttr(_colorEndAttr),
                                                    sizeUniform(_sizeUniform),
                                                    totalDeltaSpeedUniform(_totalDeltaSpeedUniform)
        {
            //LOGI("Ellipse::Ellipse()");
            isVisible = true;
            init();
        }

        virtual ~Ellipse(){
            //LOGI("~Ellipse");
            delete [] colorStartArray;
            delete [] colorEndArray;
            delete [] arrayPosition;
            delete [] arrayDelta;
        }

        void render();

        void setVisible(bool _isVisible){
            isVisible = _isVisible;
        }

        bool getVisible(){
            return isVisible;
        }

        void changeDirection(bool isLeftOrRight);

    private:
        COLOR_TYPE colorType;
        FLICKER_FREQUENCY frequency;
        GLfloat transparancy;
        bool isResetTransparancy;
        GLuint frequencyInterval;
        bool isMove;
        const GLfloat pointSize;

        void init();
        void setValues();

        GLuint textureID;
        GLuint programID;

        GLuint positionUniform;
        GLuint speedAttr;
        GLuint radiusUniform;
        GLuint totalDeltaSpeedUniform;
        GLint deltaAttr;
        GLint colorStartAttr;
        GLint colorEndAttr;
        GLint sizeUniform;

        GLfloat * colorStartArray;
        GLfloat * colorEndArray;
        GLfloat * arrayPosition;
        GLfloat * arrayDelta;

        GLfloat centerCoords[2];
        GLfloat radius[2];
        GLfloat sizeUniformArray[2];

        unsigned int count;
        GLfloat centerX;
        GLfloat centerY;
        GLfloat radiusX;
        GLfloat radiusY;
        bool isVisible;

        float totalDeltaSpeed;
        float deltaSpeed;
};

#endif

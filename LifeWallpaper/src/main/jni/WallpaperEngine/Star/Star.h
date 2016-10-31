#ifndef LIFEWALLPAPERTREE_STAR_H
#define LIFEWALLPAPERTREE_STAR_H

#include <GLES2/gl2.h>
#include <LogGL.h>
#include <WallpaperEngine/AbstractClasses/Render.h>
#include <WallpaperEngine/Common/Methods.h>

class Star : public Render {
    public:
        static const enum FUNCTION_TYPE { DYNAMIC_UNIFORM = 0, DYNAMIC_RANDOM = 1, HYPOCYCLOID = 2, EPICYCLOID = 3, STATIC_RANDOM = 4 };
        static const enum COLOR_TYPE { RANDOM = 0, RED = 1, GREEN = 2, BLUE = 3, BROWN = 4};

        Star(FUNCTION_TYPE _type,
             COLOR_TYPE _color,
             GLuint _count,
             GLfloat _centerX,
             GLfloat _centerY,
             GLfloat _radiusX,
             GLfloat _radiusY,
             GLuint _programID,
             GLuint _textureID,
             GLuint _starsAngle,
             GLuint _starColor,
             GLuint _starCenter,
             GLuint _starRadius,
             GLuint _starArgumentsX,
             GLuint _starArgumentsY,
             GLuint _starSize,
             GLuint _starTotalDeltaSpeed) : type(_type),
                                            color(_color),
                                            count(_count),
                                            centerX(_centerX),
                                            centerY(_centerY),
                                            radiusX(_radiusX),
                                            radiusY(_radiusY),
                                            programID(_programID),
                                            textureID(_textureID),
                                            starsAngle(_starsAngle),
                                            starColor(_starColor),
                                            starCenter(_starCenter),
                                            starRadius(_starRadius),
                                            starArgumentsX(_starArgumentsX),
                                            starArgumentsY(_starArgumentsY),
                                            starSize(_starSize),
                                            starTotalDeltaSpeed(_starTotalDeltaSpeed)
    {
        LOGI("Star::Star()");
        isVisible = true;
        init();
    }

    virtual ~Star(){
        LOGI("~Star");
        delete [] arrayColor;
        delete [] arrayPosition;
    }

    void render();

    void setVisible(bool _isVisible){
        isVisible = _isVisible;
    }

    bool getVisible(){
        return isVisible;
    }

private:

    void init();
    void setValues();

    // For type of function for output
    const FUNCTION_TYPE type;
    // For figure color
    const COLOR_TYPE color;

    // For shader
    GLuint textureID;
    GLuint programID;
    GLuint starsAngle;
    GLuint starColor;
    GLuint starCenter;
    GLuint starRadius;
    GLuint starArgumentsX;
    GLuint starArgumentsY;
    GLuint starSize;
    GLuint starTotalDeltaSpeed;

    // For data
    GLuint count;
    GLfloat centerX;
    GLfloat centerY;
    GLfloat radiusX;
    GLfloat radiusY;
    GLfloat radiusXMax;
    GLfloat radiusYMax;
    GLfloat radiusStep;
    GLfloat argumentsX[2];
    GLfloat strictArgumentX[2];
    GLfloat argumentsY[2];
    GLfloat strictArgumentY[2];
    GLfloat deltaArgument;
    GLfloat deltaArgumentX[2];
    GLfloat deltaArgumentY[2];
    GLfloat * arrayPosition;
    GLfloat * arrayColor;
    GLfloat totalDeltaSpeed;
    GLfloat deltaSpeed;
    GLfloat sizePoint;

    // For visibility
    bool isVisible;
};

#endif

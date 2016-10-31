#ifndef LIFEWALLPAPERTREE_SNOWDRIFT_H
#define LIFEWALLPAPERTREE_SNOWDRIFT_H

#include <GLES2/gl2.h>
#include <vector>
#include <WallpaperEngine/AbstractClasses/Render.h>
#include <WallpaperEngine/Ellipse/Ellipse.h>
#include <WallpaperEngine/Snowdrift/Snowdrift.h>

class Snowdrift : public Render {
public:
    Snowdrift(  GLuint _width,
                GLfloat _radiusX,
                GLfloat _radiusY,
                GLfloat _pointRadius,
                GLfloat _centerX,
                GLfloat _centerY,
                GLuint _programID,
                GLuint _textureID,
                GLuint _positionAttr,
                GLuint _speedAttr,
                GLuint _radiusAttr,
                GLuint _deltaAttr,
                GLuint _colorStartAttr,
                GLuint _colorEndAttr,
                GLuint _sizeUniform,
                GLuint _totalDeltaSpeedUniform ) : WIDTH(_width),
                                                   bottomRadiusX(_radiusX),
                                                   bottomRadiusY(_radiusY),
                                                   startPointRadius(_pointRadius),
                                                   CENTER_X(_centerX),
                                                   CENTER_Y(_centerY),
                                                   programID(_programID),
                                                   textureID(_textureID),
                                                   positionAttr(_positionAttr),
                                                   speedAttr(_speedAttr),
                                                   radiusAttr(_radiusAttr),
                                                   deltaAttr(_deltaAttr),
                                                   colorStartAttr(_colorStartAttr),
                                                   colorEndAttr(_colorEndAttr),
                                                   sizeUniform(_sizeUniform),
                                                   totalDeltaSpeedUniform(_totalDeltaSpeedUniform),
                                                   INIT_COUNT(150),
                                                   INIT_TRANSPARANCY(0.5f),
                                                   DRADIUS_STEP(25.f)
    {
        LOGI("Snowdrift::Snowdrift()");
        init();
    }

    virtual ~Snowdrift(){
        LOGI("~Snowdrift()");
        for(int i = 0; i < ellipses.size(); i++){
            delete ellipses[i];
        }
    }

    void setVisible(bool _isVisible){
        isVisible = _isVisible;
    }

    bool getVisible(){
        return isVisible;
    }

    void render();

private:
    void init();

    // Init values
    const GLfloat INIT_COUNT;
    const GLfloat INIT_TRANSPARANCY;
    const GLfloat CENTER_X;
    const GLfloat CENTER_Y;
    const GLfloat DRADIUS_STEP;
    const GLuint WIDTH;

    // Change values
    GLfloat bottomRadiusX;
    GLfloat bottomRadiusY;
    GLfloat startPointRadius;
    GLuint outerCount;
    bool isVisible;

    // Container for all ellipse objectes
    std::vector<Render *> ellipses;

    // For ellipse program
    GLuint programID;
    GLuint textureID;
    GLuint positionAttr;
    GLuint speedAttr;
    GLuint radiusAttr;
    GLuint deltaAttr;
    GLuint colorStartAttr;
    GLuint colorEndAttr;
    GLuint sizeUniform;
    GLuint totalDeltaSpeedUniform;
};


#endif

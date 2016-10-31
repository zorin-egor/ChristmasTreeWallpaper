#ifndef LIFEWALLPAPERTREE_TREE_H
#define LIFEWALLPAPERTREE_TREE_H

#include <GLES2/gl2.h>
#include <vector>
#include <WallpaperEngine/AbstractClasses/Render.h>
#include <WallpaperEngine/Ellipse/Ellipse.h>

class Tree : public Render {
    public:
        Tree(GLuint _height,
             GLfloat _radiusX,
             GLfloat _radiusY,
             GLfloat _centerX,
             GLfloat _pointSize,
             GLfloat _border,
             GLuint _programID,
             GLuint _textureID,
             GLuint _positionAttr,
             GLuint _speedAttr,
             GLuint _radiusAttr,
             GLuint _deltaAttr,
             GLuint _colorStartAttr,
             GLuint _colorEndAttr,
             GLuint _sizeUniform,
             GLuint _totalDeltaSpeedUniform ) : HEIGHT(_height),
                                                bottomRadiusX(_radiusX),
                                                bottomRadiusY(_radiusY),
                                                BOTTOM_X(_centerX),
                                                POINT_SIZE(_pointSize),
                                                BORDER(_border),
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
                                                COUNT(200),
                                                BOTTOM_Y(-1.0f + BORDER),
                                                TRASPARANCY(1.0f)

        {
            LOGI("Tree::Tree()");
            init();
        }

        virtual ~Tree(){
            LOGI("~Tree()");
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
        GLfloat getBottomY();
        GLfloat getTopY();
        void changeDirection(bool isLeftOrRight);

    private:
        void init();

        // Init values
        const GLfloat BORDER;
        const GLuint COUNT;
        const GLuint HEIGHT;
        const GLfloat BOTTOM_X;
        const GLfloat BOTTOM_Y;
        const GLfloat POINT_SIZE;
        const GLfloat TRASPARANCY;

        // Change values
        GLfloat step;
        GLfloat bottomRadiusX;
        GLfloat bottomRadiusY;
        GLfloat topY;
        bool isVisible;

        // Container for all ellipse objectes
        std::vector<Ellipse *> ellipses;

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

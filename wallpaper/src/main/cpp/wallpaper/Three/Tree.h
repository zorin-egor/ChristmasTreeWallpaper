#ifndef TREE_H
#define TREE_H

#include <GLES2/gl2.h>
#include <vector>

#include "../AbstractClasses/Render.h"
#include "../Ellipse/Ellipse.h"


class Tree : public Render {

    private:

        static const GLuint COUNT;
        static const GLfloat TRANSPARENCY;

        const GLfloat BORDER;
        const GLuint HEIGHT;
        const GLfloat BOTTOM_X;
        const GLfloat BOTTOM_Y;
        const GLfloat POINT_SIZE;


    private:

        // Change values
        GLfloat m_fStep;
        GLfloat m_fBottomRadiusX;
        GLfloat m_fBottomRadiusY;
        GLfloat m_fTopY;
        bool m_bIsVisible;

        // Container for all ellipse objects
        std::vector<Ellipse*> m_oEllipses;

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

        Tree(GLuint height,
             GLfloat radiusX,
             GLfloat radiusY,
             GLfloat centerX,
             GLfloat pointSize,
             GLfloat border,
             GLuint programID,
             GLuint textureID,
             GLuint positionAttr,
             GLuint speedAttr,
             GLuint radiusAttr,
             GLuint deltaAttr,
             GLuint colorStartAttr,
             GLuint colorEndAttr,
             GLuint sizeUniform,
             GLuint totalDeltaSpeedUniform);

        virtual ~Tree();


    public:

        void setVisible(bool _isVisible) {
            m_bIsVisible = _isVisible;
        }

        bool getVisible() {
            return m_bIsVisible;
        }

        void render();

        GLfloat getBottomY();

        GLfloat getTopY();

        void changeDirection(bool isLeftOrRight);


    private:

        void init();

};


#endif

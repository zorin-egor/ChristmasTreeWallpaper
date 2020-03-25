#include "Tree.h"

const GLuint Tree::COUNT = 200;
const GLfloat Tree::TRANSPARENCY = 1.0f;

Tree::Tree(GLuint height,
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
           GLuint totalDeltaSpeedUniform ) : HEIGHT(height),
                                             m_fBottomRadiusX(radiusX),
                                             m_fBottomRadiusY(radiusY),
                                             BOTTOM_X(centerX),
                                             POINT_SIZE(pointSize),
                                             BORDER(border),
                                             m_nProgramId(programID),
                                             m_nTextureId(textureID),
                                             m_nPositionAttr(positionAttr),
                                             m_nSpeedAttr(speedAttr),
                                             m_nRadiusAttr(radiusAttr),
                                             m_nDeltaAttr(deltaAttr),
                                             m_nColorStartAttr(colorStartAttr),
                                             m_nColorEndAttr(colorEndAttr),
                                             m_nSizeUniform(sizeUniform),
                                             m_nTotalDeltaSpeedUniform(totalDeltaSpeedUniform),
                                             BOTTOM_Y(-1.0f + BORDER)

{
    LOGI("Tree::Tree()");
    init();
}

Tree::~Tree() {
    LOGI("Tree::~Tree()");
    std::for_each(m_oEllipses.begin(), m_oEllipses.end(), [](std::vector<Ellipse*>::value_type &item) {
        delete item;
    });
    m_oEllipses.clear();
}


void Tree::init() {
    LOGI("BORDER: %f;", BORDER);
    m_bIsVisible = true;
    m_fStep = (2.0f - BORDER * 2.0f) / (GLfloat) HEIGHT;
    GLfloat centerY = BOTTOM_Y;
    GLuint countValue = COUNT;
    GLuint dCount = COUNT / HEIGHT;
    GLfloat dRadiusX = m_fBottomRadiusX / (GLfloat) HEIGHT;
    GLfloat dRadiusY = m_fBottomRadiusY / (GLfloat) HEIGHT * 0.95f;
    for(int i = 0; i < HEIGHT; i++, countValue -= dCount, m_fBottomRadiusX -= dRadiusX, centerY += m_fStep, m_fBottomRadiusY -= dRadiusY) {
        m_oEllipses.push_back(new Ellipse(countValue,
                                          m_fBottomRadiusX,
                                          m_fBottomRadiusY,
                                          BOTTOM_X,
                                          centerY,
                                          POINT_SIZE,
                                          Ellipse::COLOR_TYPE::RANDOM,
                                          Ellipse::HIGH,
                                          TRANSPARENCY,
                                          true,
                                          m_nProgramId,
                                          m_nTextureId,
                                          m_nPositionAttr,
                                          m_nSpeedAttr,
                                          m_nRadiusAttr,
                                          m_nDeltaAttr,
                                          m_nColorStartAttr,
                                          m_nColorEndAttr,
                                          m_nSizeUniform,
                                          m_nTotalDeltaSpeedUniform));
    }

    m_fTopY = centerY;
}

void Tree::render() {
    if (m_bIsVisible) {
        std::for_each(m_oEllipses.begin(), m_oEllipses.end(), [](std::vector<Ellipse*>::value_type &item) {
            item->render();
        });
    }
}

GLfloat Tree::getBottomY() {
    return BOTTOM_Y;
}

GLfloat Tree::getTopY() {
    return m_fTopY;
}

void Tree::changeDirection(bool isLeftOrRight) {
    std::for_each(m_oEllipses.begin(), m_oEllipses.end(), [&](std::vector<Ellipse*>::value_type &item) {
        item->changeDirection(isLeftOrRight);
    });
}

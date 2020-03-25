#include "Snowdrift.h"

const GLfloat Snowdrift::INIT_COUNT = 150;
const GLfloat Snowdrift::INIT_TRANSPARENCY = 0.5f;
const GLfloat Snowdrift::DRADIUS_STEP = 25.0f;

Snowdrift::Snowdrift(GLuint width,
                     GLfloat radiusX,
                     GLfloat radiusY,
                     GLfloat pointRadius,
                     GLfloat centerX,
                     GLfloat centerY,
                     GLuint programID,
                     GLuint textureID,
                     GLuint positionAttr,
                     GLuint speedAttr,
                     GLuint radiusAttr,
                     GLuint deltaAttr,
                     GLuint colorStartAttr,
                     GLuint colorEndAttr,
                     GLuint sizeUniform,
                     GLuint totalDeltaSpeedUniform ) : WIDTH(width),
                                                       m_fBottomRadiusX(radiusX),
                                                       m_fBottomRadiusY(radiusY),
                                                       m_fStartPointRadius(pointRadius),
                                                       CENTER_X(centerX),
                                                       CENTER_Y(centerY),
                                                       m_nProgramId(programID),
                                                       m_nTextureId(textureID),
                                                       m_nPositionAttr(positionAttr),
                                                       m_nSpeedAttr(speedAttr),
                                                       m_nRadiusAttr(radiusAttr),
                                                       m_nDeltaAttr(deltaAttr),
                                                       m_nColorStartAttr(colorStartAttr),
                                                       m_nColorEndAttr(colorEndAttr),
                                                       m_nSizeUniform(sizeUniform),
                                                       m_nTotalDeltaSpeedUniform(totalDeltaSpeedUniform)
{
    LOGI("Snowdrift::Snowdrift()");
    init();
}

Snowdrift::~Snowdrift() {
    LOGI("Snowdrift::~Snowdrift()");
    for(int i = 0; i < m_oEllipses.size(); i++) {
        delete m_oEllipses[i];
    }
}

void Snowdrift::init() {
    m_bIsVisible = true;
    m_nOuterCount = INIT_COUNT;
    GLfloat transparency = INIT_TRANSPARENCY;
    GLfloat transparencyStep = transparency / (GLfloat) WIDTH;
    GLuint dCount = (GLuint)m_nOuterCount / (WIDTH * 2);
    GLfloat dRadiusX = m_fBottomRadiusX / DRADIUS_STEP;
    GLfloat dRadiusY = m_fBottomRadiusY / DRADIUS_STEP;
    GLfloat dPointRadius = m_fStartPointRadius / (GLfloat)WIDTH * 0.95f;

    for(int i = 0; i < WIDTH; i++, m_nOuterCount -= dCount,
                                   m_fBottomRadiusX += dRadiusX,
                                   m_fBottomRadiusY += dRadiusY,
                                   transparency -= transparencyStep,
                                   m_fStartPointRadius -= dPointRadius) {

        //LOGI("Snowdrift::init(); COUNT: %d; DCOUNT: %d", m_nOuterCount, dCount);
        if (i > WIDTH * 0.7f) {
            //LOGI("Snowdrift::init(); Change: %d;", dCount);
            dCount =  INIT_COUNT / WIDTH * 2;
        }

        m_oEllipses.push_back(new Ellipse(m_nOuterCount,
                                          m_fBottomRadiusX,
                                          m_fBottomRadiusY,
                                          CENTER_X,
                                          CENTER_Y,
                                          m_fStartPointRadius,
                                          Ellipse::COLOR_TYPE::RANDOM,
                                          Ellipse::HIGH,
                                          transparency,
                                          false,
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
}

void Snowdrift::render() {
    if (m_bIsVisible) {
        for(int i = 0; i < m_oEllipses.size(); i++) {
            m_oEllipses[i]->render();
        }
    }
}
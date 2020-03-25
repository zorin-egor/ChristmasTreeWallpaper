#include "Ellipse.h"

Ellipse::Ellipse(  unsigned int count,
          GLfloat radiusX,
          GLfloat radiusY,
          GLfloat centerX,
          GLfloat centerY,
          GLfloat pointSize,
          COLOR_TYPE colorType,
          FLICKER_FREQUENCY frequency,
          GLfloat transparency,
          bool isMove,
          GLuint programID,
          GLuint textureID,
          GLuint positionUniform,
          GLuint speedAttr,
          GLuint radiusAttr,
          GLuint deltaAttr,
          GLuint colorStartAttr,
          GLuint colorEndAttr,
          GLuint sizeUniform,
          GLuint totalDeltaSpeedUniform) : m_nCount(count),
                                           m_fRadiusX(radiusX),
                                           m_fRadiusY(radiusY),
                                           m_fCenterX(centerX),
                                           m_fCenterY(centerY),
                                           pointSize(pointSize),
                                           m_oColorType(colorType),
                                           m_oFrequency(frequency),
                                           m_fTransparency(transparency),
                                           m_bIsMove(isMove),
                                           m_nProgramId(programID),
                                           m_nTextureId(textureID),
                                           m_nPositionUniform(positionUniform),
                                           m_nSpeedAttr(speedAttr),
                                           m_nRadiusUniform(radiusAttr),
                                           m_nDeltaAttr(deltaAttr),
                                           m_nColorStartAttr(colorStartAttr),
                                           m_nColorEndAttr(colorEndAttr),
                                           m_nSizeUniform(sizeUniform),
                                           m_nTotalDeltaSpeedUniform(totalDeltaSpeedUniform)
{
    LOGI("Ellipse::Ellipse()");
    m_bIsVisible = true;
    init();
}

Ellipse::~Ellipse() {
    LOGI("Ellipse::~Ellipse()");
    // Off attributes
//    glDisableVertexAttribArray(m_nSpeedAttr);
//    glDisableVertexAttribArray(m_nDeltaAttr);
//    glDisableVertexAttribArray(m_nColorStartAttr);
//    glDisableVertexAttribArray(m_nColorEndAttr);

    delete [] m_pColorStartArray;
    delete [] m_pColorEndArray;
    delete [] m_pArrayPosition;
    delete [] m_pArrayDelta;
}

void Ellipse::render() {
    //LOGI("Ellipse::render(); Cx: %f; Cy: %f; Cc: %d; Rx: %f; Ry: %f;", CENTER_X, CENTER_Y, m_nCount, m_fRadius[0], m_fRadius[1]);
    // Need draw this object?
    if (!m_bIsVisible) {
        return;
    }

    setValues();

    // Use render shader programm
    glUseProgram(m_nProgramId);
    checkGLError("Ellipse - glUseProgram");

    // Choose you texture
    glBindTexture(GL_TEXTURE_2D, m_nTextureId);
    checkGLError("Ellipse - glBindTexture");

    // Fill attributes and uniforms
    // Speed
    glVertexAttribPointer(m_nSpeedAttr, 1, GL_FLOAT, GL_FALSE, 0, m_pArrayPosition);
    checkGLError("Ellipse - glVertexAttribPointer - m_nSpeedAttr");
    glEnableVertexAttribArray(m_nSpeedAttr);
    checkGLError("Ellipse - glVertexAttribPointer - m_nSpeedAttr - enabled");

    // Delta for color mix
    glVertexAttribPointer(m_nDeltaAttr, 1, GL_FLOAT, GL_FALSE, 0, m_pArrayDelta);
    checkGLError("Ellipse - glVertexAttribPointer - m_nDeltaAttr");
    glEnableVertexAttribArray(m_nDeltaAttr);
    checkGLError("Ellipse - glVertexAttribPointer - m_nDeltaAttr - enabled");

    // Color start
    glVertexAttribPointer(m_nColorStartAttr, 4, GL_FLOAT, GL_FALSE, 0, m_pColorStartArray);
    checkGLError("Ellipse - glVertexAttribPointer - m_nColorStartAttr");
    glEnableVertexAttribArray(m_nColorStartAttr);
    checkGLError("Ellipse - glVertexAttribPointer - m_nColorStartAttr - enabled");

    // Color end
    glVertexAttribPointer(m_nColorEndAttr, 4, GL_FLOAT, GL_FALSE, 0, m_pColorEndArray);
    checkGLError("Ellipse - glVertexAttribPointer - m_nColorEndAttr");
    glEnableVertexAttribArray(m_nColorEndAttr);
    checkGLError("Ellipse - glVertexAttribPointer - m_nColorEndAttr - enabled");

    // Position
    glUniform2f(m_nPositionUniform, m_fCenterCoords[0], m_fCenterCoords[1]);
    checkGLError("Ellipse - glUniform2f - m_nPositionUniform");

    // Radius
    glUniform2f(m_nRadiusUniform, m_fRadius[0], m_fRadius[1]);
    checkGLError("Ellipse - glUniform2f - m_nRadiusUniform");

    // Size
    glUniform2f(m_nSizeUniform, m_fSizeUniformArray[0], m_fSizeUniformArray[1]);
    checkGLError("Ellipse - glUniform2f - m_nSizeUniform");

    // Total singleSpeed
    glUniform1f(m_nTotalDeltaSpeedUniform, m_fTotalDeltaSpeed);
    checkGLError("Ellipse - glUniform1f - m_nTotalDeltaSpeedUniform");

    // Draw poligon
    glDrawArrays(GL_POINTS, 0, m_nCount);
    checkGLError("Ellipse - glDrawArrays");

    // Off attributes
    glDisableVertexAttribArray(m_nSpeedAttr);
    glDisableVertexAttribArray(m_nDeltaAttr);
    glDisableVertexAttribArray(m_nColorStartAttr);
    glDisableVertexAttribArray(m_nColorEndAttr);
}

void Ellipse::init() {
    //LOGI("Ellipse::init(); Cx: %f; Cy: %f; Cc: %d; Rx: %f; Ry: %f;", CENTER_X, CENTER_Y, m_nCount, m_fRadius[0], m_fRadius[1]);
    // Set frequency interval to 0
    m_nFrequencyInterval = 0;
    // For default reset transparency
    m_bIsResetTransparency = false;
    // Current speed
    m_fTotalDeltaSpeed = 5000.0f;
    // Delta rotate speed
    m_fDeltaSpeed = 0.01f;
    // For radius
    m_fRadius[0] = m_fRadiusX;
    m_fRadius[1] = m_fRadiusY;
    // For center of circle
    m_fCenterCoords[0] = m_fCenterX;
    m_fCenterCoords[1] = m_fCenterY;

    // 4 color * count
    m_pColorStartArray = new GLfloat[m_nCount * 4];
    Methods::fillArray(m_pColorStartArray, 0.0f, m_nCount * 4);

    // 4 color * count
    m_pColorEndArray = new GLfloat[m_nCount * 4];
    Methods::fillArray(m_pColorEndArray, 0.0f, m_nCount * 4);
    switch(m_oColorType) {
        case RED :
            Methods::fillArrayRGBA(m_pColorStartArray, m_nCount, 1.0f, 0.0f, 0.0f, m_fTransparency);
            Methods::fillArrayRGBA(m_pColorEndArray, m_nCount, 1.0f, 0.0f, 0.0f, m_fTransparency);
            break;

        case GREEN:
            Methods::fillArrayRGBA(m_pColorStartArray, m_nCount, 0.0f, 1.0f, 0.0f, m_fTransparency);
            Methods::fillArrayRGBA(m_pColorEndArray, m_nCount, 0.0f, 1.0f, 0.0f, m_fTransparency);
            break;

        case BLUE:
            Methods::fillArrayRGBA(m_pColorStartArray, m_nCount, 0.0f, 0.0f, 1.0f, m_fTransparency);
            Methods::fillArrayRGBA(m_pColorEndArray, m_nCount, 0.0f, 0.0f, 1.0f, m_fTransparency);
            break;

        case WHITE:
            Methods::fillArrayRGBA(m_pColorStartArray, m_nCount, 1.0f, 1.0f, 1.0f, m_fTransparency);
            Methods::fillArrayRGBA(m_pColorEndArray, m_nCount, 1.0f, 1.0f, 1.0f, m_fTransparency);
            break;
    }

    // Size mix from ... to
    m_fSizeUniformArray[0] = pointSize;
    m_fSizeUniformArray[1] = pointSize;
    if (RANDOM == m_oColorType && NONE == m_oFrequency) {
        m_fSizeUniformArray[0] = (GLfloat)Methods::getStrictRandom((int)(pointSize / 2)) + 1.0f;
        m_fSizeUniformArray[1] = (GLfloat)Methods::getStrictRandom((int)pointSize) + 5.0f;
    }

    // Initial position
    m_pArrayPosition = new GLfloat[m_nCount];
    for (int i = 0; i < m_nCount; i++) {
        if (!m_bIsMove) {
            m_pArrayPosition[i] = (GLfloat)Methods::getStrictRandom(10000);
        } else {
            m_pArrayPosition[i] = (GLfloat)i;
        }
    }

    // Random delta for color
    m_pArrayDelta = new GLfloat[m_nCount];
    for (int i = 0; i < m_nCount; i++) {
        m_pArrayDelta[i] = Methods::getShortRandom();
    }
}

void Ellipse::setValues() {
    // Every point move around
    if (m_bIsMove) {
        if (m_fTotalDeltaSpeed > 10000.0f || m_fTotalDeltaSpeed < 0.0f) {
            m_fDeltaSpeed *= -1.0f;
        }
        m_fTotalDeltaSpeed = m_fTotalDeltaSpeed + m_fDeltaSpeed;
    }

    // Change colors and transparency random
    if (RANDOM == m_oColorType) {
        for(int i = 0; i < m_nCount; i++) {
            // Color start
            m_pColorStartArray[i * 4] = Methods::getShortRandom() * 0.5f;
            m_pColorStartArray[i * 4 + 1] = Methods::getShortRandom() * 0.5f;
            m_pColorStartArray[i * 4 + 2] = Methods::getShortRandom() * 0.5f;
            m_pColorStartArray[i * 4 + 3] = Methods::getShortRandom() * 0.5f;

            // Color end
            m_pColorEndArray[i * 4] = Methods::getShortRandom() + 0.5f;
            m_pColorEndArray[i * 4 + 1] = Methods::getShortRandom() + 0.5f;
            m_pColorEndArray[i * 4 + 2] = Methods::getShortRandom() + 0.5f;
            m_pColorEndArray[i * 4 + 3] = Methods::getShortRandom() + 0.5f;
        }
    }

    // Change transparency
    if (NONE != m_oFrequency && RANDOM != m_oColorType) {
        switch(m_oFrequency) {
            case LOW :
                if (m_nFrequencyInterval % 20 == 0) {
                    m_bIsResetTransparency = true;
                }
                break;
            case MIDDLE :
                if (m_nFrequencyInterval % 10 == 0) {
                    m_bIsResetTransparency = true;
                }
                break;
            case HIGH :
                if (m_nFrequencyInterval % 5 == 0) {
                    m_bIsResetTransparency = true;
                }
                break;
        }

        // Change transparency and reset counter
        if (m_bIsResetTransparency) {
            m_nFrequencyInterval = 0;
            m_bIsResetTransparency = false;

            for(int i = 0; i < m_nCount; i++) {
                m_pColorStartArray[i * 4 + 3] = Methods::getShortRandom() * m_fTransparency * 0.5f;
                m_pColorEndArray[i * 4 + 3] = Methods::getShortRandom() * m_fTransparency * 0.8f;
            }
        }
        m_nFrequencyInterval++;
    }
}

void Ellipse::changeDirection(bool isLeftOrRight) {
    if (isLeftOrRight) {
        m_fDeltaSpeed = -fabsf(m_fDeltaSpeed);
    } else {
        m_fDeltaSpeed = fabsf(m_fDeltaSpeed);
    }
}


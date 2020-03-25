#include "Star.h"

Star::Star(FUNCTION_TYPE type,
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
           GLuint starTotalDeltaSpeed) : m_oType(type),
                                         m_oColor(color),
                                         m_nCount(count),
                                         m_fCenterX(centerX),
                                         m_fCenterY(centerY),
                                         m_fRadiusX(radiusX),
                                         m_fRadiusY(radiusY),
                                         m_nProgramId(programID),
                                         m_nTextureId(textureID),
                                         m_nStarsAngle(starsAngle),
                                         m_nStarColor(starColor),
                                         m_nStarCenter(starCenter),
                                         m_nStarRadius(starRadius),
                                         m_nStarArgumentsX(starArgumentsX),
                                         m_nStarArgumentsY(starArgumentsY),
                                         m_nStarSize(starSize),
                                         m_nStarTotalDeltaSpeed(starTotalDeltaSpeed)
{
    LOGI("Star::Star()");
    m_bIsVisible = true;
    init();
}

Star::~Star() {
    LOGI("Star::~Star()");
    // Off attributes
//    glDisableVertexAttribArray(m_nStarsAngle);
//    glDisableVertexAttribArray(m_nStarColor);
    delete [] m_pArrayColor;
    delete [] m_pArrayPosition;
}

void Star::render() {
    //LOGI("Star::render(); Cx: %f; Cy: %f; Cc: %d; Rx: %f; Ry: %f;", CENTER_X, CENTER_Y, m_nCount, radius[0], radius[1]);
    // Need draw this object?
    if (!m_bIsVisible) {
        return;
    }

    setValues();

    // Use render shader programm
    glUseProgram(m_nProgramId);
    checkGLError("Star - glUseProgram");

    // Choose you texture
    glBindTexture(GL_TEXTURE_2D, m_nTextureId);
    checkGLError("Star - glBindTexture");

    // Fill attributes and uniforms
    // Init position
    glVertexAttribPointer(m_nStarsAngle, 1, GL_FLOAT, GL_FALSE, 0, m_pArrayPosition);
    checkGLError("Star - glVertexAttribPointer - m_nStarsAngle");
    glEnableVertexAttribArray(m_nStarsAngle);
    checkGLError("Star - glVertexAttribPointer - m_nStarsAngle - enabled");

    // For color
    glVertexAttribPointer(m_nStarColor, 4, GL_FLOAT, GL_FALSE, 0, m_pArrayColor);
    checkGLError("Star - glVertexAttribPointer - m_nStarColor");
    glEnableVertexAttribArray(m_nStarColor);
    checkGLError("Star - glVertexAttribPointer - m_nStarColor - enabled");

    // Center
    glUniform2f(m_nStarCenter, m_fCenterX, m_fCenterY);
    checkGLError("Star - glUniform2f - m_nStarCenter");

    // Radius
    glUniform2f(m_nStarRadius, m_fRadiusX, m_fRadiusY);
    checkGLError("Star - glUniform2f - m_nStarRadius");

    // Arguments X
    glUniform2f(m_nStarArgumentsX, m_fArgumentsX[0], m_fArgumentsX[1]);
    checkGLError("Star - glUniform2f - m_nStarArgumentsX");

    // Arguments Y
    glUniform2f(m_nStarArgumentsY, m_fArgumentsY[0], m_fArgumentsY[1]);
    checkGLError("Star - glUniform2f - m_nStarArgumentsY");

    // Size of point
    glUniform1f(m_nStarSize, m_fSizePoint);
    checkGLError("Star - glUniform2f - m_nStarSize");

    // Delta speed
    glUniform1f(m_nStarTotalDeltaSpeed, m_fTotalDeltaSpeed);
    checkGLError("Star - glUniform2f - deltaPositionUniform");

    // Draw poligon
    glDrawArrays(GL_POINTS, 0, m_nCount);
    checkGLError("Star - glDrawArrays");

    // Off attributes
    glDisableVertexAttribArray(m_nStarsAngle);
    glDisableVertexAttribArray(m_nStarColor);
}

void Star::init() {
    //LOGI("Star::init(); Cx: %f; Cy: %f; Cc: %d; Rx: %f; Ry: %f;", CENTER_X, CENTER_Y, m_nCount);
    // Parameters for functions
    m_fDeltaArgument = 0.00001f;
    m_fDeltaArgumentX[0] = 0.000001f;
    m_fDeltaArgumentX[1] = 0.000001f;
    m_fDeltaArgumentY[0] = 0.000001f;
    m_fDeltaArgumentY[1] = 0.000001f;

    // Default arguments
    // For X
    m_fArgumentsX[0] = 1.0f;
    m_fArgumentsX[1] = 1.0f;
    // For Y
    m_fArgumentsY[0] = 1.0f;
    m_fArgumentsY[1] = 1.0f;

    // Radius restrict
    m_fRadiusStep = 0.0001f;
    m_fRadiusXMax = 0.7f;
    m_fRadiusYMax = 0.7f;

    // User choice
    switch(m_oType) {
        case DYNAMIC_UNIFORM :
            m_fArgumentsX[0] = 1.1f;
            m_fArgumentsX[1] = 1.1f;
            m_fArgumentsY[0] = 1.1f;
            m_fArgumentsY[1] = 1.1f;
            break;
        case DYNAMIC_RANDOM :
            // Get upper strict
            m_fStrictArgumentX[0] = 0.55f + (GLfloat)Methods::getStrictRandom(5);
            m_fStrictArgumentX[1] = 0.55f + (GLfloat)Methods::getStrictRandom(5);
            m_fStrictArgumentY[0] = 0.55f + (GLfloat)Methods::getStrictRandom(5);
            m_fStrictArgumentY[1] = 0.55f + (GLfloat)Methods::getStrictRandom(5);
            // Start values
            m_fArgumentsX[0] = m_fStrictArgumentX[0];
            m_fArgumentsX[1] = m_fStrictArgumentX[1];
            m_fArgumentsY[0] = m_fStrictArgumentY[0];
            m_fArgumentsY[1] = m_fStrictArgumentY[1];
            break;
        case HYPOCYCLOID :
            m_fArgumentsX[0] = 1.1f;
            m_fArgumentsX[1] = 1.1f;
            m_fArgumentsY[0] = 1.1f;
            m_fArgumentsY[1] = 1.1f;
            break;
        case EPICYCLOID :
            m_fArgumentsX[0] = 3.1f;
            m_fArgumentsX[1] = 3.1f;
            m_fArgumentsY[0] = 3.1f;
            m_fArgumentsY[1] = 3.1f;
            break;
        case STATIC_RANDOM :
            GLfloat randFloatValue1 = Methods::getShortRandom();
            GLfloat randFloatValue2 = Methods::getShortRandom();
            GLfloat randIntValue1 = (GLfloat)Methods::getStrictRandom(5) + 1.0f;
            GLfloat randIntValue2 = (GLfloat)Methods::getStrictRandom(5) + 1.0f;
            m_fArgumentsX[0] = randIntValue1 + randFloatValue1;
            m_fArgumentsX[1] = randIntValue2 + randFloatValue2;
            m_fArgumentsY[0] = randIntValue1 + randFloatValue1;
            m_fArgumentsY[1] = randIntValue2 + randFloatValue2;
            break;
    }

    //LOGI("Star::init - ARGS(); Ax0: %f; Ax1: %f; Ay0: %f; Ay1: %f;", m_fArgumentsX[0], m_fArgumentsX[1], m_fArgumentsY[0], m_fArgumentsY[1]);
    // Point sizePoint
    m_fSizePoint = 5.0f;
    // Current speed
    m_fTotalDeltaSpeed = 0.0f;
    // Delta rotate speed
    m_fDeltaSpeed = 0.01f;

    // 4 color * count
    m_pArrayColor = new GLfloat[m_nCount * 4];
    Methods::fillArray(m_pArrayColor, 0.0f, m_nCount * 4);
    switch(m_oColor) {
        case RED:
            Methods::fillArrayRGBA(m_pArrayColor, m_nCount, 1.0f, 0.0f, 0.0f, 1.0f);
            break;
        case GREEN:
            Methods::fillArrayRGBA(m_pArrayColor, m_nCount, 0.0f, 1.0f, 0.0f, 1.0f);
            break;
        case BLUE:
            Methods::fillArrayRGBA(m_pArrayColor, m_nCount, 0.0f, 0.0f, 1.0f, 1.0f);
            break;
        case BROWN:
            Methods::fillArrayRGBA(m_pArrayColor, m_nCount, 0.647059f, 0.164706f, 0.164706f, 1.0f);
            break;

    }

    // Initial position
    m_pArrayPosition = new GLfloat[m_nCount];
    for(int i = 0; i < m_nCount; i++) {
        m_pArrayPosition[i] = (GLfloat)i;
    }
}

void Star::setValues() {
    // For change speed
    if (m_fTotalDeltaSpeed > 1000.0f || m_fTotalDeltaSpeed < 0.0f) {
        m_fDeltaSpeed *= -1.0f;
    }

    m_fTotalDeltaSpeed = m_fTotalDeltaSpeed + m_fDeltaSpeed;

    // For change arguments dynamic
    if (DYNAMIC_UNIFORM == m_oType) {
        if (m_fArgumentsX[0] > 1.3f || m_fArgumentsX[0] < 1.0f) {
            m_fDeltaArgument *= -1.0f;
        }

        m_fArgumentsX[0] = m_fArgumentsX[0] + m_fDeltaArgument;
        m_fArgumentsX[1] = m_fArgumentsX[1] + m_fDeltaArgument;
        m_fArgumentsY[0] = m_fArgumentsY[0] + m_fDeltaArgument;
        m_fArgumentsY[1] = m_fArgumentsY[1] + m_fDeltaArgument;
    } else if (DYNAMIC_RANDOM == m_oType) {
        // For X arguments
        if (m_fArgumentsX[0] > m_fStrictArgumentX[0] || m_fArgumentsX[0] < 0.5f) {
            m_fDeltaArgumentX[0] *= -1.0f;
        }
        m_fArgumentsX[0] = m_fArgumentsX[0] + m_fDeltaArgumentX[0];

        if (m_fArgumentsX[1] > m_fStrictArgumentX[1] || m_fArgumentsX[1] < 0.5f) {
            m_fDeltaArgumentX[1] *= -1.0f;
        }
        m_fArgumentsX[1] = m_fArgumentsX[1] + m_fDeltaArgumentX[1];

        // For Y arguments
        if (m_fArgumentsY[0] > m_fStrictArgumentY[0] || m_fArgumentsY[0] < 0.5f) {
            m_fDeltaArgumentY[0] *= -1.0f;
        }
        m_fArgumentsY[0] = m_fArgumentsY[0] + m_fDeltaArgumentY[0];

        if (m_fArgumentsY[1] > m_fStrictArgumentY[1] || m_fArgumentsY[1] < 0.5f) {
            m_fDeltaArgumentY[1] *= -1.0f;
        }
        m_fArgumentsY[1] = m_fArgumentsY[1] + m_fDeltaArgumentY[1];

        // For radius change dynamically
        if (m_fRadiusX > m_fRadiusXMax || m_fRadiusX < 0.1f) {
            m_fRadiusStep *= -1.0f;
        }
        m_fRadiusX = m_fRadiusX + m_fRadiusStep;

        if (m_fRadiusY > m_fRadiusYMax || m_fRadiusY < 0.1f) {
            m_fRadiusStep *= -1.0f;
        }
        m_fRadiusY = m_fRadiusY + m_fRadiusStep;
    }

    // Fill colors
    if (RANDOM == m_oColor) {
        for(int i = 0; i < m_nCount; i++) {
            m_pArrayColor[i * 4] = Methods::getShortRandom();
            m_pArrayColor[i * 4 + 1] = Methods::getShortRandom();
            m_pArrayColor[i * 4 + 2] = Methods::getShortRandom();
            m_pArrayColor[i * 4 + 3] = Methods::getShortRandom() + 0.1f;
        }
    }
}
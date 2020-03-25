#include "Snow.h"

Snow::Snow( GLuint count,
            GLuint maxSize,
            COLOR_TYPE colorType,
            WIND_POWER windType,
            GLfloat angleFall,
            GLfloat snowEnds,
            GLuint programID,
            GLuint textureID,
            GLuint attrStartPosition,
            GLuint attrFallSpeed,
            GLuint attrSnowSize,
            GLuint attrSnowShift,
            GLuint attrSnowColor,
            GLuint uniformAngle,
            GLuint attrFreq,
            GLuint attrAmplitude) : m_nCount(count),
                                    m_nMaxSize(maxSize),
                                    m_oColorType(colorType),
                                    m_oWindType(windType),
                                    m_fSnowEnds(snowEnds),
                                    m_nProgramId(programID),
                                    m_nTextureId(textureID),
                                    m_nAttrStartPosition(attrStartPosition),
                                    m_nAttrFallSpeed(attrFallSpeed),
                                    m_nAttrSnowSize(attrSnowSize),
                                    m_nAttrSnowShift(attrSnowShift),
                                    m_nAttrSnowColor(attrSnowColor),
                                    m_nUniformAngle(uniformAngle),
                                    m_nAttrFreq(attrFreq),
                                    m_nAttrAmplitude(attrAmplitude),
                                    m_nAmplitudeStrict(50),
                                    m_bIsChangeAmplitude(false)
{
    LOGI("Snow::Snow()");
    m_bIsVisible = true;
    m_fRadianAngleFall = m_fNewRadianAngleFall = Methods::degreesToRadians(angleFall);
    init();
}

Snow::~Snow() {
    LOGI("Snow::~Snow()");
    // Off attributes
//    glDisableVertexAttribArray(m_nAttrStartPosition);
//    glDisableVertexAttribArray(m_nAttrFallSpeed);
//    glDisableVertexAttribArray(m_nAttrSnowSize);
//    glDisableVertexAttribArray(m_nAttrSnowShift);
//    glDisableVertexAttribArray(m_nAttrSnowColor);
//    glDisableVertexAttribArray(m_nAttrFreq);
//    glDisableVertexAttribArray(m_nAttrAmplitude);

    delete [] m_pArrayStartPosition;
    delete [] m_pArrayFallSpeed;
    delete [] m_pArrayFallSpeedSteps;
    delete [] m_pArraySnowSize;
    delete [] m_pArraySnowShift;
    delete [] m_pArraySnowColor;
    delete [] m_pArraySnowFreq;
    delete [] m_pArraySnowAmplitude;
}

void Snow::render() {
    //LOGI("Star::render(); Cx: %f; Cy: %f; Cc: %d; Rx: %f; Ry: %f;", CENTER_X, CENTER_Y, m_nCount, radius[0], radius[1]);
    // Need draw this object?
    if (!m_bIsVisible)
        return;

    setValues();

    // Use render shader program
    glUseProgram(m_nProgramId);
    checkGLError("Snow - glUseProgram");

    // Choose you texture
    glBindTexture(GL_TEXTURE_2D, m_nTextureId);
    checkGLError("Snow - glBindTexture");

    // Fill attributes and uniforms
    // Position
    glVertexAttribPointer(m_nAttrStartPosition, 1, GL_FLOAT, GL_FALSE, 0, m_pArrayStartPosition);
    checkGLError("Snow - glVertexAttribPointer - m_nAttrStartPosition");
    glEnableVertexAttribArray(m_nAttrStartPosition);
    checkGLError("Snow - glVertexAttribPointer - m_nAttrStartPosition - enabled");

    // Speed
    glVertexAttribPointer(m_nAttrFallSpeed, 1, GL_FLOAT, GL_FALSE, 0, m_pArrayFallSpeed);
    checkGLError("Snow - glVertexAttribPointer - m_nAttrFallSpeed");
    glEnableVertexAttribArray(m_nAttrFallSpeed);
    checkGLError("Snow - glVertexAttribPointer - m_nAttrFallSpeed - enabled");

    // Snow size
    glVertexAttribPointer(m_nAttrSnowSize, 1, GL_FLOAT, GL_FALSE, 0, m_pArraySnowSize);
    checkGLError("Snow - glVertexAttribPointer - m_nAttrSnowSize");
    glEnableVertexAttribArray(m_nAttrSnowSize);
    checkGLError("Snow - glVertexAttribPointer - m_nAttrSnowSize - enabled");

    // Snow shift
    glVertexAttribPointer(m_nAttrSnowShift, 1, GL_FLOAT, GL_FALSE, 0, m_pArraySnowShift);
    checkGLError("Snow - glVertexAttribPointer - m_nAttrSnowShift");
    glEnableVertexAttribArray(m_nAttrSnowShift);
    checkGLError("Snow - glVertexAttribPointer - m_nAttrSnowShift - enabled");

    // Snow colors
    glVertexAttribPointer(m_nAttrSnowColor, 4, GL_FLOAT, GL_FALSE, 0, m_pArraySnowColor);
    checkGLError("Snow - glVertexAttribPointer - m_nAttrSnowColor");
    glEnableVertexAttribArray(m_nAttrSnowColor);
    checkGLError("Snow - glVertexAttribPointer - m_nAttrSnowColor - enabled");

    // Angle rotate
    glUniform1f(m_nUniformAngle, m_fRadianAngleFall);
    checkGLError("Star - glUniform2f - starSize");

    // Snow frequency
    glVertexAttribPointer(m_nAttrFreq, 1, GL_FLOAT, GL_FALSE, 0, m_pArraySnowFreq);
    checkGLError("Snow - glVertexAttribPointer - m_nAttrFreq");
    glEnableVertexAttribArray(m_nAttrFreq);
    checkGLError("Snow - glVertexAttribPointer - m_nAttrFreq - enabled");

    // Snow amplitude
    glVertexAttribPointer(m_nAttrAmplitude, 1, GL_FLOAT, GL_FALSE, 0, m_pArraySnowAmplitude);
    checkGLError("Snow - glVertexAttribPointer - m_nAttrAmplitude");
    glEnableVertexAttribArray(m_nAttrAmplitude);
    checkGLError("Snow - glVertexAttribPointer - m_nAttrAmplitude - enabled");

    // Draw poligon
    glDrawArrays(GL_POINTS, 0, m_nCount);
    checkGLError("Snow - glDrawArrays");

    // Off attributes
    glDisableVertexAttribArray(m_nAttrStartPosition);
    glDisableVertexAttribArray(m_nAttrFallSpeed);
    glDisableVertexAttribArray(m_nAttrSnowSize);
    glDisableVertexAttribArray(m_nAttrSnowShift);
    glDisableVertexAttribArray(m_nAttrSnowColor);
    glDisableVertexAttribArray(m_nAttrFreq);
    glDisableVertexAttribArray(m_nAttrAmplitude);
}

void Snow::init() {
    // For random start positions
    GLfloat stepForStart = 2.0f / (GLfloat) m_nCount;
    GLfloat startPosition = -1.0f;
    // Set start positions
    m_pArrayStartPosition = new GLfloat[m_nCount];
    for(int i = 0; i < m_nCount; i++, startPosition += stepForStart) {
        m_pArrayStartPosition[i] = -1.0;
    }

    // Set speed for single object
    m_pArrayFallSpeed = new GLfloat[m_nCount];
    Methods::fillArray(m_pArrayFallSpeed, 0.0f, m_nCount);

    // Get random steps for objects fall
    m_pArrayFallSpeedSteps = new GLfloat[m_nCount];
    setPower(WIND_POWER::SLOW);

    // Set random size
    m_pArraySnowSize = new GLfloat[m_nCount];
    for(int i = 0; i < m_nCount; i++) {
        m_pArraySnowSize[i] = 3.0f + (GLfloat)Methods::getStrictRandom(m_nMaxSize);
    }

    // Get shift
    m_pArraySnowShift = new GLfloat[m_nCount];
    for(int i = 0; i < m_nCount; i++) {
        m_pArraySnowShift[i] = Methods::getFullRandom();
    }

    // Set random frequency
    m_pArraySnowFreq = new GLfloat[m_nCount];
    for(int i = 0; i < m_nCount; i++) {
        m_pArraySnowFreq[i] = (GLfloat)Methods::getStrictRandom(10) / 1000.0f;
    }

    // Set random amplitude
    m_pArraySnowAmplitude = new GLfloat[m_nCount];
    for(int i = 0; i < m_nCount; i++) {
        m_pArraySnowAmplitude[i] = 20.0f + (GLfloat)Methods::getStrictRandom(m_nAmplitudeStrict);
    }

    // Fill color
    m_pArraySnowColor = new GLfloat[m_nCount * 4];
    Methods::fillArray(m_pArraySnowColor, 0.0f, m_nCount * 4);
    switch(m_oColorType) {
        case WHITE :
            Methods::fillArrayRGBA(m_pArraySnowColor, m_nCount, 1.0f, 1.0f, 1.0f, 1.0f);
            break;
        case BLUE :
            Methods::fillArrayRGBA(m_pArraySnowColor, m_nCount, 0.74902f, 0.847059f, 0.847059f, 1.0f);
            break;
        case GREY :
            Methods::fillArrayRGBA(m_pArraySnowColor, m_nCount, 0.658824f, 0.658824f, 0.658824f, 1.0f);
            break;
    }
}

void Snow::setValues() {
    // For change speed
    for(int i = 0; i < m_nCount; i++) {
        if (m_pArrayFallSpeed[i] > m_fSnowEnds) {
            m_pArrayFallSpeed[i] = 0.0f;
        }

        m_pArrayFallSpeed[i] += m_pArrayFallSpeedSteps[i];

        // Change amplitude
        if (m_bIsChangeAmplitude) {
            m_pArraySnowAmplitude[i] = (GLfloat)Methods::getStrictRandom(m_nAmplitudeStrict) + 1.0f;
        }

        // Color random
        if (RANDOM == m_oColorType) {
            m_pArraySnowColor[i * 4] = Methods::getShortRandom();
            m_pArraySnowColor[i * 4 + 1] = Methods::getShortRandom();
            m_pArraySnowColor[i * 4 + 2] = Methods::getShortRandom();
            m_pArraySnowColor[i * 4 + 3] = Methods::getShortRandom() + 0.3f;
        }
    }

    // Change angle slow
    GLfloat deltaAngle = fabsf(m_fRadianAngleFall) - fabsf(m_fNewRadianAngleFall);
    if (fabsf(deltaAngle) > 0.05f) {
        if (deltaAngle > 0.0f) {
            m_fRadianAngleFall += 0.005f;
        } else {
            m_fRadianAngleFall -= 0.005f;
        }
    }

    m_bIsChangeAmplitude = false;
}

void Snow::setDegrees(GLfloat angle) {
    m_fNewRadianAngleFall = Methods::degreesToRadians(angle);
}

void Snow::setPower(WIND_POWER power) {
    m_bIsChangeAmplitude = true;
    GLfloat ratio;

    switch(power) {
        case SLOW :
            ratio = 0.005;
            m_nAmplitudeStrict = 70;
            break;
        case MIDDLE :
            ratio = 0.01;
            m_nAmplitudeStrict = 40;
            break;
        case FAST :
            ratio = 0.1;
            m_nAmplitudeStrict = 2;
            break;
        default: ratio = 0.01;
    }

    for(int i = 0; i < m_nCount; i++) {
        m_pArrayFallSpeedSteps[i] = Methods::getShortRandom() * ratio;
    }
}
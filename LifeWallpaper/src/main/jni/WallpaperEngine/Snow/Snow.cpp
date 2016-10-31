#include "Snow.h"

void Snow::render() {
    //LOGI("Star::render(); Cx: %f; Cy: %f; Cc: %d; Rx: %f; Ry: %f;", CENTER_X, CENTER_Y, count, radius[0], radius[1]);
    // Need draw this object?
    if(!isVisible)
        return;

    setValues();

    // Use render shader program
    glUseProgram(programID);
    checkGLError("Snow - glUseProgram");

    // Choose you texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    checkGLError("Snow - glBindTexture");

    // Fill attributes and uniforms
    // Position
    glVertexAttribPointer(attrStartPosition, 1, GL_FLOAT, GL_FALSE, 0, arrayStartPosition);
    checkGLError("Snow - glVertexAttribPointer - attrStartPosition");
    glEnableVertexAttribArray(attrStartPosition);
    checkGLError("Snow - glVertexAttribPointer - attrStartPosition - enabled");

    // Speed
    glVertexAttribPointer(attrFallSpeed, 1, GL_FLOAT, GL_FALSE, 0, arrayFallSpeed);
    checkGLError("Snow - glVertexAttribPointer - attrFallSpeed");
    glEnableVertexAttribArray(attrFallSpeed);
    checkGLError("Snow - glVertexAttribPointer - attrFallSpeed - enabled");

    // Snow size
    glVertexAttribPointer(attrSnowSize, 1, GL_FLOAT, GL_FALSE, 0, arraySnowSize);
    checkGLError("Snow - glVertexAttribPointer - attrSnowSize");
    glEnableVertexAttribArray(attrSnowSize);
    checkGLError("Snow - glVertexAttribPointer - attrSnowSize - enabled");

    // Snow shift
    glVertexAttribPointer(attrSnowShift, 1, GL_FLOAT, GL_FALSE, 0, arraySnowShift);
    checkGLError("Snow - glVertexAttribPointer - attrSnowShift");
    glEnableVertexAttribArray(attrSnowShift);
    checkGLError("Snow - glVertexAttribPointer - attrSnowShift - enabled");

    // Snow colors
    glVertexAttribPointer(attrSnowColor, 4, GL_FLOAT, GL_FALSE, 0, arraySnowColor);
    checkGLError("Snow - glVertexAttribPointer - attrSnowColor");
    glEnableVertexAttribArray(attrSnowColor);
    checkGLError("Snow - glVertexAttribPointer - attrSnowColor - enabled");

    // Angle rotate
    glUniform1f(uniformAngle, radianAngleFall);
    checkGLError("Star - glUniform2f - starSize");

    // Snow frequency
    glVertexAttribPointer(attrFreq, 1, GL_FLOAT, GL_FALSE, 0, arraySnowFreq);
    checkGLError("Snow - glVertexAttribPointer - attrFreq");
    glEnableVertexAttribArray(attrFreq);
    checkGLError("Snow - glVertexAttribPointer - attrFreq - enabled");

    // Snow amplitude
    glVertexAttribPointer(attrAmplitude, 1, GL_FLOAT, GL_FALSE, 0, arraySnowAmplitude);
    checkGLError("Snow - glVertexAttribPointer - attrAmplitude");
    glEnableVertexAttribArray(attrAmplitude);
    checkGLError("Snow - glVertexAttribPointer - attrAmplitude - enabled");

    // Draw poligon
    glDrawArrays(GL_POINTS, 0, count);
    checkGLError("Snow - glDrawArrays");

    // Off attributes
    glDisableVertexAttribArray(attrStartPosition);
    glDisableVertexAttribArray(attrFallSpeed);
    glDisableVertexAttribArray(attrSnowSize);
    glDisableVertexAttribArray(attrSnowShift);
    glDisableVertexAttribArray(attrSnowColor);
    glDisableVertexAttribArray(attrFreq);
    glDisableVertexAttribArray(attrAmplitude);
}

void Snow::init(){
    // For random start positions
    GLfloat stepForStart = 2.0f / (GLfloat) count;
    GLfloat startPosition = -1.0f;
    // Set start positions
    arrayStartPosition = new GLfloat[count];
    for(int i = 0; i < count; i++, startPosition += stepForStart) {
        arrayStartPosition[i] = -1.0;
    }

    // Set speed for single object
    arrayFallSpeed = new GLfloat[count];
    Methods::fillArray(arrayFallSpeed, 0.0f, count);

    // Get random steps for objects fall
    arrayFallSpeedSteps = new GLfloat[count];
    setPower(WIND_POWER::SLOW);

    // Set random size
    arraySnowSize = new GLfloat[count];
    for(int i = 0; i < count; i++) {
        arraySnowSize[i] = 3.0f + (GLfloat)Methods::getStrictRandom(maxSize);
    }

    // Get shift
    arraySnowShift = new GLfloat[count];
    for(int i = 0; i < count; i++) {
        arraySnowShift[i] = Methods::getFullRandom();
    }

    // Set random frequency
    arraySnowFreq = new GLfloat[count];
    for(int i = 0; i < count; i++) {
        arraySnowFreq[i] = (GLfloat)Methods::getStrictRandom(10) / 1000.0f;
    }

    // Set random amplitude
    arraySnowAmplitude = new GLfloat[count];
    for(int i = 0; i < count; i++) {
        arraySnowAmplitude[i] = 20.0f + (GLfloat)Methods::getStrictRandom(amplitudeStrict);
    }

    // Fill color
    arraySnowColor = new GLfloat[count * 4];
    Methods::fillArray(arraySnowColor, 0.0f, count * 4);
    switch(colorType){
        case WHITE :
            Methods::fillArrayRGBA(arraySnowColor, count, 1.0f, 1.0f, 1.0f, 1.0f);
            break;
        case BLUE :
            Methods::fillArrayRGBA(arraySnowColor, count, 0.74902f, 0.847059f, 0.847059f, 1.0f);
            break;
        case GREY :
            Methods::fillArrayRGBA(arraySnowColor, count, 0.658824f, 0.658824f, 0.658824f, 1.0f);
            break;
    }
}

void Snow::setValues(){
    // For change speed
    for(int i = 0; i < count; i++){
        if(arrayFallSpeed[i] > snowEnds)
            arrayFallSpeed[i] = 0.0f;
        arrayFallSpeed[i] += arrayFallSpeedSteps[i];

        // Change amplitude
        if(isChangeAmplitude)
            arraySnowAmplitude[i] = (GLfloat)Methods::getStrictRandom(amplitudeStrict) + 1.0f;

        // Color random
        if(RANDOM == colorType){
            arraySnowColor[i * 4] = Methods::getShortRandom();
            arraySnowColor[i * 4 + 1] = Methods::getShortRandom();
            arraySnowColor[i * 4 + 2] = Methods::getShortRandom();
            arraySnowColor[i * 4 + 3] = Methods::getShortRandom() + 0.3f;
        }
    }

    // Change angle slow
    GLfloat deltaAngle = fabsf(radianAngleFall) - fabsf(newRadianAngleFall);
    if(fabsf(deltaAngle) > 0.05f)
    if(deltaAngle > 0.0f)
        radianAngleFall += 0.005f;
    else
        radianAngleFall -= 0.005f;

    isChangeAmplitude = false;
}

void Snow::setDegrees(GLfloat _angle){
    newRadianAngleFall = Methods::degreesToRadians(_angle);
}

void Snow::setPower(WIND_POWER _power){
    isChangeAmplitude = true;
    GLfloat ratio;
    switch(_power){
        case SLOW :
            ratio = 0.005;
            amplitudeStrict = 70;
            break;
        case MIDDLE :
            ratio = 0.01;
            amplitudeStrict = 40;
            break;
        case FAST :
            ratio = 0.1;
            amplitudeStrict = 2;
            break;
        default: ratio = 0.01;
    }

    for(int i = 0; i < count; i++) {
        arrayFallSpeedSteps[i] = Methods::getShortRandom() * ratio;
    }
}
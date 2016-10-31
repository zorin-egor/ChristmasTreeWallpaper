#include "Star.h"

void Star::render() {
    //LOGI("Star::render(); Cx: %f; Cy: %f; Cc: %d; Rx: %f; Ry: %f;", CENTER_X, CENTER_Y, count, radius[0], radius[1]);
    // Need draw this object?
    if(!isVisible)
        return;

    setValues();

    // Use render shader programm
    glUseProgram(programID);
    checkGLError("Star - glUseProgram");

    // Choose you texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    checkGLError("Star - glBindTexture");

    // Fill attributes and uniforms
    // Init position
    glVertexAttribPointer(starsAngle, 1, GL_FLOAT, GL_FALSE, 0, arrayPosition);
    checkGLError("Star - glVertexAttribPointer - starsAngle");
    glEnableVertexAttribArray(starsAngle);
    checkGLError("Star - glVertexAttribPointer - starsAngle - enabled");

    // For color
    glVertexAttribPointer(starColor, 4, GL_FLOAT, GL_FALSE, 0, arrayColor);
    checkGLError("Star - glVertexAttribPointer - starColor");
    glEnableVertexAttribArray(starColor);
    checkGLError("Star - glVertexAttribPointer - starColor - enabled");

    // Center
    glUniform2f(starCenter, centerX, centerY);
    checkGLError("Star - glUniform2f - starCenter");

    // Radius
    glUniform2f(starRadius, radiusX, radiusY);
    checkGLError("Star - glUniform2f - starRadius");

    // Arguments X
    glUniform2f(starArgumentsX, argumentsX[0], argumentsX[1]);
    checkGLError("Star - glUniform2f - starArgumentsX");

    // Arguments Y
    glUniform2f(starArgumentsY, argumentsY[0], argumentsY[1]);
    checkGLError("Star - glUniform2f - starArgumentsY");

    // Size of point
    glUniform1f(starSize, sizePoint);
    checkGLError("Star - glUniform2f - starSize");

    // Delta speed
    glUniform1f(starTotalDeltaSpeed, totalDeltaSpeed);
    checkGLError("Star - glUniform2f - deltaPositionUniform");

    // Draw poligon
    glDrawArrays(GL_POINTS, 0, count);
    checkGLError("Star - glDrawArrays");

    // Off attributes
    glDisableVertexAttribArray(starsAngle);
    glDisableVertexAttribArray(starColor);
}

void Star::init(){
    //LOGI("Star::init(); Cx: %f; Cy: %f; Cc: %d; Rx: %f; Ry: %f;", CENTER_X, CENTER_Y, count);
    // Parameters for functions
    deltaArgument = 0.00001f;
    deltaArgumentX[0] = 0.000001f;
    deltaArgumentX[1] = 0.000001f;
    deltaArgumentY[0] = 0.000001f;
    deltaArgumentY[1] = 0.000001f;

    // Default arguments
    // For X
    argumentsX[0] = 1.0f;
    argumentsX[1] = 1.0f;
    // For Y
    argumentsY[0] = 1.0f;
    argumentsY[1] = 1.0f;

    // Radius restrict
    radiusStep = 0.0001f;
    radiusXMax = 0.7f;
    radiusYMax = 0.7f;

    // User choice
    switch(type){
        case DYNAMIC_UNIFORM :
            argumentsX[0] = 1.1f;
            argumentsX[1] = 1.1f;
            argumentsY[0] = 1.1f;
            argumentsY[1] = 1.1f;
            break;
        case DYNAMIC_RANDOM :
            // Get upper strict
            strictArgumentX[0] = 0.55f + (GLfloat)Methods::getStrictRandom(5);
            strictArgumentX[1] = 0.55f + (GLfloat)Methods::getStrictRandom(5);
            strictArgumentY[0] = 0.55f + (GLfloat)Methods::getStrictRandom(5);
            strictArgumentY[1] = 0.55f + (GLfloat)Methods::getStrictRandom(5);
            // Start values
            argumentsX[0] = strictArgumentX[0];
            argumentsX[1] = strictArgumentX[1];
            argumentsY[0] = strictArgumentY[0];
            argumentsY[1] = strictArgumentY[1];
            break;
        case HYPOCYCLOID :
            argumentsX[0] = 1.1f;
            argumentsX[1] = 1.1f;
            argumentsY[0] = 1.1f;
            argumentsY[1] = 1.1f;
            break;
        case EPICYCLOID :
            argumentsX[0] = 3.1f;
            argumentsX[1] = 3.1f;
            argumentsY[0] = 3.1f;
            argumentsY[1] = 3.1f;
            break;
        case STATIC_RANDOM :
            GLfloat randFloatValue1 = Methods::getShortRandom();
            GLfloat randFloatValue2 = Methods::getShortRandom();
            GLfloat randIntValue1 = (GLfloat)Methods::getStrictRandom(5) + 1.0f;
            GLfloat randIntValue2 = (GLfloat)Methods::getStrictRandom(5) + 1.0f;
            argumentsX[0] = randIntValue1 + randFloatValue1;
            argumentsX[1] = randIntValue2 + randFloatValue2;
            argumentsY[0] = randIntValue1 + randFloatValue1;
            argumentsY[1] = randIntValue2 + randFloatValue2;
            break;
    }

    //LOGI("Star::init - ARGS(); Ax0: %f; Ax1: %f; Ay0: %f; Ay1: %f;", argumentsX[0], argumentsX[1], argumentsY[0], argumentsY[1]);
    // Point sizePoint
    sizePoint = 5.0f;
    // Current speed
    totalDeltaSpeed = 0.0f;
    // Delta rotate speed
    deltaSpeed = 0.01f;

    // 4 color * count
    arrayColor = new GLfloat[count * 4];
    Methods::fillArray(arrayColor, 0.0f, count * 4);
    switch(color){
        case RED:
            Methods::fillArrayRGBA(arrayColor, count, 1.0f, 0.0f, 0.0f, 1.0f);
            break;
        case GREEN:
            Methods::fillArrayRGBA(arrayColor, count, 0.0f, 1.0f, 0.0f, 1.0f);
            break;
        case BLUE:
            Methods::fillArrayRGBA(arrayColor, count, 0.0f, 0.0f, 1.0f, 1.0f);
            break;
        case BROWN:
            Methods::fillArrayRGBA(arrayColor, count, 0.647059f, 0.164706f, 0.164706f, 1.0f);
            break;

    }

    // Initial position
    arrayPosition = new GLfloat[count];
    for(int i = 0; i < count; i++)
        arrayPosition[i] = (GLfloat)i;
}

void Star::setValues(){
    // For change speed
    if(totalDeltaSpeed > 1000.0f || totalDeltaSpeed < 0.0f)
        deltaSpeed *= -1.0f;

    totalDeltaSpeed = totalDeltaSpeed + deltaSpeed;

    // For change arguments dynamic
    if(DYNAMIC_UNIFORM == type){
        if(argumentsX[0] > 1.3f || argumentsX[0] < 1.0f)
            deltaArgument *= -1.0f;

        argumentsX[0] = argumentsX[0] + deltaArgument;
        argumentsX[1] = argumentsX[1] + deltaArgument;
        argumentsY[0] = argumentsY[0] + deltaArgument;
        argumentsY[1] = argumentsY[1] + deltaArgument;
    } else if(DYNAMIC_RANDOM == type){
        // For X arguments
        if(argumentsX[0] > strictArgumentX[0] || argumentsX[0] < 0.5f)
            deltaArgumentX[0] *= -1.0f;
        argumentsX[0] = argumentsX[0] + deltaArgumentX[0];

        if(argumentsX[1] > strictArgumentX[1] || argumentsX[1] < 0.5f)
            deltaArgumentX[1] *= -1.0f;
        argumentsX[1] = argumentsX[1] + deltaArgumentX[1];

        // For Y arguments
        if(argumentsY[0] > strictArgumentY[0] || argumentsY[0] < 0.5f)
            deltaArgumentY[0] *= -1.0f;
        argumentsY[0] = argumentsY[0] + deltaArgumentY[0];

        if(argumentsY[1] > strictArgumentY[1] || argumentsY[1] < 0.5f)
            deltaArgumentY[1] *= -1.0f;
        argumentsY[1] = argumentsY[1] + deltaArgumentY[1];

        // For radius change dynamicaly
        if(radiusX > radiusXMax || radiusX < 0.1f)
            radiusStep *= -1.0f;
        radiusX = radiusX + radiusStep;

        if(radiusY > radiusYMax || radiusY < 0.1f)
            radiusStep *= -1.0f;
        radiusY = radiusY + radiusStep;
    }

    // Fill colors
    if(RANDOM == color){
        for(int i = 0; i < count; i++){
            arrayColor[i * 4] = Methods::getShortRandom();
            arrayColor[i * 4 + 1] = Methods::getShortRandom();
            arrayColor[i * 4 + 2] = Methods::getShortRandom();
            arrayColor[i * 4 + 3] = Methods::getShortRandom() + 0.1f;
        }
    }
}
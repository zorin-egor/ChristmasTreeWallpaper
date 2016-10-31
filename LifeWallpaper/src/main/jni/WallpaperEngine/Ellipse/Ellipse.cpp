#include "Ellipse.h"

void Ellipse::render() {
    //LOGI("Ellipse::render(); Cx: %f; Cy: %f; Cc: %d; Rx: %f; Ry: %f;", CENTER_X, CENTER_Y, count, radius[0], radius[1]);
    // Need draw this object?
    if(!isVisible)
        return;

    setValues();

    // Use render shader programm
    glUseProgram(programID);
    checkGLError("Ellipse - glUseProgram");

    // Choose you texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    checkGLError("Ellipse - glBindTexture");

    // Fill attributes and uniforms
    // Speed
    glVertexAttribPointer(speedAttr, 1, GL_FLOAT, GL_FALSE, 0, arrayPosition);
    checkGLError("Ellipse - glVertexAttribPointer - speedAttr");
    glEnableVertexAttribArray(speedAttr);
    checkGLError("Ellipse - glVertexAttribPointer - speedAttr - enabled");

    // Delta for color mix
    glVertexAttribPointer(deltaAttr, 1, GL_FLOAT, GL_FALSE, 0, arrayDelta);
    checkGLError("Ellipse - glVertexAttribPointer - deltaAttr");
    glEnableVertexAttribArray(deltaAttr);
    checkGLError("Ellipse - glVertexAttribPointer - deltaAttr - enabled");

    // Color start
    glVertexAttribPointer(colorStartAttr, 4, GL_FLOAT, GL_FALSE, 0, colorStartArray);
    checkGLError("Ellipse - glVertexAttribPointer - colorStartAttr");
    glEnableVertexAttribArray(colorStartAttr);
    checkGLError("Ellipse - glVertexAttribPointer - colorStartAttr - enabled");

    // Color end
    glVertexAttribPointer(colorEndAttr, 4, GL_FLOAT, GL_FALSE, 0, colorEndArray);
    checkGLError("Ellipse - glVertexAttribPointer - colorEndAttr");
    glEnableVertexAttribArray(colorEndAttr);
    checkGLError("Ellipse - glVertexAttribPointer - colorEndAttr - enabled");

    // Position
    glUniform2f(positionUniform, centerCoords[0], centerCoords[1]);
    checkGLError("Ellipse - glUniform2f - positionUniform");

    // Radius
    glUniform2f(radiusUniform, radius[0], radius[1]);
    checkGLError("Ellipse - glUniform2f - radiusUniform");

    // Size
    glUniform2f(sizeUniform, sizeUniformArray[0], sizeUniformArray[1]);
    checkGLError("Ellipse - glUniform2f - sizeUniform");

    // Total singleSpeed
    glUniform1f(totalDeltaSpeedUniform, totalDeltaSpeed);
    checkGLError("Ellipse - glUniform1f - totalDeltaSpeedUniform");

    // Draw poligon
    glDrawArrays(GL_POINTS, 0, count);
    checkGLError("Ellipse - glDrawArrays");

    // Off attributes
    glDisableVertexAttribArray(speedAttr);
    glDisableVertexAttribArray(deltaAttr);
    glDisableVertexAttribArray(colorStartAttr);
    glDisableVertexAttribArray(colorEndAttr);
}

void Ellipse::init(){
    //LOGI("Ellipse::init(); Cx: %f; Cy: %f; Cc: %d; Rx: %f; Ry: %f;", CENTER_X, CENTER_Y, count, radius[0], radius[1]);
    // Set frequency interval to 0
    frequencyInterval = 0;
    // For default reset transparancy
    isResetTransparancy = false;
    // Current speed
    totalDeltaSpeed = 5000.0f;
    // Delta rotate speed
    deltaSpeed = 0.01f;
    // For radius
    radius[0] = radiusX;
    radius[1] = radiusY;
    // For center of circle
    centerCoords[0] = centerX;
    centerCoords[1] = centerY;

    // 4 color * count
    colorStartArray = new GLfloat[count * 4];
    Methods::fillArray(colorStartArray, 0.0f, count * 4);

    // 4 color * count
    colorEndArray = new GLfloat[count * 4];
    Methods::fillArray(colorEndArray, 0.0f, count * 4);
    switch(colorType){
        case RED :
            Methods::fillArrayRGBA(colorStartArray, count, 1.0f, 0.0f, 0.0f, transparancy);
            Methods::fillArrayRGBA(colorEndArray, count, 1.0f, 0.0f, 0.0f, transparancy);
            break;

        case GREEN:
            Methods::fillArrayRGBA(colorStartArray, count, 0.0f, 1.0f, 0.0f, transparancy);
            Methods::fillArrayRGBA(colorEndArray, count, 0.0f, 1.0f, 0.0f, transparancy);
            break;

        case BLUE:
            Methods::fillArrayRGBA(colorStartArray, count, 0.0f, 0.0f, 1.0f, transparancy);
            Methods::fillArrayRGBA(colorEndArray, count, 0.0f, 0.0f, 1.0f, transparancy);
            break;

        case WHITE:
            Methods::fillArrayRGBA(colorStartArray, count, 1.0f, 1.0f, 1.0f, transparancy);
            Methods::fillArrayRGBA(colorEndArray, count, 1.0f, 1.0f, 1.0f, transparancy);
            break;
    }

    // Size mix from ... to
    sizeUniformArray[0] = pointSize;
    sizeUniformArray[1] = pointSize;
    if(RANDOM == colorType && NONE == frequency){
        sizeUniformArray[0] = (GLfloat)Methods::getStrictRandom((int)(pointSize / 2)) + 1.0f;
        sizeUniformArray[1] = (GLfloat)Methods::getStrictRandom((int)pointSize) + 5.0f;
    }

    // Initial position
    arrayPosition = new GLfloat[count];
    for(int i = 0; i < count; i++)
        if(!isMove)
            arrayPosition[i] = (GLfloat)Methods::getStrictRandom(10000);
        else
            arrayPosition[i] = (GLfloat)i;

    // Random delta for color
    arrayDelta = new GLfloat[count];
    for(int i = 0; i < count; i++)
        arrayDelta[i] = Methods::getShortRandom();
}

void Ellipse::setValues(){
    // Every point move around
    if(isMove){
        if(totalDeltaSpeed > 10000.0f || totalDeltaSpeed < 0.0f)
            deltaSpeed *= -1.0f;
        totalDeltaSpeed = totalDeltaSpeed + deltaSpeed;
    }

    // Change colors and transparancy random
    if(RANDOM == colorType){
        for(int i = 0; i < count; i++){
            // Color start
            colorStartArray[i * 4] = Methods::getShortRandom() * 0.5f;
            colorStartArray[i * 4 + 1] = Methods::getShortRandom() * 0.5f;
            colorStartArray[i * 4 + 2] = Methods::getShortRandom() * 0.5f;
            colorStartArray[i * 4 + 3] = Methods::getShortRandom() * 0.5f;

            // Color end
            colorEndArray[i * 4] = Methods::getShortRandom() + 0.5f;
            colorEndArray[i * 4 + 1] = Methods::getShortRandom() + 0.5f;
            colorEndArray[i * 4 + 2] = Methods::getShortRandom() + 0.5f;
            colorEndArray[i * 4 + 3] = Methods::getShortRandom() + 0.5f;
        }
    }

    // Change transperency
    if(NONE != frequency && RANDOM != colorType){
        switch(frequency){
            case LOW :
                if(frequencyInterval % 20 == 0) isResetTransparancy = true;
                break;
            case MIDDLE :
                if(frequencyInterval % 10 == 0) isResetTransparancy = true;
                break;
            case HIGH :
                if(frequencyInterval % 5 == 0) isResetTransparancy = true;
                break;
        }

        // Change transparancy and reset counter
        if(isResetTransparancy){
            frequencyInterval = 0;
            isResetTransparancy = false;

            for(int i = 0; i < count; i++){
                colorStartArray[i * 4 + 3] = Methods::getShortRandom() * transparancy * 0.5f;
                colorEndArray[i * 4 + 3] = Methods::getShortRandom() * transparancy * 0.8f;
            }
        }

        frequencyInterval++;
    }
}

void Ellipse::changeDirection(bool isLeftOrRight){
    if(isLeftOrRight)
        deltaSpeed = -fabsf(deltaSpeed);
    else
        deltaSpeed = fabsf(deltaSpeed);
}


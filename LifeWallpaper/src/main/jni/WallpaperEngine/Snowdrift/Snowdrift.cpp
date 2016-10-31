#include "Snowdrift.h"

void Snowdrift::init(){
    isVisible = true;
    outerCount = INIT_COUNT;
    GLfloat transparancy = INIT_TRANSPARANCY;
    GLfloat transparancyStep = transparancy / (GLfloat) WIDTH;
    GLuint dCount = (GLuint)outerCount / (WIDTH * 2);
    GLfloat dRadiusX = bottomRadiusX / DRADIUS_STEP;
    GLfloat dRadiusY = bottomRadiusY / DRADIUS_STEP;
    GLfloat dPointRadius = startPointRadius / (GLfloat)WIDTH * 0.95f;

    for(int i = 0; i < WIDTH; i++, outerCount -= dCount,
                                   bottomRadiusX += dRadiusX,
                                   bottomRadiusY += dRadiusY,
                                   transparancy -= transparancyStep,
                                   startPointRadius -= dPointRadius){

        //LOGI("Snowdrift::init(); COUNT: %d; DCOUNT: %d", outerCount, dCount);
        if(i > WIDTH * 0.7f){
            //LOGI("Snowdrift::init(); Change: %d;", dCount);
            dCount =  INIT_COUNT / WIDTH * 2;
        }

        ellipses.push_back(new Ellipse(outerCount,
                                       bottomRadiusX,
                                       bottomRadiusY,
                                       CENTER_X,
                                       CENTER_Y,
                                       startPointRadius,
                                       Ellipse::COLOR_TYPE::RANDOM,
                                       Ellipse::HIGH,
                                       transparancy,
                                       false,
                                       programID,
                                       textureID,
                                       positionAttr,
                                       speedAttr,
                                       radiusAttr,
                                       deltaAttr,
                                       colorStartAttr,
                                       colorEndAttr,
                                       sizeUniform,
                                       totalDeltaSpeedUniform));
    }
}

void Snowdrift::render(){
    if(isVisible)
        for(int i = 0; i < ellipses.size(); i++){
            ellipses[i]->render();
        }
}
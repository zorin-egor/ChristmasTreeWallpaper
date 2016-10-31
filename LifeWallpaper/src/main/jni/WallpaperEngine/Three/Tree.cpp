#include "Tree.h"

void Tree::init(){
    LOGI("BORDER: %f;", BORDER);
    isVisible = true;
    step = (2.0f - BORDER * 2.0f) / (GLfloat) HEIGHT;
    GLfloat centerY = BOTTOM_Y;
    GLuint countValue = COUNT;
    GLuint dCount = COUNT / HEIGHT;
    GLfloat dRadiusX = bottomRadiusX / (GLfloat) HEIGHT;
    GLfloat dRadiusY = bottomRadiusY / (GLfloat) HEIGHT * 0.95f;
    for(int i = 0; i < HEIGHT; i++, countValue -= dCount, bottomRadiusX -= dRadiusX, centerY += step, bottomRadiusY -= dRadiusY){
        ellipses.push_back(new Ellipse(countValue,
                                       bottomRadiusX,
                                       bottomRadiusY,
                                       BOTTOM_X,
                                       centerY,
                                       POINT_SIZE,
                                       Ellipse::COLOR_TYPE::RANDOM,
                                       Ellipse::HIGH,
                                       TRASPARANCY,
                                       true,
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

    topY = centerY;
}

void Tree::render(){
    //LOGI("Tree::render(); SIZE: %d", ellipses.sizePoint());
    if(isVisible)
        for(int i = 0; i < ellipses.size(); i++){
            ellipses[i]->render();
        }
}

GLfloat Tree::getBottomY(){
    return BOTTOM_Y;
}

GLfloat Tree::getTopY(){
    return topY;
}

void Tree::changeDirection(bool isLeftOrRight){
    for(int i = 0; i < ellipses.size(); i++){
        ellipses[i]->changeDirection(isLeftOrRight);
    }
}

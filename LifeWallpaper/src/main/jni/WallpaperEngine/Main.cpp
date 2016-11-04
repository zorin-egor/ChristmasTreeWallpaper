#include "Main.h"

Main::~Main(){
    LOGI("~Main();");
    //glUseProgram(0);
    //glDeleteProgram(programEllipse);
    //glDeleteProgram(programStar);
    //glDeleteProgram(programSnow);

    deleteObjects();
    delete pTextures;
}

bool Main::init(){
    // Ellipse
    programEllipse = MakeShaders::createProgram(MakeShaders::v_ellipse_shader, MakeShaders::f_ellipse_shader);
    if(programEllipse == 0)
        return false;

    threesAngle = glGetAttribLocation(programEllipse, "a_ArrayAngle");
    checkGLError("Main::init - pThree - a_ArraySpeed");

    threeDelta = glGetAttribLocation(programEllipse, "a_Delta");
    checkGLError("Main::init - pThree - a_Delta");

    threeColorStart = glGetAttribLocation(programEllipse, "a_ColorStart");
    checkGLError("Main::init - pThree - a_ColorStart");

    threeColorEnd = glGetAttribLocation(programEllipse, "a_ColorEnd");
    checkGLError("Main::init - pThree - a_ColorEnd");

    threePosition = glGetUniformLocation(programEllipse, "u_ArrayCoords");
    checkGLError("Main::init - pThree - u_ArrayCoords");

    threeRadius = glGetUniformLocation(programEllipse, "u_ArrayRadius");
    checkGLError("Main::init - pThree - u_ArrayRadius");

    threeSize = glGetUniformLocation(programEllipse, "u_Size");
    checkGLError("Main::init - pThree - u_Size");

    threeTotalDeltaSpeed = glGetUniformLocation(programEllipse, "u_TotalDeltaSpeed");
    checkGLError("Main::init - pThree - u_TotalDeltaSpeed");

    // Star
    programStar = MakeShaders::createProgram(MakeShaders::v_star_shader, MakeShaders::f_star_shader);
    if(programStar == 0)
        return false;

    starsAngle = glGetAttribLocation(programStar, "a_ArrayAngle");
    checkGLError("Main::init - stars - a_ArraySpeed");

    starColor = glGetAttribLocation(programStar, "a_ArrayColor");
    checkGLError("Main::init - stars - a_ArrayColor");

    starCenter = glGetUniformLocation(programStar, "u_Center");
    checkGLError("Main::init - stars - u_Center");

    starRadius = glGetUniformLocation(programStar, "u_Radius");
    checkGLError("Main::init - stars - u_Radius");

    starArgumentsX = glGetUniformLocation(programStar, "u_ArgumentsX");
    checkGLError("Main::init - stars - u_ArgumentsX");

    starArgumentsY = glGetUniformLocation(programStar, "u_ArgumentsY");
    checkGLError("Main::init - stars - u_ArgumentsY");

    starSize = glGetUniformLocation(programStar, "u_PointSize");
    checkGLError("Main::init - stars - u_PointSize");

    starTotalDeltaSpeed = glGetUniformLocation(programStar, "u_TotalDeltaSpeed");
    checkGLError("Main::init - stars - u_TotalDeltaSpeed");

    // Snow
    programSnow = MakeShaders::createProgram(MakeShaders::v_snow_shader, MakeShaders::f_snow_shader);
    if(programSnow == 0)
        return false;

    snowStartCoords = glGetAttribLocation(programSnow, "a_ArrayCoords");
    checkGLError("Main::init - snow - a_ArrayCoords");

    snowFallSpeed = glGetAttribLocation(programSnow, "a_ArraySpeed");
    checkGLError("Main::init - snow - a_ArraySpeed");

    snowSize = glGetAttribLocation(programSnow, "a_ArraySize");
    checkGLError("Main::init - snow - a_ArraySize");

    snowShift = glGetAttribLocation(programSnow, "a_ArrayShift");
    checkGLError("Main::init - snow - a_ArrayShift");

    snowColor = glGetAttribLocation(programSnow, "a_ArrayColor");
    checkGLError("Main::init - snow - a_ArrayColor");

    snowAngle = glGetUniformLocation(programSnow, "u_angle");
    checkGLError("Main::init - snow - u_angle");

    snowFreq = glGetAttribLocation(programSnow, "a_ArrayFreq");
    checkGLError("Main::init - snow - a_ArrayFreq");

    snowAmplitude = glGetAttribLocation(programSnow, "a_ArrayAmplitude");
    checkGLError("Main::init - snow - a_ArrayAmplitude");

    // Clear compiliers
    glReleaseShaderCompiler();

    //On alfa-blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    checkGLError("Main::init - glBlendFunc");
    glEnable(GL_BLEND);
    checkGLError("Main::init - glEnable");

    // Get slots of img
    pTextures = new ManageTexture(env, pngManager, assetManager);

    return true;
}

void Main::onChange(int width, int height, bool isQuality){
    this->width = width;
    this->height = height;
    this->isQuality = isQuality;
    coefficient = (float) width / (float) height;

    // Recreate objects with new data
    deleteObjects();
    createObjects();

    // Set viewport
    glViewport(0, 0, width, height);
    checkGLError("Main::onChange - glViewport");
}

void Main::createObjects(){
    // Snow back
    GLuint snowBackCount = 40;
    if(!isQuality)
        snowBackCount = 30;

    pSnowBack = new Snow(snowBackCount,
                         5,
                         Snow::BLUE,
                         WIND_POWER,
                         ANGLE,
                         1.4f,
                         programSnow,
                         pTextures->getTexturesPackIDs(ManageTexture::SNOW),
                         snowStartCoords,
                         snowFallSpeed ,
                         snowSize,
                         snowShift,
                         snowColor,
                         snowAngle,
                         snowFreq,
                         snowAmplitude);
    object.push_back(pSnowBack);

    // For proportions
    GLfloat bottomX = width < height? 0.5f : 0.5 / coefficient;
    GLfloat bottomY = width < height? 0.08f : 0.12f;

    // Tree
    GLuint treeSize = 50;
    if(!isQuality)
        treeSize = 35;

    GLfloat border = height < width? 0.5f : 0.6f;
    pThree = new Tree(treeSize,
                      bottomX,
                      bottomY,
                      0.0f,
                      10.0f,
                      border,
                      programEllipse,
                      pTextures->getTexturesPackIDs(ManageTexture::TREE),
                      threePosition,
                      threesAngle,
                      threeRadius,
                      threeDelta,
                      threeColorStart,
                      threeColorEnd,
                      threeSize,
                      threeTotalDeltaSpeed);

    // Snowdrift
    GLuint snowDriftSize = 30;
    if(!isQuality)
        snowDriftSize = 10;

    pSnowdrift = new Snowdrift( snowDriftSize,
                                bottomX,
                                bottomY,
                                15.0f,
                                0.0f,
                                pThree->getBottomY(),
                                programEllipse,
                                pTextures->getTexturesPackIDs(ManageTexture::TREE),
                                threePosition,
                                threesAngle,
                                threeRadius,
                                threeDelta,
                                threeColorStart,
                                threeColorEnd,
                                threeSize,
                                threeTotalDeltaSpeed);

    object.push_back(pSnowdrift);
    object.push_back(pThree);

    // Star
    GLuint starCount = 300;
    if(!isQuality)
        starCount = 200;

    object.push_back(new Star( Star::HYPOCYCLOID,
                               Star::RED,
                               starCount,
                               0.0f,
                               pThree->getTopY() + 0.1f,
                               0.05f / coefficient,
                               0.05f,
                               programStar,
                               pTextures->getTexturesPackIDs(ManageTexture::TREE),
                               starsAngle,
                               starColor,
                               starCenter,
                               starRadius,
                               starArgumentsX,
                               starArgumentsY,
                               starSize,
                               starTotalDeltaSpeed));

    // Snow front
    GLuint snowFrontCount = 100;
    if(!isQuality)
        snowFrontCount = 50;

    pSnowFront = new Snow(snowFrontCount,
                          20,
                          Snow::BLUE,
                          WIND_POWER,
                          ANGLE,
                          1.95f,
                          programSnow,
                          pTextures->getTexturesPackIDs(ManageTexture::SNOW),
                          snowStartCoords,
                          snowFallSpeed ,
                          snowSize,
                          snowShift,
                          snowColor,
                          snowAngle,
                          snowFreq,
                          snowAmplitude);
    object.push_back(pSnowFront);
}

void Main::deleteObjects(){
    // Delete all links
    for(int i = 0; i < object.size(); i++){
        delete object[i];
    }

    // Clear links
    object.clear();
}

void Main::step(){
    // Clear screen
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    checkGLError("Main::step - glClearColor");
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGLError("Main::step - glClear");

    // Draw all objects
    for(int i = 0; i < object.size(); i++){
        object[i]->render();
    }
}

void Main::action(bool isLeftOrRight){
    pThree->changeDirection(isLeftOrRight);
    if(isLeftOrRight){
        if(currentAngle < STRICT_LEFT){
            // Change angle
            pSnowFront->setDegrees(currentAngle += ANGLE_STEP);
            pSnowBack->setDegrees(currentAngle);
            // Change power
            if(currentAngle > ANGLE + STRICT_INTERVAL && currentAngle < ANGLE + STRICT_INTERVAL * 2.0f){
                pSnowFront->setPower(Snow::WIND_POWER::MIDDLE);
                pSnowBack->setPower(Snow::WIND_POWER::MIDDLE);
            } else if(currentAngle > ANGLE + STRICT_INTERVAL * 2.0f){
                pSnowFront->setPower(Snow::WIND_POWER::FAST);
                pSnowBack->setPower(Snow::WIND_POWER::FAST);
            }
        }
    } else {
        if(currentAngle > STRICT_RIGHT){
            pSnowFront->setDegrees(currentAngle -= ANGLE_STEP);
            pSnowBack->setDegrees(currentAngle);
            // Change power
            if(currentAngle < ANGLE - STRICT_INTERVAL && currentAngle > ANGLE - STRICT_INTERVAL * 2.0f){
                pSnowFront->setPower(Snow::WIND_POWER::MIDDLE);
                pSnowBack->setPower(Snow::WIND_POWER::MIDDLE);
            } else if(currentAngle < ANGLE - STRICT_INTERVAL * 2.0f){
                pSnowFront->setPower(Snow::WIND_POWER::FAST);
                pSnowBack->setPower(Snow::WIND_POWER::FAST);
            }

        }
    }

    // Default fo 90
    if(currentAngle < ANGLE + 10.0f && currentAngle > ANGLE - 10.0f){
        pSnowFront->setPower(Snow::WIND_POWER::SLOW);
        pSnowBack->setPower(Snow::WIND_POWER::SLOW);
    }
}
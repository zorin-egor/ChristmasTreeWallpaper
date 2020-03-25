#include "Wallpaper.h"

const GLfloat Wallpaper::ANGLE = -90.0f;
const GLfloat Wallpaper::STRICT_LEFT = -65.0f;
const GLfloat Wallpaper::STRICT_RIGHT = -125.f;
const GLfloat Wallpaper::STRICT_INTERVAL = (fabsf(STRICT_RIGHT) - fabsf(STRICT_LEFT)) / 5.0f;
const GLfloat Wallpaper::ANGLE_STEP = 5.0f;


Wallpaper::Wallpaper(JNIEnv * env, jobject assetManager, jobject pngManager) {
    LOGI("Wallpaper::Wallpaper();");
    WIND_POWER = Snow::WIND_POWER::SLOW;
    m_fCurrentAngle = ANGLE;
    init(env, assetManager, pngManager);
}

Wallpaper::~Wallpaper() {
    LOGI("Wallpaper::Wallpaper();");
    //glUseProgram(0);
    //glDeleteProgram(m_nProgramEllipse);
    //glDeleteProgram(m_nProgramStar);
    //glDeleteProgram(m_nProgramSnow);

    deleteTextureObjects();
    delete m_pTextures;
}

bool Wallpaper::init(JNIEnv* env, jobject assetManager, jobject pngManager) {
    // Create texture manager
    m_pTextures = new TexturesManager(env, pngManager, assetManager);

    // Ellipse
    m_nProgramEllipse = MakeShaders::createProgram(MakeShaders::V_ELLIPSE_SHADER, MakeShaders::F_ELLIPSE_SHADER);
    if (m_nProgramEllipse == 0) {
        return false;
    }

    m_nThreesAngle = glGetAttribLocation(m_nProgramEllipse, "a_ArrayAngle");
    checkGLError("Wallpaper::init - three - a_ArrayAngle");

    m_nThreeDelta = glGetAttribLocation(m_nProgramEllipse, "a_Delta");
    checkGLError("Wallpaper::init - three - a_Delta");

    m_nThreeColorStart = glGetAttribLocation(m_nProgramEllipse, "a_ColorStart");
    checkGLError("Wallpaper::init - three - a_ColorStart");

    m_nThreeColorEnd = glGetAttribLocation(m_nProgramEllipse, "a_ColorEnd");
    checkGLError("Wallpaper::init - three - a_ColorEnd");

    m_nThreePosition = glGetUniformLocation(m_nProgramEllipse, "u_ArrayCoords");
    checkGLError("Wallpaper::init - three - u_ArrayCoords");

    m_nThreeRadius = glGetUniformLocation(m_nProgramEllipse, "u_ArrayRadius");
    checkGLError("Wallpaper::init - three - u_ArrayRadius");

    m_nThreeSize = glGetUniformLocation(m_nProgramEllipse, "u_Size");
    checkGLError("Wallpaper::init - three - u_Size");

    m_nThreeTotalDeltaSpeed = glGetUniformLocation(m_nProgramEllipse, "u_TotalDeltaSpeed");
    checkGLError("Wallpaper::init - three - u_TotalDeltaSpeed");

    // Star
    m_nProgramStar = MakeShaders::createProgram(MakeShaders::V_STAR_SHADER, MakeShaders::F_STAR_SHADER);
    if (m_nProgramStar == 0) {
        return false;
    }

    m_nStarsAngle = glGetAttribLocation(m_nProgramStar, "a_ArrayAngle");
    checkGLError("Wallpaper::init - stars - a_ArrayAngle");

    m_nStarColor = glGetAttribLocation(m_nProgramStar, "a_ArrayColor");
    checkGLError("Wallpaper::init - stars - a_ArrayColor");

    m_nStarCenter = glGetUniformLocation(m_nProgramStar, "u_Center");
    checkGLError("Wallpaper::init - stars - u_Center");

    m_nStarRadius = glGetUniformLocation(m_nProgramStar, "u_Radius");
    checkGLError("Wallpaper::init - stars - u_Radius");

    m_nStarArgumentsX = glGetUniformLocation(m_nProgramStar, "u_ArgumentsX");
    checkGLError("Wallpaper::init - stars - u_ArgumentsX");

    m_nStarArgumentsY = glGetUniformLocation(m_nProgramStar, "u_ArgumentsY");
    checkGLError("Wallpaper::init - stars - u_ArgumentsY");

    m_nStarSize = glGetUniformLocation(m_nProgramStar, "u_PointSize");
    checkGLError("Wallpaper::init - stars - u_PointSize");

    m_nStarTotalDeltaSpeed = glGetUniformLocation(m_nProgramStar, "u_TotalDeltaSpeed");
    checkGLError("Wallpaper::init - stars - u_TotalDeltaSpeed");

    // Snow
    m_nProgramSnow = MakeShaders::createProgram(MakeShaders::V_SNOW_SHADER, MakeShaders::F_SNOW_SHADER);
    if (m_nProgramSnow == 0) {
        return false;
    }

    m_nSnowStartCoords = glGetAttribLocation(m_nProgramSnow, "a_ArrayCoords");
    checkGLError("Wallpaper::init - snow - a_ArrayCoords");

    m_nSnowFallSpeed = glGetAttribLocation(m_nProgramSnow, "a_ArraySpeed");
    checkGLError("Wallpaper::init - snow - a_ArraySpeed");

    m_nSnowSize = glGetAttribLocation(m_nProgramSnow, "a_ArraySize");
    checkGLError("Wallpaper::init - snow - a_ArraySize");

    m_nSnowShift = glGetAttribLocation(m_nProgramSnow, "a_ArrayShift");
    checkGLError("Wallpaper::init - snow - a_ArrayShift");

    m_nSnowColor = glGetAttribLocation(m_nProgramSnow, "a_ArrayColor");
    checkGLError("Wallpaper::init - snow - a_ArrayColor");

    m_nSnowAngle = glGetUniformLocation(m_nProgramSnow, "u_angle");
    checkGLError("Wallpaper::init - snow - u_angle");

    m_nSnowFreq = glGetAttribLocation(m_nProgramSnow, "a_ArrayFreq");
    checkGLError("Wallpaper::init - snow - a_ArrayFreq");

    m_nSnowAmplitude = glGetAttribLocation(m_nProgramSnow, "a_ArrayAmplitude");
    checkGLError("Wallpaper::init - snow - a_ArrayAmplitude");

    // Clear compilers
    glReleaseShaderCompiler();

    //On alpha-blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    checkGLError("Wallpaper::init - glBlendFunc");
    glEnable(GL_BLEND);
    checkGLError("Wallpaper::init - glEnable");

    return true;
}

void Wallpaper::screen(int width, int height) {
    glViewport(0, 0, width, height);
    checkGLError("Wallpaper::screen - glViewport");

    auto isResize = m_nWidth != width || m_nHeight != height;

    m_nWidth = width;
    m_nHeight = height;
    m_fCoefficient = (float) width / (float) height;

    // Recreate objects with new data
    if (isResize) {
        deleteTextureObjects();
        createTextureObjects();
    }
}

void Wallpaper::createTextureObjects() {
    // Snow back
    GLuint snowBackCount = 40;
    if (!m_bIsQuality) {
        snowBackCount = 30;
    }

    m_pSnowBack = new Snow(snowBackCount,
                           5,
                           Snow::BLUE,
                           WIND_POWER,
                           ANGLE,
                           1.4f,
                           m_nProgramSnow,
                           m_pTextures->getTextureId(TexturesManager::SNOW),
                           m_nSnowStartCoords,
                           m_nSnowFallSpeed ,
                           m_nSnowSize,
                           m_nSnowShift,
                           m_nSnowColor,
                           m_nSnowAngle,
                           m_nSnowFreq,
                           m_nSnowAmplitude);
    m_oObjects.push_back(m_pSnowBack);

    // For proportions
    GLfloat bottomX = m_nWidth < m_nHeight ? 0.5f : 0.5 / m_fCoefficient;
    GLfloat bottomY = m_nWidth < m_nHeight ? 0.08f : 0.12f;

    // Tree
    GLuint treeSize = 50;
    if (!m_bIsQuality) {
        treeSize = 35;
    }

    GLfloat border = m_nHeight < m_nWidth ? 0.5f : 0.6f;
    m_pThree = new Tree(treeSize,
                        bottomX,
                        bottomY,
                        0.0f,
                        10.0f,
                        border,
                        m_nProgramEllipse,
                        m_pTextures->getTextureId(TexturesManager::TREE),
                        m_nThreePosition,
                        m_nThreesAngle,
                        m_nThreeRadius,
                        m_nThreeDelta,
                        m_nThreeColorStart,
                        m_nThreeColorEnd,
                        m_nThreeSize,
                        m_nThreeTotalDeltaSpeed);

    // Snowdrift
    GLuint snowDriftSize = 30;
    if (!m_bIsQuality) {
        snowDriftSize = 10;
    }

    m_pSnowdrift = new Snowdrift(snowDriftSize,
                                 bottomX,
                                 bottomY,
                                 15.0f,
                                 0.0f,
                                 m_pThree->getBottomY(),
                                 m_nProgramEllipse,
                                 m_pTextures->getTextureId(TexturesManager::TREE),
                                 m_nThreePosition,
                                 m_nThreesAngle,
                                 m_nThreeRadius,
                                 m_nThreeDelta,
                                 m_nThreeColorStart,
                                 m_nThreeColorEnd,
                                 m_nThreeSize,
                                 m_nThreeTotalDeltaSpeed);

    m_oObjects.push_back(m_pSnowdrift);
    m_oObjects.push_back(m_pThree);

    // Star
    GLuint starCount = 300;
    if (!m_bIsQuality) {
        starCount = 200;
    }

    m_oObjects.push_back(new Star(Star::HYPOCYCLOID,
                                  Star::RED,
                                  starCount,
                                  0.0f,
                                  m_pThree->getTopY() + 0.1f,
                                  0.05f / m_fCoefficient,
                                  0.05f,
                                  m_nProgramStar,
                                  m_pTextures->getTextureId(TexturesManager::TREE),
                                  m_nStarsAngle,
                                  m_nStarColor,
                                  m_nStarCenter,
                                  m_nStarRadius,
                                  m_nStarArgumentsX,
                                  m_nStarArgumentsY,
                                  m_nStarSize,
                                  m_nStarTotalDeltaSpeed));

    // Snow front
    GLuint snowFrontCount = 100;
    if (!m_bIsQuality) {
        snowFrontCount = 50;
    }

    m_pSnowFront = new Snow(snowFrontCount,
                            20,
                            Snow::BLUE,
                            WIND_POWER,
                            ANGLE,
                            1.95f,
                            m_nProgramSnow,
                            m_pTextures->getTextureId(TexturesManager::SNOW),
                            m_nSnowStartCoords,
                            m_nSnowFallSpeed ,
                            m_nSnowSize,
                            m_nSnowShift,
                            m_nSnowColor,
                            m_nSnowAngle,
                            m_nSnowFreq,
                            m_nSnowAmplitude);
    m_oObjects.push_back(m_pSnowFront);
}

void Wallpaper::deleteTextureObjects() {
    // Delete all links
    std::for_each(m_oObjects.begin(), m_oObjects.end(), [](std::vector<Render*>::value_type &item) {
        delete item;
    });

    // Clear links
    m_oObjects.clear();
}

void Wallpaper::step() {
    m_oDrawMutex.lock();

    // Clear screen
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    checkGLError("Wallpaper::step - glClearColor");
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGLError("Wallpaper::step - glClear");

    // Draw all objects
    std::for_each(m_oObjects.begin(), m_oObjects.end(), [](std::vector<Render*>::value_type &item) {
        item->render();
    });

    m_oDrawMutex.unlock();
}

void Wallpaper::action(bool isLeftOrRight) {
    m_pThree->changeDirection(isLeftOrRight);

    if (isLeftOrRight) {
        if (m_fCurrentAngle < STRICT_LEFT) {
            // Change angle
            m_pSnowFront->setDegrees(m_fCurrentAngle += ANGLE_STEP);
            m_pSnowBack->setDegrees(m_fCurrentAngle);

            // Change power
            if (m_fCurrentAngle > ANGLE + STRICT_INTERVAL && m_fCurrentAngle < ANGLE + STRICT_INTERVAL * 2.0f) {
                m_pSnowFront->setPower(Snow::WIND_POWER::MIDDLE);
                m_pSnowBack->setPower(Snow::WIND_POWER::MIDDLE);
            } else if (m_fCurrentAngle > ANGLE + STRICT_INTERVAL * 2.0f) {
                m_pSnowFront->setPower(Snow::WIND_POWER::FAST);
                m_pSnowBack->setPower(Snow::WIND_POWER::FAST);
            }
        }
    } else {
        if (m_fCurrentAngle > STRICT_RIGHT) {
            m_pSnowFront->setDegrees(m_fCurrentAngle -= ANGLE_STEP);
            m_pSnowBack->setDegrees(m_fCurrentAngle);

            // Change power
            if (m_fCurrentAngle < ANGLE - STRICT_INTERVAL && m_fCurrentAngle > ANGLE - STRICT_INTERVAL * 2.0f) {
                m_pSnowFront->setPower(Snow::WIND_POWER::MIDDLE);
                m_pSnowBack->setPower(Snow::WIND_POWER::MIDDLE);
            } else if (m_fCurrentAngle < ANGLE - STRICT_INTERVAL * 2.0f) {
                m_pSnowFront->setPower(Snow::WIND_POWER::FAST);
                m_pSnowBack->setPower(Snow::WIND_POWER::FAST);
            }

        }
    }

    // Default fo 90
    if (m_fCurrentAngle < ANGLE + 10.0f && m_fCurrentAngle > ANGLE - 10.0f) {
        m_pSnowFront->setPower(Snow::WIND_POWER::SLOW);
        m_pSnowBack->setPower(Snow::WIND_POWER::SLOW);
    }
}

void Wallpaper::quality(bool isHighQuality) {
    if (m_bIsQuality == isHighQuality) {
        return;
    }

    m_oDrawMutex.lock();
    m_bIsQuality = isHighQuality;
    deleteTextureObjects();
    createTextureObjects();
    m_oDrawMutex.unlock();
}
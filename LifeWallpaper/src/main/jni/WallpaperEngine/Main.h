#ifndef LIFEWALLPAPERTREE_MAIN_H
#define LIFEWALLPAPERTREE_MAIN_H

#include <WallpaperEngine/Shaders/MakeShaders.h>
#include <WallpaperEngine/Textures/ManageTexture.h>
#include <WallpaperEngine/Ellipse/Ellipse.h>
#include <WallpaperEngine/Three/Tree.h>
#include <WallpaperEngine/Star/Star.h>
#include <WallpaperEngine/Snow/Snow.h>
#include <WallpaperEngine/Snowdrift/Snowdrift.h>
#include <WallpaperEngine/Common/Intersect.h>
#include <vector>
#include <LogGL.h>

class Main {

    public:
        Main(   JNIEnv * _env, jobject _assetManager, jobject _pngManager) :
                env(_env),
                assetManager(_assetManager),
                pngManager(_pngManager),
                ANGLE(-90.0f),
                WIND_POWER(Snow::WIND_POWER::SLOW),
                STRICT_LEFT(-65.0f),
                STRICT_RIGHT(-125.f),
                STRICT_INTERVAL((fabsf(STRICT_RIGHT) - fabsf(STRICT_LEFT)) / 5.0f),
                ANGLE_STEP(5.0f),
                currentAngle(ANGLE)
        {
                LOGI("Main();");
                init();
        }

        ~Main();
        void onChange(int width, int height, bool isQuality);
        void step();
        void action(bool isLeftOrRight);

    private:
        bool init();
        void createObjects();
        void deleteObjects();

        // Java references
        JNIEnv * env;
        jobject pngManager;
        jobject assetManager;

        // Screen
        int width;
        int height;
        bool isQuality;
        float coefficient;
        // Initial values
        const GLfloat ANGLE;
        const Snow::WIND_POWER WIND_POWER;

        // Previous values
        const GLfloat STRICT_LEFT;
        const GLfloat STRICT_RIGHT;
        const GLfloat STRICT_INTERVAL;
        const GLfloat ANGLE_STEP;
        GLfloat currentAngle;

        // For get the texture
        ManageTexture * pTextures;

        // Programs
        GLuint programEllipse;
        GLuint programStar;
        GLuint programSnow;

        // Sprites
        // Tree
        GLint threePosition;
        GLint threesAngle;
        GLint threeRadius;
        GLint threeTotalDeltaSpeed;
        GLint threeDelta;
        GLint threeSize;
        GLint threeColorStart;
        GLint threeColorEnd;

        // Star
        GLint starsAngle;
        GLint starColor;
        GLint starCenter;
        GLint starRadius;
        GLint starArgumentsX;
        GLint starArgumentsY;
        GLint starSize;
        GLint starTotalDeltaSpeed;

        // Snow
        GLint snowStartCoords;
        GLint snowFallSpeed ;
        GLint snowSize;
        GLint snowShift;
        GLint snowColor;
        GLint snowAngle;
        GLint snowFreq;
        GLint snowAmplitude;

        // For objects with save order
        std::vector<Render *> object;

        // Snow objects for change angle
        Snowdrift * pSnowdrift;
        Snow * pSnowBack;
        Snow * pSnowFront;
        Tree * pThree;
};

#endif

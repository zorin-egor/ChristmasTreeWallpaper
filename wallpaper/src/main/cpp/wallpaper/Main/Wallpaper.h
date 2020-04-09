#ifndef WALLPAPER_H
#define WALLPAPER_H

#include <vector>
#include <mutex>

#include "../AbstractClasses/Render.h"
#include "../Shaders/MakeShaders.h"
#include "Textures/TexturesManager.h"
#include "../Ellipse/Ellipse.h"
#include "../Three/Tree.h"
#include "../Star/Star.h"
#include "../Snow/Snow.h"
#include "../Snowdrift/Snowdrift.h"
#include "../Common/Intersect.h"
#include "../Common/LogGL.h"

/*
 * TODO Refactoring jni
 * TODO Refactoring opengl
 * TODO Refactoring object structure
 * */
class Wallpaper {

        private:

            // Initial values
            static const GLfloat ANGLE;

            // Previous values
            static const GLfloat STRICT_LEFT;
            static const GLfloat STRICT_RIGHT;
            static const GLfloat STRICT_INTERVAL;
            static const GLfloat ANGLE_STEP;


        private:

            Snow::WIND_POWER WIND_POWER;

            // TODO temporary solution
            std::mutex m_oDrawMutex;

            // Screen
            int m_nWidth;
            int m_nHeight;
            bool m_bIsQuality;
            float m_fCoefficient;
            GLfloat m_fCurrentAngle;

            // For get the texture
            TexturesManager * m_pTextures;

            // Programs
            GLuint m_nProgramEllipse;
            GLuint m_nProgramStar;
            GLuint m_nProgramSnow;

            // Sprites
            // Tree
            GLint m_nThreePosition;
            GLint m_nThreesAngle;
            GLint m_nThreeRadius;
            GLint m_nThreeTotalDeltaSpeed;
            GLint m_nThreeDelta;
            GLint m_nThreeSize;
            GLint m_nThreeColorStart;
            GLint m_nThreeColorEnd;

            // Star
            GLint m_nStarsAngle;
            GLint m_nStarColor;
            GLint m_nStarCenter;
            GLint m_nStarRadius;
            GLint m_nStarArgumentsX;
            GLint m_nStarArgumentsY;
            GLint m_nStarSize;
            GLint m_nStarTotalDeltaSpeed;

            // Snow
            GLint m_nSnowStartCoords;
            GLint m_nSnowFallSpeed ;
            GLint m_nSnowSize;
            GLint m_nSnowShift;
            GLint m_nSnowColor;
            GLint m_nSnowAngle;
            GLint m_nSnowFreq;
            GLint m_nSnowAmplitude;

            // For objects with save order
            std::vector<Render*> m_oObjects;

            // Snow objects for change angle
            Snowdrift * m_pSnowdrift;
            Snow * m_pSnowBack;
            Snow * m_pSnowFront;
            Tree * m_pThree;


    public:

        Wallpaper(JNIEnv * env, jobject assetManager, jobject bitmapManager);

        ~Wallpaper();


    public:

        void screen(int width, int height);

        void step();

        void action(bool isLeftOrRight);

        void quality(bool isHighQuality);


    private:

        bool init(JNIEnv* env, jobject assetManager, jobject bitmapManager);

        void createTextureObjects();

        void deleteTextureObjects();

};

#endif

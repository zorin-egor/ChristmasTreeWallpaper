#ifndef MANAGER_TEXTURE_H
#define MANAGER_TEXTURE_H

#include <string>
#include <map>
#include <GLES2/gl2.h>
#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include "../Common/LogGL.h"

struct Texture {

    uint textureId;
    uint width;
    uint height;
    u_char * pixels;

    Texture() {
        textureId = 0;
        width = 0;
        height = 0;
        pixels = nullptr;
    }

    Texture(uint id, uint w, uint h, u_char * p) {
        textureId = id;
        pixels = p;
        width = w;
        height = h;
    }

    ~Texture() {
        LOGI("~Texture()");
        glDeleteTextures(1, &textureId);
        delete [] pixels;
        pixels = nullptr;
    }
};


class TexturesManager {

    public:

        static const enum TEXTURE_TYPE  {
            SIZE = 2,
            SNOW = 0,
            TREE = 1
        };

    private:

        AAssetManager * m_pAssetManager;

        jmethodID m_pOpenId;
        jmethodID m_pCloseId;
        jmethodID m_pGetWidthId;
        jmethodID m_pGetHeightId;
        jmethodID m_pGetPixelsId;

        std::map<TEXTURE_TYPE, Texture*> m_oTextures;


    public:

        TexturesManager(JNIEnv* env, jobject pngManager, jobject assetsManager);

        ~TexturesManager();


    public:

        GLint getTextureId(TexturesManager::TEXTURE_TYPE texture) {
            return m_oTextures.count(texture) > 0? m_oTextures[texture]->textureId : -1;
        }


    private:

        void init(JNIEnv * env, jobject pngManager, jobject assetManager);

        u_char * argb2rgba(unsigned int * pixels, int w, int h);

        Texture * loadTexture(JNIEnv * env, jobject pngManager, const char * filename);

        void loadTextures(JNIEnv * env, jobject pngManager);

        GLuint createTexture(Texture * texture);

        void createTextures();
};

#endif //GAME_LOADTEXTURES_H

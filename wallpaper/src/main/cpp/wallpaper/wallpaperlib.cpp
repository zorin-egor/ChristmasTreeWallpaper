#include <jni.h>
#include <Main/Wallpaper.h>
#include <Common/LogGL.h>

#define JNI_METHOD(RTYPE, NAME) JNIEXPORT RTYPE JNICALL Java_ru_testsimpleapps_lifewallpapertree_WallpaperLib_##NAME

std::map<long, Wallpaper*> oWallpapers;

extern "C" {

    JNI_METHOD(void, init)(JNIEnv * env, jclass type, jint id, jobject assetManager, jobject bitmapManager) {
        LOGI("JNI::INIT(%i)", id);
        if (oWallpapers.count(id) <= 0) {
            oWallpapers[id] = new Wallpaper(env, assetManager, bitmapManager);
        }
    }

    JNI_METHOD(void, destroy)(JNIEnv *env, jclass type, jint id) {
        LOGI("JNI::DESTROY(%i)", id);
        if (oWallpapers.count(id) > 0) {
            delete oWallpapers[id];
            oWallpapers.erase(id);
        }
    }

    JNI_METHOD(void, screen)(JNIEnv * env, jclass type, jint id, jint width, jint height) {
        LOGI("JNI::SCREEN(%i, %i, %i)", id, height, width);
        if (oWallpapers.count(id) > 0) {
            oWallpapers[id]->screen(width, height);
        }
    }

    JNI_METHOD(void, step)(JNIEnv * env, jclass type, jint id) {
        if (oWallpapers.count(id) > 0) {
            oWallpapers[id]->step();
        }
    }

    JNI_METHOD(void, action)(JNIEnv *env, jclass type, jint id, jboolean isLeftOrRight) {
        LOGI("JNI::ACTION(%i, %s)", id, isLeftOrRight? "true" : "false");
        if (oWallpapers.count(id) > 0) {
            oWallpapers[id]->action(isLeftOrRight);
        }
    }

    JNI_METHOD(void, quality)(JNIEnv * env, jclass type, jboolean isHighQuality) {
        std::for_each(oWallpapers.begin(), oWallpapers.end(), [&](std::map<long, Wallpaper*>::value_type &item) {
            item.second->quality(isHighQuality);
        });
    }

}
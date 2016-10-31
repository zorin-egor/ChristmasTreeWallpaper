#include <jni.h>
#include <queue>
#include <WallpaperEngine/Main.h>
#include <LogGL.h>

Main * wallpaper = NULL;
std::queue<Main *> wallpapersObjects;

extern "C" {

JNIEXPORT void JNICALL Java_ru_testsimpleapps_lifewallpapertree_WallpaperLib_init(JNIEnv * env, jobject obj, jobject assetManager, jobject pngManager, jint width, jint height, jboolean isQuality){
        LOGI("INIT: H: %d; W: %d; HQ: %d;", height, width, isQuality);
        wallpaper = new Main(env, assetManager, pngManager, width, height, isQuality);
        wallpapersObjects.push(wallpaper);
    }

    JNIEXPORT void JNICALL Java_ru_testsimpleapps_lifewallpapertree_WallpaperLib_step(JNIEnv * env, jobject obj){
        if(wallpaper != NULL)
            wallpaper->step();
    }

    JNIEXPORT void JNICALL Java_ru_testsimpleapps_lifewallpapertree_WallpaperLib_action(JNIEnv *env, jclass type, jboolean isLeftOrRight) {
        if(wallpaper != NULL)
            wallpaper->action(isLeftOrRight);
    }

    JNIEXPORT void JNICALL Java_ru_testsimpleapps_lifewallpapertree_WallpaperLib_destroyPrevious(JNIEnv * env, jobject obj){
        LOGI("DESTROY_PREVIOUS; SIZE: %d;", wallpapersObjects.size());
        if(wallpapersObjects.size() > 1){
            delete wallpapersObjects.front();
            wallpapersObjects.pop();
        }
    }

    JNIEXPORT void JNICALL Java_ru_testsimpleapps_lifewallpapertree_WallpaperLib_exit(JNIEnv *env, jclass type) {
        LOGI("EXIT; SIZE: %d;", wallpapersObjects.size());
        while(!wallpapersObjects.empty()) {
            delete wallpapersObjects.front();
            wallpapersObjects.pop();
        }
    }
}
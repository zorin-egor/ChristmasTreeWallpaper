#include <jni.h>
#include <queue>
#include <WallpaperEngine/Main.h>
#include <LogGL.h>

Main * wallpaper = NULL;
std::queue<Main *> wallpapersObjects;

extern "C" {

    JNIEXPORT void JNICALL Java_ru_testsimpleapps_lifewallpapertree_WallpaperLib_init(JNIEnv * env, jobject obj, jobject assetManager, jobject pngManager){
        LOGI("JNI::INIT;");
        wallpaper = new Main(env, assetManager, pngManager);
        wallpapersObjects.push(wallpaper);
    }

    JNIEXPORT void JNICALL Java_ru_testsimpleapps_lifewallpapertree_WallpaperLib_onChange(JNIEnv * env, jobject obj, jint width, jint height, jboolean isQuality){
        LOGI("JNI::ONCHANGE: H: %d; W: %d; HQ: %d;", height, width, isQuality);
        if(wallpaper != NULL)
            wallpaper->onChange(width, height, isQuality);
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
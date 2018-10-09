#include <jni.h>
#include <string>
#include <android/log.h>
#include <android/native_window_jni.h>
#include <EGL/egl.h>
#define  LOGE(...) __android_log_print(ANDROID_LOG_ERROR,"test",__VA_ARGS__)

extern "C" JNIEXPORT jstring

JNICALL
Java_yuvplayer_yuvplayer_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_yuvplayer_yuvplayer_YUVPlayer_Open(JNIEnv *env, jobject instance, jstring url_,
                                        jobject surface) {
    const char *url = env->GetStringUTFChars(url_, 0);

    LOGE("open url is %s",url);
    //获取原始窗口
    ANativeWindow *nwin = ANativeWindow_fromSurface(env,surface);

    //------------------------
    //EGL
    //1 display 显示
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display == EGL_NO_DISPLAY){
        LOGE("get display failed!");
        return;
    }
    //初始化 后面两个参数是版本号
   if (EGL_TRUE != eglInitialize(display,0,0)){
       LOGE("eglInitialize failed!");
       return;
   }

    //surface （关联原始窗口）
    //surface 配置
    //输出配置
    EGLConfig config;
    EGLint  configNum;
    //输入配置
    EGLint  configSpec[] = {
            EGL_RED_SIZE,  8,
            EGL_GREEN_SIZE,8,
            EGL_BLUE_SIZE, 8,
            EGL_SURFACE_TYPE,
            EGL_WINDOW_BIT,
            EGL_NONE
    };

    if (EGL_TRUE !=  eglChooseConfig(display,configSpec,&config,1,&configNum))
    {
        LOGE("eglChooseConfig failed!");
        return;
    }
    //创建surface （关联原始窗口）
    EGLSurface  winSurface = eglCreateWindowSurface(display,config,nwin,0);

    if (winSurface == EGL_NO_SURFACE){
        LOGE("eglCreateWindowSurface failed!");
        return;
    }

    //context 创建关联上下文
    const EGLint ctxAttr[] = {
            EGL_CONTEXT_CLIENT_VERSION,2,EGL_NONE
    };

    EGLContext  context = eglCreateContext(display,config,EGL_NO_CONTEXT,ctxAttr);
    if (context == EGL_NO_CONTEXT){
        LOGE("eglCreateContext failed!");
        return;
    }
    //egl 关联 openl
    if (EGL_TRUE !=   eglMakeCurrent(display,winSurface,winSurface,context))
    {
        LOGE("eglMakeCurrent failed!");
        return;
    }
    LOGE("EGL Init Success!");

    env->ReleaseStringUTFChars(url_, url);
}
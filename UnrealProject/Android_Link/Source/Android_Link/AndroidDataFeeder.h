#pragma once
#if PLATFORM_ANDROID
#include <jni.h>
#include <android/log.h>
#include <string>

#define JNI_METHOD			__attribute__ ((visibility ("default"))) extern "C"
#define LOG_TAG "C++"

class AMyLinker;

#define ALOGD(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

void registerLinkerActor(AMyLinker* Actor);

JNI_METHOD void Java_com_rivotek_androiddatafeeder_androiddatafeeder_setStringValue(JNIEnv* env, jclass clazz, jstring name, jstring type, jstring value);

JNI_METHOD void Java_com_rivotek_androiddatafeeder_androiddatafeeder_setIntegerValue(JNIEnv* env, jclass clazz, jstring name, jstring type, jint value);

JNI_METHOD void Java_com_rivotek_androiddatafeeder_androiddatafeeder_setBooleanValue(JNIEnv* env, jclass clazz, jstring name, jstring type, jboolean value);

JNI_METHOD void Java_com_rivotek_androiddatafeeder_androiddatafeeder_setFloatValue(JNIEnv* env, jclass clazz, jstring name, jstring type, jfloat value);


#endif


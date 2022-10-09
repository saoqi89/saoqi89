#include "AndroidDataFeeder.h"
#include "MyLinker.h"

#if PLATFORM_ANDROID

AMyLinker* s_linkerActor = nullptr;

void registerLinkerActor(AMyLinker* actor) {
    if (nullptr == s_linkerActor) {
        s_linkerActor = actor;
    }
}

JNI_METHOD void Java_com_rivotek_androiddatafeeder_androiddatafeeder_setStringValue(JNIEnv* env, jclass clazz, jstring name, jstring type, jstring value) {
    // TODO: implement focusEvent()
    if (nullptr == env || nullptr == s_linkerActor) {
        ALOGD("!!! set String Value Error!!! env or actor is NULL");
        return;
    }

    /*const char* namestr = env->GetStringUTFChars(name, NULL);
    const char* typestr = env->GetStringUTFChars(name, NULL);
    const char* valueStr = env->GetStringUTFChars(value, NULL);
    ALOGD("!!!!!!!!!!!!!!! set %s Value %s", namestr, valueStr);

    FString nameString(UTF8_TO_TCHAR(namestr));
    FString typeString(UTF8_TO_TCHAR(typestr));
    FString vallueString(UTF8_TO_TCHAR(valueStr));
    s_linkerActor->DataManage(nameString, typeString, vallueString);

    env->ReleaseStringUTFChars(name, namestr);
    env->ReleaseStringUTFChars(type, typestr);
    env->ReleaseStringUTFChars(value, valueStr);*/
}

JNI_METHOD void Java_com_rivotek_androiddatafeeder_androiddatafeeder_setIntegerValue(JNIEnv* env, jclass clazz, jstring name, jstring type, jint value) {
    // TODO: implement focusEvent()
    if (nullptr == env || nullptr == s_linkerActor) {
        ALOGD("!!! set String Value Error!!! env or actor is NULL");
        return;
    }

    const char* jnamestr = env->GetStringUTFChars(name, NULL);
    std::string str(jnamestr);
    ALOGD("!!!!!!!!!!!!!!! set %s Value %d", jnamestr, value);

    FString nameString(UTF8_TO_TCHAR(jnamestr));
    int Num = (int)value;
    
    s_linkerActor->DataManageI(Num);
}

JNI_METHOD void Java_com_rivotek_androiddatafeeder_androiddatafeeder_setBooleanValue(JNIEnv* env, jclass clazz, jstring name, jstring type, jboolean value) {
    // TODO: implement focusEvent()
    if (nullptr == env || nullptr == s_linkerActor) {
        ALOGD("!!! set String Value Error!!! env or actor is NULL");
        return;
    }

    const char* jnamestr = env->GetStringUTFChars(name, NULL);
    std::string str(jnamestr);
    ALOGD("!!!!!!!!!!!!!!! set %s Value %d", jnamestr, value);
}

JNI_METHOD void Java_com_rivotek_androiddatafeeder_androiddatafeeder_setFloatValue(JNIEnv* env, jclass clazz, jstring name, jstring type, jfloat value) {
    // TODO: implement focusEvent()
    if (nullptr == env || nullptr == s_linkerActor) {
        ALOGD("!!! set String Value Error!!! env or actor is NULL");
        return;
    }

    const char* jnamestr = env->GetStringUTFChars(name, NULL);
    std::string str(jnamestr);
    ALOGD("!!!!!!!!!!!!!!! set %s Value %f", jnamestr, value);

    FString nameString(UTF8_TO_TCHAR(jnamestr));
    float Num = (float)value;
    
    s_linkerActor->DataManageF(nameString, Num);
}

#endif
#include "AndroidDataFeeder.h"
#include "MyLinker.h"

#if PLATFORM_ANDROID

AMyLinker* S_LinkerActor = nullptr;

void registerLinkerActor(AMyLinker* Actor)
{
	if (S_LinkerActor == nullptr)
	{
		S_LinkerActor = Actor;
	}
}

JNI_METHOD void Java_com_rivotek_androiddatafeeder_androiddatafeeder_setIntegerValue(JNIEnv* env, jclass clazz, jstring name, jstring type, jint value)
{
	if (nullptr == env || nullptr == S_LinkerActor) {
		ALOGD("!!! set String Value Error!!! env or actor is NULL");
		return;
	}

	/*const char* Namestr = env->GetStringUTFChars(name, NULL);
	const char* Typestr = env->GetStringUTFChars(type, NULL);
	//const char* vlue = env->GetStringUTFChars(value, NULL);

	FString NameString(UTF8_TO_TCHAR(Namestr));
	FString TypeString(UTF8_TO_TCHAR(Typestr));
	//int32 Num = FCString::Atoi(*valueNum);

	//jint age = (*env)->GetIntField(env, clazz);

	int Num = (int)value;
	ALOGD("!!!!!!!!!!!!!!! set Value is %d", Num);
	S_LinkerActor->DataManageI(Num);*/
}

JNI_METHOD void Java_com_rivotek_androiddatafeeder_androiddatafeeder_setIntegerValue(JNIEnv* env, jclass clazz, jstring name, jstring type, jint value) {
	// TODO: implement focusEvent()
	if (nullptr == env || nullptr == S_LinkerActor) {
		ALOGD("!!! set String Value Error!!! env or actor is NULL");
		return;
	}

	const char* jnamestr = env->GetStringUTFChars(name, NULL);
	std::string str(jnamestr);
	ALOGD("!!!!!!!!!!!!!!! set %s Value %d", jnamestr, value);

	FString nameString(UTF8_TO_TCHAR(jnamestr));
	int Num = (int)value;
    
	S_LinkerActor->DataManageI(Num);
}

JNI_METHOD void Java_com_rivotek_androiddatafeeder_androiddatafeeder_setBooleanValue(JNIEnv* env, jclass clazz, jstring name, jstring type, jboolean value) {
	// TODO: implement focusEvent()
	if (nullptr == env || nullptr == S_LinkerActor) {
		ALOGD("!!! set String Value Error!!! env or actor is NULL");
		return;
	}

	const char* jnamestr = env->GetStringUTFChars(name, NULL);
	std::string str(jnamestr);
	ALOGD("!!!!!!!!!!!!!!! set %s Value %d", jnamestr, value);
}

JNI_METHOD void Java_com_rivotek_androiddatafeeder_androiddatafeeder_setFloatValue(JNIEnv* env, jclass clazz, jstring name, jstring type, jfloat value) {
	// TODO: implement focusEvent()
	if (nullptr == env || nullptr == S_LinkerActor) {
		ALOGD("!!! set String Value Error!!! env or actor is NULL");
		return;
	}

	const char* jnamestr = env->GetStringUTFChars(name, NULL);
	std::string str(jnamestr);
	ALOGD("!!!!!!!!!!!!!!! set %s Value %f", jnamestr, value);

	FString nameString(UTF8_TO_TCHAR(jnamestr));
	float Num = (float)value;
	
	S_LinkerActor->DataManageF(Num);
}

#endif


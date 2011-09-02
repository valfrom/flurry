/*
 * android-specific implementation of the s3eFlurry extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3eFlurry_internal.h"

#include "s3eEdk.h"
#include "s3eEdk_android.h"
#include <jni.h>
#include "IwDebug.h"

static jobject g_Obj;
static jmethodID g_s3eFlurryStart;
static jmethodID g_s3eFlurryLogEvent;
static jmethodID g_s3eFlurryEndTimedEvent;
static jmethodID g_s3eFlurryLogError;
static jmethodID g_s3eFlurrySetUserID;
static jmethodID g_s3eFlurrySetUserAge;
static jmethodID g_s3eFlurrySetUserGender;
static jmethodID g_s3eFlurrySetLocation;
static jmethodID g_s3eFlurrySetSessionReportOnClose;
static jmethodID g_s3eFlurrySetSessionReportOnPause;

s3eResult s3eFlurryInit_platform()
{
    // Get the environment from the pointer
    JNIEnv* env = s3eEdkJNIGetEnv();
    jobject obj = NULL;
    jmethodID cons = NULL;

    // Get the extension class
    jclass cls = s3eEdkAndroidFindClass("s3eFlurry");
    if (!cls)
        goto fail;

    // Get its constructor
    cons = env->GetMethodID(cls, "<init>", "()V");
    if (!cons)
        goto fail;

    // Construct the java class
    obj = env->NewObject(cls, cons);
    if (!obj)
        goto fail;

    // Get all the extension methods
    g_s3eFlurryStart = env->GetMethodID(cls, "s3eFlurryStart", "(Ljava/lang/String;)V");
    if (!g_s3eFlurryStart)
        goto fail;

    g_s3eFlurryLogEvent = env->GetMethodID(cls, "s3eFlurryLogEvent", "(Ljava/lang/String;Z)V");
    if (!g_s3eFlurryLogEvent)
        goto fail;

    g_s3eFlurryEndTimedEvent = env->GetMethodID(cls, "s3eFlurryEndTimedEvent", "(Ljava/lang/String;)V");
    if (!g_s3eFlurryEndTimedEvent)
        goto fail;

    g_s3eFlurryLogError = env->GetMethodID(cls, "s3eFlurryLogError", "(Ljava/lang/String;Ljava/lang/String;)V");
    if (!g_s3eFlurryLogError)
        goto fail;

    g_s3eFlurrySetUserID = env->GetMethodID(cls, "s3eFlurrySetUserID", "(Ljava/lang/String;)V");
    if (!g_s3eFlurrySetUserID)
        goto fail;

    g_s3eFlurrySetUserAge = env->GetMethodID(cls, "s3eFlurrySetUserAge", "(I)V");
    if (!g_s3eFlurrySetUserAge)
        goto fail;

    g_s3eFlurrySetUserGender = env->GetMethodID(cls, "s3eFlurrySetUserGender", "(Z)V");
    if (!g_s3eFlurrySetUserGender)
        goto fail;

    g_s3eFlurrySetLocation = env->GetMethodID(cls, "s3eFlurrySetLocation", "()V");
    if (!g_s3eFlurrySetLocation)
        goto fail;

    g_s3eFlurrySetSessionReportOnClose = env->GetMethodID(cls, "s3eFlurrySetSessionReportOnClose", "()V");
    if (!g_s3eFlurrySetSessionReportOnClose)
        goto fail;

    g_s3eFlurrySetSessionReportOnPause = env->GetMethodID(cls, "s3eFlurrySetSessionReportOnPause", "()V");
    if (!g_s3eFlurrySetSessionReportOnPause)
        goto fail;



    IwTrace(FLURRY, ("FLURRY init success"));
    g_Obj = env->NewGlobalRef(obj);
    env->DeleteLocalRef(obj);
    env->DeleteLocalRef(cls);

    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;

fail:
    jthrowable exc = env->ExceptionOccurred();
    if (exc)
    {
        env->ExceptionDescribe();
        env->ExceptionClear();
        IwTrace(s3eFlurry, ("One or more java methods could not be found"));
    }
    return S3E_RESULT_ERROR;

}

void s3eFlurryTerminate_platform()
{
    // Add any platform-specific termination code here
}

void s3eFlurryStart_platform(const char* ID)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring ID_jstr = env->NewStringUTF(ID);
    env->CallVoidMethod(g_Obj, g_s3eFlurryStart, ID_jstr);
}

void s3eFlurryLogEvent_platform(const char* eventName, const s3eBool timed)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring eventName_jstr = env->NewStringUTF(eventName);
    env->CallVoidMethod(g_Obj, g_s3eFlurryLogEvent, eventName_jstr);
}

void s3eFlurryEndTimedEvent_platform(const char* eventName)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring eventName_jstr = env->NewStringUTF(eventName);
    env->CallVoidMethod(g_Obj, g_s3eFlurryEndTimedEvent, eventName_jstr);
}

void s3eFlurryLogError_platform(const char* errorName, const char* errorMessage)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring errorName_jstr = env->NewStringUTF(errorName);
    jstring errorMessage_jstr = env->NewStringUTF(errorMessage);
    env->CallVoidMethod(g_Obj, g_s3eFlurryLogError, errorName_jstr, errorMessage_jstr);
}

void s3eFlurrySetUserID_platform(const char* userID)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring userID_jstr = env->NewStringUTF(userID);
    env->CallVoidMethod(g_Obj, g_s3eFlurrySetUserID, userID_jstr);
}

void s3eFlurrySetUserAge_platform(const uint8 age)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_s3eFlurrySetUserAge);
}

void s3eFlurrySetUserGender_platform(const s3eFlurryUserGender gender)
{
    JNIEnv* env = s3eEdkJNIGetEnv();

	if(gender == S3E_FLURRY_MALE)
		env->CallVoidMethod(g_Obj, g_s3eFlurrySetUserGender, true);
	else if(gender == S3E_FLURRY_FEMALE)
		env->CallVoidMethod(g_Obj, g_s3eFlurrySetUserGender, false);
}

void s3eFlurrySetLocation_platform(s3eLocation* location)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_s3eFlurrySetLocation);
}

void s3eFlurrySetSessionReportOnClose_platform(const s3eBool sendReportOnClose)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_s3eFlurrySetSessionReportOnClose);
}

void s3eFlurrySetSessionReportOnPause_platform(const s3eBool sendReportOnPause)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_s3eFlurrySetSessionReportOnPause);
}

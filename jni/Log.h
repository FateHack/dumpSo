#ifndef _SECSHELL_LOG_
#define _SECSHELL_LOG_

#include <android/log.h>
#include <stdarg.h>


#ifdef __cplusplus
extern "C" {
#endif

#define LOG_TAG    "Fuck"

#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define LOGF(...)  __android_log_print(ANDROID_LOG_FATAL,LOG_TAG,__VA_ARGS__)

#if (1)
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#else
#define LOGD(...)
#define LOGI(...)
#endif



#ifdef __cplusplus
}
#endif

#endif



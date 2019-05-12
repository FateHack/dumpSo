#include <map>
#include <string.h>
#include <string>
#include <pthread.h>
#include <signal.h>
#include "public.h"
#include "Main.h"


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
    jint result = JNI_ERR;
    jint version = 0;
    JNIEnv* env = 0;
    do
    {
        if(vm->GetEnv((void**)&env, JNI_VERSION_1_6) == JNI_OK)
        {
        	version = JNI_VERSION_1_6;
        }
        else if(vm->GetEnv((void**)&env, JNI_VERSION_1_4) == JNI_OK)
        {
        	version = JNI_VERSION_1_4;
        }
        else if(vm->GetEnv((void**)&env, JNI_VERSION_1_2) == JNI_OK)
        {
        	version = JNI_VERSION_1_2;
        }
        else if(vm->GetEnv((void**)&env, JNI_VERSION_1_1) == JNI_OK)
        {
        	version = JNI_VERSION_1_1;
        }
        else
        {
        	
        	break;
        }
    	result = version;

    } while(0);


    return result;
}



__attribute__((constructor)) void entry()
{

	LOGI("=======================Enter lib entry=====================");
	
	
	int err;
    pthread_t ntid;

    pthread_create(&ntid, NULL, hook_u3d, NULL);
    if (err != 0) {
        printf("create thread failed:%s\n", strerror(err));

    }

}

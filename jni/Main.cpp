#include "Log.h"
#include <unistd.h>
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sys/mman.h>
#include <vector>
#include <pthread.h>
#include <signal.h>
#include <jni.h>
#include "Utils.h"

using namespace std;

//typedef int(*mprotect_t)(void* __addr, size_t __size, int __prot);

int dump(const char *soName) {
    ProcMap map=getLibraryMap(soName);
    if (!map.isValid())//maps中没有找到相应的内存映射
    {
        return -1;
    }
    int n=map.length/getpagesize()+1;
    int ret = mprotect(map.startAddr, n*getpagesize(), PROT_READ | PROT_WRITE | PROT_EXEC);//内存可读可写
    char* memory=(char*)malloc(map.length);
    memcpy(memory,map.startAddr,map.length);
    char savePath[1024]={0};
    sprintf(savePath,"/sdcard/%s-%s",map.startAddr,soName);
    FILE* file=fopen(savePath,"w+");
    fwrite(memory,1,map.length,file);
    fclose(file);
    free(memory);
	return 0;
}

void *my_thread(void *pVoid) {
    LOGD("Hook:====hook_game_proxy begin====");
    while (1) {
		int ret=dump("libil2cpp.so");
		int ret2=dump("global-metadata.dat");
		if(ret==0&&ret2==0){
            pthread_exit((void *) "the first return!");
		  }
          sleep(2);
		}
    LOGD("Hook:=====hook_game_proxy finish=====");
}

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

    pthread_create(&ntid, NULL, my_thread, NULL);
    if (err != 0) {
        printf("create thread failed:%s\n", strerror(err));

    }

}

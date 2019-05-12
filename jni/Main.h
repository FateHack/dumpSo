#ifndef _HOOK_H_
#define _HOOK_H_

#include <jni.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <elf.h> 
#include <string>
#include <list>
#include <map>

void* hook_u3d(void *pVoid);

#endif //_HOOK_H_
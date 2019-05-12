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


using namespace std;


//typedef int(*mprotect_t)(void* __addr, size_t __size, int __prot);


void printAddr(char *addr) {
    LOGI("Addr %p : %x %x %x %x %x %x %x %x", addr, addr[0], addr[1], addr[2], addr[3], addr[4], addr[5], addr[6],
         addr[7]);
}


void *get_module_base(const char *module_name) {
    FILE *fp;
    long addr = 0;
    char *pch;
    char filename[32];
    char line[1024];
    snprintf(filename, sizeof(filename), "/proc/self/maps");
    fp = fopen(filename, "r");
    if (fp != NULL) {
        while (fgets(line, sizeof(line), fp)) {
            if (strstr(line, module_name)) {
                pch = strtok(line, "-");
                addr = strtoul(pch, NULL, 16);
                if (addr == 0x8000)
                    addr = 0;
                break;
            }
        }
        fclose(fp);
    }
    return (void *) addr;
}

int getMaps(const char *soName) {
    vector<string> strLine;
    vector<string>::iterator it;
    FILE *fp;
    char fileName[32];
    char line[1024];
    char *pch;
    long beginAddr;
    long endAddr;
	bool isil2cpp=false;
    fp = fopen("/proc/self/maps", "r");
    int length = 0;
    if (fp != NULL) {
        while (fgets(line, sizeof(line), fp)) { 
            if (strstr(line, soName)) {
                string s(line);
				isil2cpp=true;
                LOGE("s--%s", s.c_str());
                strLine.push_back(s);
            }
        }
    }
	if(!isil2cpp){
		
		return -1;
	}
    fclose(fp);
    it = strLine.begin();
    char *new_line = (char *) malloc(1024);
    char *new_line2 = (char *) malloc(1024);
    strcpy(new_line, (*it).c_str());
    pch = strtok(new_line, "-");
	char* begAddr=pch;
    if (pch != NULL) {
        beginAddr = strtoul(pch, NULL, 16);
    }
    it = strLine.end() - 1;
    strcpy(new_line2, (*it).c_str());
    pch = strtok(new_line2, " ");
    if (pch != NULL) {
        pch = strtok(pch, "-");
        pch = strtok(NULL, "-");
        LOGE("pch--%s", pch);
    }
    endAddr = strtoul(pch, NULL, 16);
    LOGE("beginAddr=%ld", beginAddr);
    LOGE("endAddr=%ld", endAddr);
    length = (int) (endAddr - beginAddr);
    free(new_line);
    free(new_line2);
    new_line = NULL;
    new_line2 = NULL;
    uint32_t page_size = getpagesize();
    int n = length / page_size;
    int ret = mprotect((void *) beginAddr, page_size * n, PROT_READ | PROT_WRITE | PROT_EXEC);
    LOGE("page_size=%d", page_size);
    LOGE("length=%d", length);
    char *memory = (char *) malloc(length * sizeof(char));
    memcpy(memory, (void *) beginAddr, length);
	char savePath[1024];
	sprintf(savePath,"/sdcard/%s-%s",begAddr,soName);
    FILE *file = fopen(savePath, "w+");
    fwrite(memory, 1, length, file);
    LOGE("ret is %d", ret);
    fclose(file);
	return 0;
}

char *get_processName() {
    char *path = "/proc/self/cmdline";
    ifstream in(path);
    char proccessName[255];
    in.read(proccessName, sizeof(proccessName));
    in.close();
    return proccessName;


}


void *hook_u3d(void *pVoid) {
    LOGD("Hook:====hook_game_proxy begin====");
    while (1) {
        char *proccessName = get_processName();
        char libPath[255];

        sprintf(libPath, "/data/data/%s/lib/libil2cpp.so", proccessName);
		if(fopen(libPath,"r")!=NULL){
		
		int ret=getMaps("libil2cpp.so");
		getMaps("global-metadata.dat");
		if(ret==0){
        pthread_exit((void *) "the first return!");
		}
		
		}
		sleep(2);
    }
    LOGD("Hook:=====hook_game_proxy finish=====");

}

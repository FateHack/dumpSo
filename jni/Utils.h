
#ifndef UTILS_H
#define UTILS_H

#include <dlfcn.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <sys/stat.h>


struct ProcMap {
    void *startAddr;
    void *endAddr;
    size_t length;
    std::string perms;
    long offset;
    std::string dev;
    int inode;
    std::string pathname;

    bool isValid() { return (startAddr != NULL && endAddr != NULL && !pathname.empty()); }
};


ProcMap getLibraryMap(int pid,const char *libraryName);

std::string getProcName();

std::string getSoName();

bool getFileStat(const char *fileName, struct stat *buffer);

bool isMainProcName();

#endif //UTILS_H

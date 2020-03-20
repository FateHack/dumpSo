

#include "Utils.h"


ProcMap getLibraryMap(const char *libraryName) {
    ProcMap retMap;
    char line[512] = {0};

    FILE *fp = fopen("/proc/self/maps", "rt");
    if (fp != NULL) {
        while (fgets(line, sizeof(line), fp)) {
            if (strstr(line, libraryName)) {
                char tmpPerms[5] = {}, tmpDev[12] = {}, tmpPathname[455] = {};
                // parse a line in maps file
                // (format) startAddress-endAddress perms offset dev inode pathname
                sscanf(line, "%llx-%llx %s %ld %s %d %s",
                       (long long unsigned *) &retMap.startAddr,
                       (long long unsigned *) &retMap.endAddr,
                       tmpPerms, &retMap.offset, tmpDev, &retMap.inode, tmpPathname);

                retMap.length = (uintptr_t) retMap.endAddr - (uintptr_t) retMap.startAddr;
                retMap.perms = tmpPerms;
                retMap.dev = tmpDev;
                retMap.pathname = tmpPathname;
                break;
            }
        }
        fclose(fp);
    }
    return retMap;
}


std::string getProcName() {
    std::string ret;
    char cmdline[256] = {0};
    FILE *fp;

    fp = fopen("/proc/self/cmdline", "r");
    if (fp) {
        fgets(cmdline, sizeof(cmdline), fp);
        fclose(fp);
        ret = cmdline;
    }
    return ret;
}

bool getFileStat(const char *fileName, struct stat *buffer) {
    return stat(fileName, buffer) != -1;
}
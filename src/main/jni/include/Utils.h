#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string>
#include <string.h>
#include <limits.h>
#include <inttypes.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

uintptr_t libBaseAddress = 0;

uintptr_t find_library(const char *library) {
    char filename[0xFF] = {0},
            buffer[1024] = {0};
    FILE *fp = NULL;
    uintptr_t address = 0, start = 0, end = 0;
    char flags[7], path[PATH_MAX];
    pid_t pid = getpid();
    sprintf(filename, "/proc/%d/maps", pid);
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("fopen");
        goto done;
    }
    while (fgets(buffer, sizeof(buffer), fp)) {
        strcpy(path, "");
        sscanf(buffer, "%" PRIxPTR "-%" PRIxPTR " %s %*x %*x:%*x %*u %s\n", &start, &end, flags, path);
        if (strstr(flags, "r-xp") == 0) continue;
        if (strstr(path, library)) {
            address = start;
            goto done;
        }
    }
    done:
    if (fp) {
        fclose(fp);
    }
    return address;
}

const char *GetPackageName() {
    char *id[256];
    FILE *fp = fopen("proc/self/cmdline", "r");
    if (fp) {
        fread(id, sizeof(id), 1, fp);
        fclose(fp);
    }
    return (const char*)id;
}

string pointerToString(uintptr_t ptr) {
    char buffer[20];
#if defined(__aarch64__)
    snprintf(buffer, sizeof(buffer), "0x%llX", static_cast<unsigned long long>(ptr));
#else
    snprintf(buffer, sizeof(buffer), "0x%lX", static_cast<unsigned long long>(ptr));
#endif
    return string(buffer);
}

void DumpFile(string text) {
    string dir = "/storage/emulated/0/Android/data/" + string(GetPackageName()) + "/dump.cpp"; // here's your path
    ofstream file(dir.c_str(), ios::app);
    file << text << endl;
    file.close();
}
void DumpFile(const char *text = "") {
    string dir = "/storage/emulated/0/Android/data/" + string(GetPackageName()) + "/dump.cpp";
    ofstream file(dir.c_str(), ios::app);
    file << text << endl;
    file.close();
}
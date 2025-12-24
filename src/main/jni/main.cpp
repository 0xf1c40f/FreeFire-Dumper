#include <jni.h>
#include <pthread.h>

#include "Dumper.h"

void *functions (void*) 
{
    do {
		address = find_library("libil2cpp.so");
	} while (address == 0);
    HookInit();
    sleep(1);
    Dumper();
    pthread_exit(nullptr);
}

__attribute__((constructor))
void lib_main() {
    pthread_t threads;
    pthread_create(&threads, NULL, functions, NULL);
}

extern "C" jint JNIEXPORT JNI_OnLoad(JavaVM *vm, void *key) {
    JNIEnv *env;
    vm->GetEnv((void**)&env, JNI_VERSION_1_6);
    return JNI_VERSION_1_6;
}
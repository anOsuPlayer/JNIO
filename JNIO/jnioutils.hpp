#ifndef JNIOUTILS
    #define JNIOUTILS

    #include "jni.h"
    #include "jnioenv.hpp"

    #define JNIOImpl extern "C" JNIEXPORT JNICALL

    #define DefaultArgs jnio::JNIOEnv env, jobject thisObj

    #define StaticArgs jnio::JNIOEnv env, jclass thisClass

#endif
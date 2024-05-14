#ifndef JNIOUTILS
    #define JNIOUTILS

    #include "jni.h"
    #include "jnioenv.hpp"

    #define JNIOImpl extern "C" JNIEXPORT JNICALL

    #define DefaultArgs jnio::JNIOEnv env, jobject thisObj

    #define StaticArgs jnio::JNIOEnv env, jclass thisClass

    namespace jnio {

        const jboolean TRUE = jboolean(JNI_TRUE);

        const jboolean FALSE = jboolean(JNI_FALSE);

        jboolean operator ""jz (unsigned long long l);

        jbyte operator ""jb (unsigned long long l);
        
        jchar operator ""jc (unsigned long long l);
        
        jshort operator ""js (unsigned long long l);
        
        jint operator ""ji (unsigned long long l);
        
        jlong operator ""jl (unsigned long long l);
        
        jfloat operator ""jf (long double ld);
        
        jdouble operator ""jd (long double ld);
    }

#endif
#ifndef JNIO_UTILS
    #define JNIO_UTILS

    #include "jni.h"
    
    #define JNIOImpl extern "C" JNIEXPORT JNICALL

    namespace jnio {

		#define member_args JNIEnv* env, jobject jthis

    	#define static_args JNIEnv* env, jclass clazz

        static jboolean TRUE = jboolean(JNI_TRUE);

        static jboolean FALSE = jboolean(JNI_FALSE);

        jboolean operator ""_jz (unsigned long long);

        jbyte operator ""_jb (unsigned long long);
        
        jchar operator ""_jc (unsigned long long);
        
        jshort operator ""_js (unsigned long long);
        
        jint operator ""_ji (unsigned long long);
        
        jlong operator ""_jl (unsigned long long);
        
        jfloat operator ""_jf (long double);
        
        jdouble operator ""_jd (long double);
    }

#endif
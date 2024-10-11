#ifndef JNIO_UTILS
    #define JNIO_UTILS

    #include "jni.h"
    
    #define JNIOImpl extern "C" JNIEXPORT JNICALL

    namespace jnio {

		#define member_args JNIEnv* env, jobject jthis

    	#define static_args JNIEnv* env, jclass clazz

        static jboolean TRUE(JNI_TRUE);

        static jboolean FALSE(JNI_FALSE);

        constexpr jboolean operator ""_jz (unsigned long long l) {
            return l == 0 ? 1 : 0;
        }

        constexpr jbyte operator ""_jb (unsigned long long l) {
            return static_cast<jbyte>(l);
        }
        
        constexpr jchar operator ""_jc (unsigned long long l) {
            return static_cast<jchar>(l);
        }
        
        constexpr jshort operator ""_js (unsigned long long l) {
            return static_cast<jshort>(l);
        }
        
        constexpr jint operator ""_ji (unsigned long long l) {
            return static_cast<jint>(l);
        }

        constexpr jlong operator ""_jl (unsigned long long l) {
            return static_cast<jlong>(l);
        }
        
        constexpr jfloat operator ""_jf (long double ld) {
            return static_cast<jfloat>(ld);
        }
        
        constexpr jdouble operator ""_jd (long double ld) {
            return static_cast<jdouble>(ld);
        }
    }

#endif
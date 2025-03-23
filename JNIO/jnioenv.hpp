#ifndef JNIO_ENVIRONMENT_H
    #define JNIO_ENVIRONMENT_H

    #include <jni.h>

    namespace jnio {

        static JNIEnv* JNIOEnv;

        void init(JNIEnv* environment);
    }

#endif
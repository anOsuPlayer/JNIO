#ifndef JNIO_ENV
    #define JNIO_ENV

    #include "jni.h"

    namespace jnio {

        class JNIOEnv {
            private:
                JNIOEnv() = default;

                JNIEnv* environment;

            public:
                JNIOEnv(JNIEnv* environment);

                JNIEnv* get_JNIEnv() noexcept;
        };
    }

#endif
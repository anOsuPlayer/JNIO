#ifndef JNIO_ENV
    #define JNIO_ENV

    #include "jni.h"

    namespace jnio {

        class JNIOEnv {
            private:
                JNIOEnv() = default;

                mutable JNIEnv* environment;

            public:
                JNIOEnv(JNIEnv* environment);

                const JNIOEnv& operator = (const JNIOEnv& other) const;

                JNIEnv* get_JNIEnv() const noexcept;
        };
    }

#endif
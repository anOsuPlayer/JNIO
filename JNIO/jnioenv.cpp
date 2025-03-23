#include "jnioenv.hpp"

namespace jnio {

    void init(JNIEnv* environment) {
        JNIOEnv = environment;
    }
}
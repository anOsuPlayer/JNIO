#include "jnioenv.hpp"

namespace jnio {

    JNIOEnv::JNIOEnv(JNIEnv* environment) {
        this->environment = environment;
    }

    JNIEnv* JNIOEnv::get_JNIEnv() noexcept {
        return this->environment;
    } 
}
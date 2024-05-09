#include "jnioenv.hpp"

namespace jnio {

    JNIOEnv::JNIOEnv(JNIEnv* environment) {
        this->environment = environment;
    }

    const JNIOEnv& JNIOEnv::operator = (const JNIOEnv& other) const {
        this->environment = other.environment;
        return *this;
    }

    JNIEnv* JNIOEnv::get_JNIEnv() const noexcept {
        return this->environment;
    } 
}
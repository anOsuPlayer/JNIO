#include "jnioutils.hpp"

namespace jnio {

    jboolean operator ""_jz (unsigned long long l) {
        return l == 0 ? FALSE : TRUE;
    }

    jbyte operator ""_jb (unsigned long long l) {
        return static_cast<jbyte>(l);
    }
    
    jchar operator ""_jc (unsigned long long l) {
        return static_cast<jchar>(l);
    }
    
    jshort operator ""_js (unsigned long long l) {
        return static_cast<jshort>(l);
    }
    
    jint operator ""_ji (unsigned long long l) {
        return static_cast<jint>(l);
    }

    jlong operator ""_jl (unsigned long long l) {
        return static_cast<jlong>(l);
    }
    
    jfloat operator ""_jf (long double ld) {
        return static_cast<jfloat>(ld);
    }
    
    jdouble operator ""_jd (long double ld) {
        return static_cast<jdouble>(ld);
    }
}
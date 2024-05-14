#include "jnioutils.hpp"

namespace jnio {

    jboolean operator ""jz (unsigned long long l) {
        return l == 0 ? FALSE : TRUE;
    }

    jbyte operator ""jb (unsigned long long l) {
        return static_cast<jbyte>(l);
    }
    
    jchar operator ""jc (unsigned long long l) {
        return static_cast<jchar>(l);
    }
    
    jshort operator ""js (unsigned long long l) {
        return static_cast<jshort>(l);
    }
    
    jint operator ""ji (unsigned long long l) {
        return static_cast<jint>(l);
    }

    jlong operator ""jl (unsigned long long l) {
        return static_cast<jlong>(l);
    }
    
    jfloat operator ""jf (long double ld) {
        return static_cast<jfloat>(ld);
    }
    
    jdouble operator ""jd (long double ld) {
        return static_cast<jdouble>(ld);
    }
}
#pragma once

#include "jnioexception.hpp"

namespace jnio {

    class NoSuchMethodException : public jnio_exception {
        public:
            NoSuchMethodException();
            explicit NoSuchMethodException(const char* message);
    };
}
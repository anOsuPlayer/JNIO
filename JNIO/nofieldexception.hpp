#pragma once

#include "jnioexception.hpp"

namespace jnio {

    class NoSuchFieldException : public jnio_exception {
        public:
            NoSuchFieldException();
            explicit NoSuchFieldException(const char* message);
    };
}
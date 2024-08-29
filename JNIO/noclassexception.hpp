#pragma once

#include "jnioexception.hpp"

namespace jnio {

    class NoSuchClassException : public jnio_exception {
        public:
            NoSuchClassException();
            explicit NoSuchClassException(const char* message);
    };
}
#pragma once

#include "jnioexception.hpp"

namespace jnio {

    class no_such_method : public jnio_exception {
        public:
            no_such_method();
            explicit no_such_method(const char* message);
    };
}
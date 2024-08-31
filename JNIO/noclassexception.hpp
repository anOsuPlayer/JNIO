#pragma once

#include "jnioexception.hpp"

namespace jnio {

    class no_such_class : public jnio_exception {
        public:
            no_such_class();
            explicit no_such_class(const char* message);
    };
}
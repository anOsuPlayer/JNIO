#pragma once

#include "jnioexception.hpp"

namespace jnio {

    class no_such_field : public jnio_exception {
        public:
            no_such_field();
            explicit no_such_field(const char* message);
    };
}
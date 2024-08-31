#include "nomethodexception.hpp"

namespace jnio {

    no_such_method::no_such_method() : jnio_exception("No such method exists.") {

    }

    no_such_method::no_such_method(const char* message) : jnio_exception(message) {
		
    }
}
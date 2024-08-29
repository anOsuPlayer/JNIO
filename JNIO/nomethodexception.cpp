#include "nomethodexception.hpp"

namespace jnio {

    NoSuchMethodException::NoSuchMethodException() : jnio_exception("No such method exists.") {

    }

    NoSuchMethodException::NoSuchMethodException(const char* message) : jnio_exception(message) {
		
    }
}
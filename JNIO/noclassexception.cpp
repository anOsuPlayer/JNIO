#include "noclassexception.hpp"

namespace jnio {

    NoSuchClassException::NoSuchClassException() : jnio_exception("No such class exists.") {

    }

    NoSuchClassException::NoSuchClassException(const char* message) : jnio_exception(message) {
		
    }
}
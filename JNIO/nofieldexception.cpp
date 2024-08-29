#include "nofieldexception.hpp"

namespace jnio {

    NoSuchFieldException::NoSuchFieldException() : jnio_exception("No such field exists.") {

    }

    NoSuchFieldException::NoSuchFieldException(const char* message) : jnio_exception(message) {
		
    }
}
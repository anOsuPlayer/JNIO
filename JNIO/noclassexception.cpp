#include "noclassexception.hpp"

namespace jnio {

    no_such_class::no_such_class() : jnio_exception("No such class exists.") {

    }

    no_such_class::no_such_class(const char* message) : jnio_exception(message) {
		
    }
}
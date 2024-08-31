#include "nofieldexception.hpp"

namespace jnio {

    no_such_field::no_such_field() : jnio_exception("No such field exists.") {

    }

    no_such_field::no_such_field(const char* message) : jnio_exception(message) {
		
    }
}
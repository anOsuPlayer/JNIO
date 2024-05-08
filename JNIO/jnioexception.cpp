#include "jnioexception.hpp"

namespace jnio {

    jnio_exception::jnio_exception(const char* message) {
        this->message = message;
    }

    const char* jnio_exception::what() const noexcept {
        return this->message;
    }
}
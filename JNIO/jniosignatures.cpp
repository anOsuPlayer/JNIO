#include "jniosignatures.hpp"

namespace jnio {

    base_signature::base_signature(const char* signature) {
        this->signature = std::string(signature);
    }

    base_signature::base_signature(const std::string& signature) {
        this->signature = signature;
    }

    base_signature::base_signature(const base_signature& signature) {
        this->signature = signature.signature;
    }

    const std::string& base_signature::get_signature() const noexcept {
        return this->signature;
    }

    const base_signature& base_signature::operator = (const base_signature& signature) {
        this->signature = signature.signature;
        return *this;
    }

    const base_signature base_signature::VOID = base_signature("V");

    const base_signature base_signature::BOOLEAN = base_signature("Z");

    const base_signature base_signature::BYTE = base_signature("B");

    const base_signature base_signature::CHAR = base_signature("C");

    const base_signature base_signature::SHORT = base_signature("S");

    const base_signature base_signature::INT = base_signature("I");

    const base_signature base_signature::LONG = base_signature("J");

    const base_signature base_signature::FLOAT = base_signature("F");

    const base_signature base_signature::DOUBLE = base_signature("D");

    object_signature::object_signature(const char* signature) {
        this->signature = "L";
        this->signature += signature;
        this->signature += ";";
        for (int i = 0; i < this->signature.size(); i++) {
            this->signature[i] = (this->signature[i] == '.') ? '/' : this->signature[i];
        }
    }

    object_signature::object_signature(const std::string& signature) {
        this->signature = "L";
        this->signature += signature;
        this->signature += ";";
        for (int i = 0; i < this->signature.size(); i++) {
            this->signature[i] = (this->signature[i] == '.') ? '/' : this->signature[i];
        }
    }

    const object_signature object_signature::OBJECT = object_signature("java/lang/Object");

    const object_signature object_signature::STRING = object_signature("java/lang/String");

    array_signature::array_signature(const std::string& signature) {
        this->signature = signature;
    }

    array_signature::array_signature(const base_signature& signature, unsigned int height = 1) {
        if (height == 0) {
            throw jnio_exception("array_signature height must be greater or equal to one.");
        }
        
        for (int i = 0; i < height; i++) {
            this->signature += "[";
        }
        this->signature += signature.signature;
    }

    base_signature array_signature::component_type() const noexcept {
        std::string component = this->signature.substr(1);
        switch (component[0]) {
            case '[' : {
                return array_signature(component);
            }
            case 'L' : {
                return object_signature(component);
            }
            default : {
                return base_signature(component);
            }
        }
    }

    base_signature array_signature::base_type() const noexcept {
        std::string component = this->signature.substr(this->signature.find_last_of('['));
        switch (component[0]) {
            case 'L' : {
                return object_signature(component);
            }
            default : {
                return base_signature(component);
            }
        }
    }
}
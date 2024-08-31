#include "javasignature.hpp"

namespace jnio::sign {

    pure_signature::pure_signature(const std::string& s) {
		this->sign = s;
    }

	pure_signature::operator const char*() const noexcept {
		return this->sign.c_str();
	}

	const std::string& pure_signature::string() const noexcept {
		return this->sign;
	}

	bool pure_signature::operator == (const pure_signature& s) const noexcept {
		return this->sign == s.sign;
	}

	signature::signature(const std::string& signature) : pure_signature(signature) {

	}

	args::args(std::initializer_list<signature> s) {
		for (auto it = s.begin(); it != s.end(); it++) {
			*this += *it;
		}
	}

	args& args::operator + (const signature& s) {
        if (s == VOID) {
            throw std::invalid_argument("A Void signature cannot be part of a args.");
        }
		this->sign += s.string();

        return *this;
    }

    args& args::operator += (const signature& s) {
        return *this + s;
    }

    object::object(const std::string& s) : signature(s) {
        if (this->sign[0] != 'L' || this->sign[0] != '[') {
			this->sign = 'L' + this->sign;
		}
		if (this->sign[this->sign.size()-1] != ';') {
			this->sign += ';';
		}

        for (size_t i = 1; i < this->sign.size(); i++) {
            this->sign[i] = (this->sign[i] == '.') ? '/' : this->sign[i];
        }
    }

    array::array(const signature& base, size_t order) {
        if (order == 0) {
            throw std::invalid_argument("Unable to create a signature referring to a 0-dimensions array.");
        }
        if (base == VOID) {
            throw std::invalid_argument("Cannot create an array of a void array.");
        }

		this->sign += std::string('[', order) + base.string();
    }

	size_t array::get_order() const noexcept {
		return this->order;
	}

    signature array::getBasesignature() const noexcept {
        return signature(this->string().substr(this->order));
    }

    method::method(const std::string& s) {
        this->sign = s;
    }

    method::method(const signature& returntype) {
        this->sign = "()" + returntype.string();
    }

    method::method(const signature& returntype, const args& args) {
        this->sign = "(";
		this->sign += args.string();
		this->sign += ')';
		this->sign += returntype.string();
    }

    signature method::returnType() const noexcept {
        return signature(this->string().substr(this->string().find_last_of(')')+1));
    }

    constructor::constructor() : method(VOID) {

    }

    constructor::constructor(const std::string& signature) : method(signature) {
        if (signature[signature.length()-1] != 'V') {
            throw std::invalid_argument("constructors must not state any return type other than void: \"(...)V\"");
        }
    }

    constructor::constructor(const args& args) : method(VOID, args) {

    }

    field::field(const std::string& signature) {
        if (signature.find('(') != std::string::npos || signature.find(')') != std::string::npos) {
			throw std::invalid_argument("Unable to initialize a field with a method.");
		}
    }

    field::field(const signature& type) {
        this->sign = type.string();
    }
}
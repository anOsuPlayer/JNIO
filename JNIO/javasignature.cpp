#include "javasignature.hpp"

namespace jnio::sign {

    PureSignature::PureSignature(const std::string& s) {
		this->signature = s;
    }

	PureSignature::operator const char*() const noexcept {
		return this->signature.c_str();
	}

	const std::string& PureSignature::string() const noexcept {
		return this->signature;
	}

	bool PureSignature::operator == (const PureSignature& s) const noexcept {
		return this->signature == s.signature;
	}

	Signature::Signature(const std::string& signature) : PureSignature(signature) {

	}

	Args::Args(std::initializer_list<Signature> s) {
		for (auto it = s.begin(); it != s.end(); it++) {
			*this += *it;
		}
	}

	Args& Args::operator + (const Signature& s) {
        if (s == VOID) {
            throw std::invalid_argument("A Void Signature cannot be part of a Args.");
        }
		this->signature += s.string();

        return *this;
    }

    Args& Args::operator += (const Signature& s) {
        return *this + s;
    }

    Object::Object(const std::string& s) : Signature(s) {
        if (this->signature[0] != 'L' || this->signature[0] != '[') {
			this->signature = 'L' + this->signature;
		}
		if (this->signature[this->signature.size()-1] != ';') {
			this->signature += ';';
		}

        for (size_t i = 1; i < this->signature.size(); i++) {
            this->signature[i] = (this->signature[i] == '.') ? '/' : this->signature[i];
        }
    }

    Array::Array(const Signature& base, size_t order) {
        if (order == 0) {
            throw std::invalid_argument("Unable to create a Signature referring to a 0-dimensions array.");
        }
        if (base == VOID) {
            throw std::invalid_argument("Cannot create an Array of a void array.");
        }

		this->signature += std::string('[', order) + base.string();
    }

	size_t Array::get_order() const noexcept {
		return this->order;
	}

    Signature Array::getBaseSignature() const noexcept {
        return Signature(this->string().substr(this->order));
    }

    Method::Method(const std::string& s) {
        this->signature = s;
    }

    Method::Method(const Signature& returntype) {
        this->signature = "()" + returntype.string();
    }

    Method::Method(const Signature& returntype, const Args& args) {
        this->signature = "(";
		this->signature += args.string();
		this->signature += ')';
		this->signature += returntype.string();
    }

    Signature Method::returnType() const noexcept {
        return Signature(this->string().substr(this->string().find_last_of(')')+1));
    }

    Constructor::Constructor() : Method(VOID) {

    }

    Constructor::Constructor(const std::string& signature) : Method(signature) {
        if (signature[signature.length()-1] != 'V') {
            throw std::invalid_argument("Constructors must not state any return type other than void: \"(...)V\"");
        }
    }

    Constructor::Constructor(const Args& args) : Method(VOID, args) {

    }

    Field::Field(const std::string& signature) {
        if (signature.find('(') != std::string::npos || signature.find(')') != std::string::npos) {
			throw std::invalid_argument("Unable to initialize a Field with a Method.");
		}
    }

    Field::Field(const Signature& type) {
        this->signature = type.string();
    }
}
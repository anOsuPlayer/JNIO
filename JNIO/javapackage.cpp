#include "javapackage.hpp"

namespace jnio {

    java_package::java_package(const std::string& location) {
		this->location = location;
    }
    
    java_class java_package::get_class(const char* classname) const {
        if (classname == nullptr) {
            throw std::invalid_argument("Unable to find a Java Class from a nullptr.");
        }
        return java_class(*this, classname);
    }

    const std::string& java_package::string() const noexcept {
        return this->location;
    }

	const char* java_package::c_str() const noexcept {
        return this->location.c_str();
    }

	bool java_package::operator == (const java_package& other) const noexcept {
        return this->location == other.location;
    }
	
}
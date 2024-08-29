#include "javapackage.hpp"

namespace jnio {

    JavaPackage::JavaPackage(JNIEnv* env, const std::string& location) {
		this->env = env;
		this->location = location;
    }
    
    JavaClass JavaPackage::getClass(const char* classname) const {
        if (classname == nullptr) {
            throw std::invalid_argument("Unable to find a Java Class from a nullptr.");
        }
        return JavaClass(this->env, *this, classname);
    }

    const std::string& JavaPackage::string() const noexcept {
        return this->location;
    }

	const char* JavaPackage::c_str() const noexcept {
        return this->location.c_str();
    }

	bool JavaPackage::operator == (const JavaPackage& other) const noexcept {
        return this->location == other.location;
    }
	
}
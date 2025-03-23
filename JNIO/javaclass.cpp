#include "javaclass.hpp"
#include "javamethod.hpp"

namespace jnio {

	static jmethodID GET_CLASS;

	static jmethodID GET_NAME;

    java_class::java_class(jclass clazz) {
        this->clazz = (jclass) JNIOEnv->NewWeakGlobalRef(clazz);

        if (GET_CLASS == nullptr) {
			GET_CLASS = JNIOEnv->GetMethodID(clazz, "get_class", "()Ljava/lang/Class;");
		}

		jclass thisClass = (jclass) JNIOEnv->CallObjectMethod(clazz, GET_CLASS);

		if (GET_NAME == nullptr) {
			GET_NAME = JNIOEnv->GetMethodID(thisClass, "getName", "()Ljava/lang/String;");
		}

		jstring name = (jstring) JNIOEnv->CallObjectMethod(thisClass, GET_NAME);

        const char* str = JNIOEnv->GetStringUTFChars(name, 0);
        this->classname = str;

        JNIOEnv->ReleaseStringUTFChars(name, str);
        JNIOEnv->DeleteLocalRef(name);
        JNIOEnv->DeleteLocalRef(thisClass);
    }

    java_class::java_class(const std::string& classname) {
		this->classname = classname;
		for (size_t i = 0; i < this->classname.size(); i++) {
            this->classname[i] = (this->classname[i] == '.') ? '/' : this->classname[i];
        }

        jclass c = JNIOEnv->FindClass(this->classname.c_str());

        if (c == nullptr) {
            throw no_such_class();
        }
        this->clazz = (jclass) JNIOEnv->NewWeakGlobalRef(c);
        JNIOEnv->DeleteLocalRef(c);
    }
	
    java_class::java_class(const java_package& pack, const std::string& classname) {
        this->classname = pack.string();
		this->classname += '/';
		this->classname += classname;
		for (size_t i = 0; i < this->classname.size(); i++) {
            this->classname[i] = (this->classname[i] == '.') ? '/' : this->classname[i];
        }

        jclass c = JNIOEnv->FindClass(this->classname.c_str());

        if (c == nullptr) {
            throw no_such_class();
        }
        this->clazz = (jclass) JNIOEnv->NewWeakGlobalRef(c);

        JNIOEnv->DeleteLocalRef(c);
    }

    java_class::java_class(const java_class& clazz) {
        this->classname = clazz.classname;
        this->clazz = (jclass) JNIOEnv->NewWeakGlobalRef(clazz.clazz);
    }

    java_class::~java_class() {
        if (this->clazz != nullptr) {
            JNIOEnv->DeleteWeakGlobalRef(this->clazz);
        }
    }

    java_class& java_class::operator = (const java_class& other) {
        this->classname = other.classname;

        if (this->clazz != nullptr) {
            JNIOEnv->DeleteWeakGlobalRef(this->clazz);
        }
        this->clazz = (jclass) JNIOEnv->NewWeakGlobalRef(other.clazz);

        return *this;
    }

    value java_class::call(const java_static_method& jsm, std::initializer_list<value> args) const {
        value r;

        switch (jsm.get_signature().return_type().string()[0]) {
            case 'Z' : {
                if (args.size() != 0) {
                    r = JNIOEnv->CallStaticBooleanMethodA(this->clazz, jsm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = JNIOEnv->CallStaticBooleanMethod(this->clazz, jsm.getJMethod());
                }
                break;
            }
            case 'B' : {
                if (args.size() != 0) {
                    r = JNIOEnv->CallStaticByteMethodA(this->clazz, jsm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = JNIOEnv->CallStaticByteMethod(this->clazz, jsm.getJMethod());
                }
                break;
            }
            case 'S' : {
                if (args.size() != 0) {
                    r = JNIOEnv->CallStaticShortMethodA(this->clazz, jsm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = JNIOEnv->CallStaticShortMethod(this->clazz, jsm.getJMethod());
                }
                break;
            }
            case 'C' : {
                if (args.size() != 0) {
                    r = JNIOEnv->CallStaticCharMethodA(this->clazz, jsm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = JNIOEnv->CallStaticCharMethod(this->clazz, jsm.getJMethod());
                }
                break;
            }
            case 'I' : {
                if (args.size() != 0) {
                    r = JNIOEnv->CallStaticIntMethodA(this->clazz, jsm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = JNIOEnv->CallStaticIntMethod(this->clazz, jsm.getJMethod());
                }
                break;
            }
            case 'J' : {
                if (args.size() != 0) {
                    r = JNIOEnv->CallStaticLongMethodA(this->clazz, jsm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = JNIOEnv->CallStaticLongMethod(this->clazz, jsm.getJMethod());
                }
                break;
            }
            case 'F' : {
                if (args.size() != 0) {
                    r = JNIOEnv->CallStaticFloatMethodA(this->clazz, jsm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = JNIOEnv->CallStaticFloatMethod(this->clazz, jsm.getJMethod());
                }
                break;
            }
            case 'D' : {
                if (args.size() != 0) {
                    r = JNIOEnv->CallStaticDoubleMethodA(this->clazz, jsm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = JNIOEnv->CallStaticDoubleMethod(this->clazz, jsm.getJMethod());
                }
                break;
            }
            case 'V' : {
                if (args.size() != 0) {
                    JNIOEnv->CallStaticVoidMethodA(this->clazz, jsm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    JNIOEnv->CallStaticVoidMethod(this->clazz, jsm.getJMethod());
                }
                break;
            }
            default : {
                if (args.size() != 0) {
                    r = JNIOEnv->CallStaticObjectMethodA(this->clazz, jsm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = JNIOEnv->CallStaticObjectMethod(this->clazz, jsm.getJMethod());
                }
                break;
            }
        }

        if (JNIOEnv->ExceptionCheck()) {
            JNIOEnv->ExceptionDescribe();
            throw jnio_exception("An error occurred.");
        }
        return r;
    }

    value java_class::access(const java_static_field& jsf) const {
        const char id = jsf.get_signature()[0];
        value r;

        switch (id) {
            case 'Z' : {
                r = JNIOEnv->GetStaticBooleanField(this->clazz, jsf.get_jfield());
                break;
            }
            case 'B' : {
                r = JNIOEnv->GetStaticByteField(this->clazz, jsf.get_jfield());
                break;
            }
            case 'S' : {
                r = JNIOEnv->GetStaticShortField(this->clazz, jsf.get_jfield());
                break;
            }
            case 'C' : {
                r = JNIOEnv->GetStaticCharField(this->clazz, jsf.get_jfield());
                break;
            }
            case 'I' : {
                r = JNIOEnv->GetStaticIntField(this->clazz, jsf.get_jfield());
                break;
            }
            case 'J' : {
                r = JNIOEnv->GetStaticLongField(this->clazz, jsf.get_jfield());
                break;
            }
            case 'F' : {
                r = JNIOEnv->GetStaticFloatField(this->clazz, jsf.get_jfield());
                break;
            }
            case 'D' : {
                r = JNIOEnv->GetStaticDoubleField(this->clazz, jsf.get_jfield());
                break;
            }
            default : {
                r = JNIOEnv->GetStaticObjectField(this->clazz, jsf.get_jfield());
                break;
            }
        }

        if (JNIOEnv->ExceptionCheck()) {
            JNIOEnv->ExceptionDescribe();
            throw jnio_exception("An error occurred.");
        }
        return r;
    }

    void java_class::edit(const java_static_field& jsf, const value& value) const {
        const char id = jsf.get_signature()[0];

        switch (id) {
            case 'Z' : {
                JNIOEnv->SetStaticBooleanField(this->clazz, jsf.get_jfield(), value);
                break;
            }
            case 'B' : {
                JNIOEnv->SetStaticByteField(this->clazz, jsf.get_jfield(), value);
                break;
            }
            case 'S' : {
                JNIOEnv->SetStaticShortField(this->clazz, jsf.get_jfield(), value);
                break;
            }
            case 'C' : {
                JNIOEnv->SetStaticCharField(this->clazz, jsf.get_jfield(), value);
                break;
            }
            case 'I' : {
                JNIOEnv->SetStaticIntField(this->clazz, jsf.get_jfield(), value);
                break;
            }
            case 'J' : {
                JNIOEnv->SetStaticLongField(this->clazz, jsf.get_jfield(), value);
                break;
            }
            case 'F' : {
                JNIOEnv->SetStaticFloatField(this->clazz, jsf.get_jfield(), value);
                break;
            }
            case 'D' : {
                JNIOEnv->SetStaticDoubleField(this->clazz, jsf.get_jfield(), value);
                break;
            }
            default : {
                JNIOEnv->SetStaticObjectField(this->clazz, jsf.get_jfield(), value);
                break;
            }
        }

        if (JNIOEnv->ExceptionCheck()) {
            JNIOEnv->ExceptionDescribe();
            throw jnio_exception("An error occurred.");
        }
    }

    java_class::operator const jclass&() const noexcept {
        return this->clazz;
    }

    jclass java_class::getJClass() const noexcept {
        return (jclass) JNIOEnv->NewLocalRef(this->clazz);
    }

    java_object java_class::as_object() const noexcept {
        return java_object(this->clazz);
    }

    java_method java_class::getMethod(const char* name, const sign::method& ms) const {
        if (name == nullptr) {
            throw std::invalid_argument("Unable to find any java_method from a nullptr.");
        }
        return java_method(name, *this, ms);
    }

    java_static_method java_class::getStaticMethod(const char* name, const sign::method& ms) const {
        if (name == nullptr) {
            throw std::invalid_argument("Unable to find any java_static_method from a nullptr.");
        }
        return java_static_method(name, *this, ms);
    }

    java_constructor java_class::getConstructor(const sign::constructor& cs) const {
        return java_constructor(*this, cs);
    }

    java_field java_class::getField(const char* name, const sign::field& fs) {
        if (name == nullptr) {
            throw std::invalid_argument("Unable to find any java_field from a nullptr.");
        }
        return java_field(name, *this, fs);
    }

    java_static_field java_class::getStaticField(const char* name, const sign::field& fs) {
        if (name == nullptr) {
            throw std::invalid_argument("Unable to find any java_static_field from a nullptr.");
        }
        return java_static_field(name, *this, fs);
    }

    bool java_class::isArray() const noexcept {
        return this->classname[0] == '[';
    }

    bool java_class::extends(const jclass& clazz) const noexcept {
        return JNIOEnv->IsAssignableFrom(this->clazz, clazz);
    }

    java_class java_class::arrayType(size_t level) const {
        if (level == 0) {
            throw std::invalid_argument("Unable to obtain 0-dimensional arrays.");
        }

		if (this->isArray()) {
			std::string name = '[' + this->classname;
			return java_class(name);
		}

		std::string name('[', level);
		name += 'L';
		name += this->classname;
		name += ';';

        return java_class(name);
    }

    java_class java_class::componentType() const noexcept {
        if (this->classname[0] == '[') {
			if (this->classname[1] == '[') {
				return java_class(this->classname.substr(1));
			}

			std::string name = this->classname.substr(2);
			return java_class(this->classname.substr(0, this->classname.size()-1));
        }

		return *this;
    }

	java_class java_class::baseType() const noexcept {
        if (this->classname[0] == '[') {
			std::string name = this->classname.substr(this->classname.find_first_of('L')+1);
			return java_class(this->classname.substr(0, this->classname.size()-1));
        }

		return *this;
    }

    const std::string& java_class::string() const noexcept {
        return this->classname;
    }

    bool java_class::operator == (const java_class& other) const noexcept {
        return this->classname == other.classname;
    }
}
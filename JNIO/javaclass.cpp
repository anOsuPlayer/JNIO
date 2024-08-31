#include "javaclass.hpp"
#include "javamethod.hpp"

namespace jnio {

	static jmethodID GET_CLASS;

	static jmethodID GET_NAME;

    java_class::java_class(JNIEnv* env, jclass clazz) {
		this->env = env;
        this->clazz = (jclass) env->NewWeakGlobalRef(clazz);

        if (GET_CLASS == nullptr) {
			GET_CLASS = env->GetMethodID(clazz, "getClass", "()Ljava/lang/Class;");
		}

		jclass thisClass = (jclass) env->CallObjectMethod(clazz, GET_CLASS);

		if (GET_NAME == nullptr) {
			GET_NAME = env->GetMethodID(thisClass, "getName", "()Ljava/lang/String;");
		}

		jstring name = (jstring) env->CallObjectMethod(thisClass, GET_NAME);

        const char* str = env->GetStringUTFChars(name, 0);
        this->classname = str;

        env->ReleaseStringUTFChars(name, str);
        env->DeleteLocalRef(name);
        env->DeleteLocalRef(thisClass);
    }

    java_class::java_class(JNIEnv* env, const std::string& classname) {
		this->env = env;
		this->classname = classname;
		for (size_t i = 0; i < this->classname.size(); i++) {
            this->classname[i] = (this->classname[i] == '.') ? '/' : this->classname[i];
        }

        jclass c = env->FindClass(this->classname.c_str());

        if (c == nullptr) {
            throw no_such_class();
        }
        this->clazz = (jclass) env->NewWeakGlobalRef(c);
        env->DeleteLocalRef(c);
    }
	
    java_class::java_class(JNIEnv* env, const java_package& pack, const std::string& classname) {
		this->env;

        this->classname = pack.string();
		this->classname += '/';
		this->classname += classname;
		for (size_t i = 0; i < this->classname.size(); i++) {
            this->classname[i] = (this->classname[i] == '.') ? '/' : this->classname[i];
        }

        jclass c = env->FindClass(this->classname.c_str());

        if (c == nullptr) {
            throw no_such_class();
        }
        this->clazz = (jclass) env->NewWeakGlobalRef(c);

        env->DeleteLocalRef(c);
    }

    java_class::java_class(const java_class& clazz) {
		this->env = clazz.env;
        this->classname = clazz.classname;
        this->clazz = (jclass) env->NewWeakGlobalRef(clazz.clazz);
    }

    java_class::~java_class() {
        if (this->clazz != nullptr) {
            env->DeleteWeakGlobalRef(this->clazz);
        }
    }

    java_class& java_class::operator = (const java_class& other) {
        this->classname = other.classname;

        if (this->clazz != nullptr) {
            env->DeleteWeakGlobalRef(this->clazz);
        }
        this->clazz = (jclass) env->NewWeakGlobalRef(other.clazz);

        return *this;
    }

    value java_class::call(const java_static_method& jsm, std::initializer_list<value> args) const {
        value r;

        switch (jsm.getSignature().returnType().string()[0]) {
            case 'Z' : {
                if (args.size() != 0) {
                    r = env->CallStaticBooleanMethodA(this->clazz, jsm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = env->CallStaticBooleanMethod(this->clazz, jsm.getJMethod());
                }
                break;
            }
            case 'B' : {
                if (args.size() != 0) {
                    r = env->CallStaticByteMethodA(this->clazz, jsm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = env->CallStaticByteMethod(this->clazz, jsm.getJMethod());
                }
                break;
            }
            case 'S' : {
                if (args.size() != 0) {
                    r = env->CallStaticShortMethodA(this->clazz, jsm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = env->CallStaticShortMethod(this->clazz, jsm.getJMethod());
                }
                break;
            }
            case 'C' : {
                if (args.size() != 0) {
                    r = env->CallStaticCharMethodA(this->clazz, jsm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = env->CallStaticCharMethod(this->clazz, jsm.getJMethod());
                }
                break;
            }
            case 'I' : {
                if (args.size() != 0) {
                    r = env->CallStaticIntMethodA(this->clazz, jsm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = env->CallStaticIntMethod(this->clazz, jsm.getJMethod());
                }
                break;
            }
            case 'J' : {
                if (args.size() != 0) {
                    r = env->CallStaticLongMethodA(this->clazz, jsm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = env->CallStaticLongMethod(this->clazz, jsm.getJMethod());
                }
                break;
            }
            case 'F' : {
                if (args.size() != 0) {
                    r = env->CallStaticFloatMethodA(this->clazz, jsm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = env->CallStaticFloatMethod(this->clazz, jsm.getJMethod());
                }
                break;
            }
            case 'D' : {
                if (args.size() != 0) {
                    r = env->CallStaticDoubleMethodA(this->clazz, jsm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = env->CallStaticDoubleMethod(this->clazz, jsm.getJMethod());
                }
                break;
            }
            case 'V' : {
                if (args.size() != 0) {
                    env->CallStaticVoidMethodA(this->clazz, jsm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    env->CallStaticVoidMethod(this->clazz, jsm.getJMethod());
                }
                break;
            }
            default : {
                if (args.size() != 0) {
                    r = env->CallStaticObjectMethodA(this->clazz, jsm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = env->CallStaticObjectMethod(this->clazz, jsm.getJMethod());
                }
                break;
            }
        }

        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            throw jnio_exception("An error occurred.");
        }
        return r;
    }

    value java_class::access(const java_static_field& jsf) const {
        const char id = jsf.getSignature()[0];
        value r;

        switch (id) {
            case 'Z' : {
                r = env->GetStaticBooleanField(this->clazz, jsf.getJField());
                break;
            }
            case 'B' : {
                r = env->GetStaticByteField(this->clazz, jsf.getJField());
                break;
            }
            case 'S' : {
                r = env->GetStaticShortField(this->clazz, jsf.getJField());
                break;
            }
            case 'C' : {
                r = env->GetStaticCharField(this->clazz, jsf.getJField());
                break;
            }
            case 'I' : {
                r = env->GetStaticIntField(this->clazz, jsf.getJField());
                break;
            }
            case 'J' : {
                r = env->GetStaticLongField(this->clazz, jsf.getJField());
                break;
            }
            case 'F' : {
                r = env->GetStaticFloatField(this->clazz, jsf.getJField());
                break;
            }
            case 'D' : {
                r = env->GetStaticDoubleField(this->clazz, jsf.getJField());
                break;
            }
            default : {
                r = env->GetStaticObjectField(this->clazz, jsf.getJField());
                break;
            }
        }

        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            throw jnio_exception("An error occurred.");
        }
        return r;
    }

    void java_class::edit(const java_static_field& jsf, const value& value) const {
        const char id = jsf.getSignature()[0];

        switch (id) {
            case 'Z' : {
                env->SetStaticBooleanField(this->clazz, jsf.getJField(), value);
                break;
            }
            case 'B' : {
                env->SetStaticByteField(this->clazz, jsf.getJField(), value);
                break;
            }
            case 'S' : {
                env->SetStaticShortField(this->clazz, jsf.getJField(), value);
                break;
            }
            case 'C' : {
                env->SetStaticCharField(this->clazz, jsf.getJField(), value);
                break;
            }
            case 'I' : {
                env->SetStaticIntField(this->clazz, jsf.getJField(), value);
                break;
            }
            case 'J' : {
                env->SetStaticLongField(this->clazz, jsf.getJField(), value);
                break;
            }
            case 'F' : {
                env->SetStaticFloatField(this->clazz, jsf.getJField(), value);
                break;
            }
            case 'D' : {
                env->SetStaticDoubleField(this->clazz, jsf.getJField(), value);
                break;
            }
            default : {
                env->SetStaticObjectField(this->clazz, jsf.getJField(), value);
                break;
            }
        }

        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            throw jnio_exception("An error occurred.");
        }
    }

    java_class::operator const jclass&() const noexcept {
        return this->clazz;
    }

    jclass java_class::getJClass() const noexcept {
        return (jclass) env->NewLocalRef(this->clazz);
    }

    java_object java_class::as_object() const noexcept {
        return java_object(this->env, this->clazz);
    }

    java_method java_class::getMethod(const char* name, const sign::method& ms) const {
        if (name == nullptr) {
            throw std::invalid_argument("Unable to find any java_method from a nullptr.");
        }
        return java_method(this->env, name, *this, ms);
    }

    java_static_method java_class::getStaticMethod(const char* name, const sign::method& ms) const {
        if (name == nullptr) {
            throw std::invalid_argument("Unable to find any java_static_method from a nullptr.");
        }
        return java_static_method(this->env, name, *this, ms);
    }

    java_constructor java_class::getConstructor(const sign::constructor& cs) const {
        return java_constructor(this->env, *this, cs);
    }

    java_field java_class::getField(const char* name, const sign::field& fs) {
        if (name == nullptr) {
            throw std::invalid_argument("Unable to find any java_field from a nullptr.");
        }
        return java_field(this->env, name, *this, fs);
    }

    java_static_field java_class::getStaticField(const char* name, const sign::field& fs) {
        if (name == nullptr) {
            throw std::invalid_argument("Unable to find any java_static_field from a nullptr.");
        }
        return java_static_field(this->env, name, *this, fs);
    }

    bool java_class::isArray() const noexcept {
        return this->classname[0] == '[';
    }

    bool java_class::extends(const jclass& clazz) const noexcept {
        return env->IsAssignableFrom(this->clazz, clazz);
    }

    java_class java_class::arrayType(size_t level) const {
        if (level == 0) {
            throw std::invalid_argument("Unable to obtain 0-dimensional arrays.");
        }

		if (this->isArray()) {
			std::string name = '[' + this->classname;
			return java_class(this->env, name);
		}

		std::string name('[', level);
		name += 'L';
		name += this->classname;
		name += ';';

        return java_class(this->env, name);
    }

    java_class java_class::componentType() const noexcept {
        if (this->classname[0] == '[') {
			if (this->classname[1] == '[') {
				return java_class(this->env, this->classname.substr(1));
			}

			std::string name = this->classname.substr(2);
			return java_class(this->env, this->classname.substr(0, this->classname.size()-1));
        }

		return *this;
    }

	java_class java_class::baseType() const noexcept {
        if (this->classname[0] == '[') {
			std::string name = this->classname.substr(this->classname.find_first_of('L')+1);
			return java_class(this->env, this->classname.substr(0, this->classname.size()-1));
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
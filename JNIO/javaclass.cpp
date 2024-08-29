#include "javaclass.hpp"
#include "javamethod.hpp"

namespace jnio {

	static jmethodID GET_CLASS;

	static jmethodID GET_NAME;

    JavaClass::JavaClass(JNIEnv* env, jclass clazz) {
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

    JavaClass::JavaClass(JNIEnv* env, const std::string& classname) {
		this->env = env;
		this->classname = classname;
		for (size_t i = 0; i < this->classname.size(); i++) {
            this->classname[i] = (this->classname[i] == '.') ? '/' : this->classname[i];
        }

        jclass c = env->FindClass(this->classname.c_str());

        if (c == nullptr) {
            throw NoSuchClassException();
        }
        this->clazz = (jclass) env->NewWeakGlobalRef(c);
        env->DeleteLocalRef(c);
    }
	
    JavaClass::JavaClass(JNIEnv* env, const JavaPackage& pack, const std::string& classname) {
		this->env;

        this->classname = pack.string();
		this->classname += '/';
		this->classname += classname;
		for (size_t i = 0; i < this->classname.size(); i++) {
            this->classname[i] = (this->classname[i] == '.') ? '/' : this->classname[i];
        }

        jclass c = env->FindClass(this->classname.c_str());

        if (c == nullptr) {
            throw NoSuchClassException();
        }
        this->clazz = (jclass) env->NewWeakGlobalRef(c);

        env->DeleteLocalRef(c);
    }

    JavaClass::JavaClass(const JavaClass& clazz) {
		this->env = clazz.env;
        this->classname = clazz.classname;
        this->clazz = (jclass) env->NewWeakGlobalRef(clazz.clazz);
    }

    JavaClass::~JavaClass() {
        if (this->clazz != nullptr) {
            env->DeleteWeakGlobalRef(this->clazz);
        }
    }

    JavaClass& JavaClass::operator = (const JavaClass& other) {
        this->classname = other.classname;

        if (this->clazz != nullptr) {
            env->DeleteWeakGlobalRef(this->clazz);
        }
        this->clazz = (jclass) env->NewWeakGlobalRef(other.clazz);

        return *this;
    }

    JValue JavaClass::call(const JavaStaticMethod& jsm, std::initializer_list<JValue> args) const {
        JValue r;

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

    JValue JavaClass::access(const JavaStaticField& jsf) const {
        const char id = jsf.getSignature()[0];
        JValue r;

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

    void JavaClass::edit(const JavaStaticField& jsf, const JValue& value) const {
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

    JavaClass::operator const jclass&() const noexcept {
        return this->clazz;
    }

    jclass JavaClass::getJClass() const noexcept {
        return (jclass) env->NewLocalRef(this->clazz);
    }

    JavaObject JavaClass::asObject() const noexcept {
        return JavaObject(this->env, this->clazz);
    }

    JavaMethod JavaClass::getMethod(const char* name, const sign::Method& ms) const {
        if (name == nullptr) {
            throw std::invalid_argument("Unable to find any JavaMethod from a nullptr.");
        }
        return JavaMethod(this->env, name, *this, ms);
    }

    JavaStaticMethod JavaClass::getStaticMethod(const char* name, const sign::Method& ms) const {
        if (name == nullptr) {
            throw std::invalid_argument("Unable to find any JavaStaticMethod from a nullptr.");
        }
        return JavaStaticMethod(this->env, name, *this, ms);
    }

    JavaConstructor JavaClass::getConstructor(const sign::Constructor& cs) const {
        return JavaConstructor(this->env, *this, cs);
    }

    JavaField JavaClass::getField(const char* name, const sign::Field& fs) {
        if (name == nullptr) {
            throw std::invalid_argument("Unable to find any JavaField from a nullptr.");
        }
        return JavaField(this->env, name, *this, fs);
    }

    JavaStaticField JavaClass::getStaticField(const char* name, const sign::Field& fs) {
        if (name == nullptr) {
            throw std::invalid_argument("Unable to find any JavaStaticField from a nullptr.");
        }
        return JavaStaticField(this->env, name, *this, fs);
    }

    bool JavaClass::isArray() const noexcept {
        return this->classname[0] == '[';
    }

    bool JavaClass::extends(const jclass& clazz) const noexcept {
        return env->IsAssignableFrom(this->clazz, clazz);
    }

    JavaClass JavaClass::arrayType(size_t level) const {
        if (level == 0) {
            throw std::invalid_argument("Unable to obtain 0-dimensional arrays.");
        }

		if (this->isArray()) {
			std::string name = '[' + this->classname;
			return JavaClass(this->env, name);
		}

		std::string name('[', level);
		name += 'L';
		name += this->classname;
		name += ';';

        return JavaClass(this->env, name);
    }

    JavaClass JavaClass::componentType() const noexcept {
        if (this->classname[0] == '[') {
			if (this->classname[1] == '[') {
				return JavaClass(this->env, this->classname.substr(1));
			}

			std::string name = this->classname.substr(2);
			return JavaClass(this->env, this->classname.substr(0, this->classname.size()-1));
        }

		return *this;
    }

	JavaClass JavaClass::baseType() const noexcept {
        if (this->classname[0] == '[') {
			std::string name = this->classname.substr(this->classname.find_first_of('L')+1);
			return JavaClass(this->env, this->classname.substr(0, this->classname.size()-1));
        }

		return *this;
    }

    const std::string& JavaClass::string() const noexcept {
        return this->classname;
    }

    bool JavaClass::operator == (const JavaClass& other) const noexcept {
        return this->classname == other.classname;
    }
}
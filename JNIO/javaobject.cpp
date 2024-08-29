#include "javaobject.hpp"

namespace jnio {

    JavaObject::JavaObject(JNIEnv* env, const jobject& obj) {
        this->env = env;
        this->obj = env->NewWeakGlobalRef(obj);
    }

    JavaObject::~JavaObject() {
        if (this->obj != nullptr) {
            env->DeleteWeakGlobalRef(this->obj);
        }
    }

	JavaObject::JavaObject(const JavaObject& obj) {
        this->env = obj.env;
		this->obj = env->NewWeakGlobalRef(obj.obj);
    }

	JavaObject& JavaObject::operator = (const JavaObject& other) {
        if (this->obj != nullptr) {
            env->DeleteWeakGlobalRef(this->obj);
        }
		this->env = other.env;
        this->obj = env->NewWeakGlobalRef(other);
        
        return *this;
    }

    JavaObject& JavaObject::operator = (const jobject& other) {
        if (this->obj != nullptr) {
            env->DeleteWeakGlobalRef(this->obj);
        }
        this->obj = env->NewWeakGlobalRef(other);
        
        return *this;
    }

    JValue JavaObject::_call(JNIEnv* env, jobject obj, const JavaMethod& jm, std::initializer_list<JValue> args) {
        sign::Signature ret = jm.getSignature().returnType();
        JValue r;

        switch (ret[0]) {
            case 'Z' : {
                if (args.size() == 0) {
                    r = env->CallBooleanMethodA(obj, jm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = env->CallBooleanMethod(obj, jm.getJMethod());
                }
                break;
            }
            case 'B' : {
                if (args.size() == 0) {
                    r = env->CallByteMethodA(obj, jm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = env->CallByteMethod(obj, jm.getJMethod());
                }
                break;
            }
            case 'S' : {
                if (args.size() == 0) {
                    r = env->CallShortMethodA(obj, jm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = env->CallShortMethod(obj, jm.getJMethod());
                }
                break;
            }
            case 'C' : {
                if (args.size() == 0) {
                    r = env->CallCharMethodA(obj, jm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = env->CallCharMethod(obj, jm.getJMethod());
                }
                break;
            }
            case 'I' : {
                if (args.size() == 0) {
                    r = env->CallIntMethodA(obj, jm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = env->CallIntMethod(obj, jm.getJMethod());
                }
                break;
            }
            case 'J' : {
                if (args.size() == 0) {
                    r = env->CallLongMethodA(obj, jm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = env->CallLongMethod(obj, jm.getJMethod());
                }
                break;
            }
            case 'F' : {
                if (args.size() == 0) {
                    r = env->CallFloatMethodA(obj, jm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = env->CallFloatMethod(obj, jm.getJMethod());
                }
                break;
            }
            case 'D' : {
                if (args.size() == 0) {
                    r = env->CallDoubleMethodA(obj, jm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = env->CallDoubleMethod(obj, jm.getJMethod());
                }
                break;
            }
            case 'V' : {
                if (args.size() == 0) {
                    env->CallVoidMethodA(obj, jm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    env->CallVoidMethod(obj, jm.getJMethod());
                }
                break;
            }
            default : {
                if (args.size() == 0) {
                    r = env->CallObjectMethodA(obj, jm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = env->CallObjectMethod(obj, jm.getJMethod());
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

    JValue JavaObject::call(const JavaMethod& jm, std::initializer_list<JValue> args) const {
        return JavaObject::_call(this->env, this->obj, jm, args);
    }

    JValue JavaObject::_access(JNIEnv* env, jobject obj, const JavaField& jf) {
        const char id = jf.getSignature()[0];
        JValue r;

        switch (id) {
            case 'Z' : {
                r = env->GetBooleanField(obj, jf.getJField());
                break;
            }
            case 'B' : {
                r = env->GetByteField(obj, jf.getJField());
                break;
            }
            case 'S' : {
                r = env->GetShortField(obj, jf.getJField());
                break;
            }
            case 'C' : {
                r = env->GetCharField(obj, jf.getJField());
                break;
            }
            case 'I' : {
                r = env->GetIntField(obj, jf.getJField());
                break;
            }
            case 'J' : {
                r = env->GetLongField(obj, jf.getJField());
                break;
            }
            case 'F' : {
                r = env->GetFloatField(obj, jf.getJField());
                break;
            }
            case 'D' : {
                r = env->GetDoubleField(obj, jf.getJField());
                break;
            }
            default : {
                r = env->GetObjectField(obj, jf.getJField());
                break;
            }
        }

        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            throw jnio_exception("An error occurred.");
        }
        return r;
    }

    JValue JavaObject::access(const JavaField& jf) const {
        return JavaObject::_access(this->env, this->obj, jf);
    }

    void JavaObject::_edit(JNIEnv* env, jobject obj, const JavaField& jf, const JValue& value) {
        const char id = jf.getSignature()[0];

        switch (id) {
            case 'Z' : {
                env->SetBooleanField(obj, jf.getJField(), value);
                break;
            }
            case 'B' : {
                env->SetByteField(obj, jf.getJField(), value);
                break;
            }
            case 'S' : {
                env->SetShortField(obj, jf.getJField(), value);
                break;
            }
            case 'C' : {
                env->SetCharField(obj, jf.getJField(), value);
                break;
            }
            case 'I' : {
                env->SetIntField(obj, jf.getJField(), value);
                break;
            }
            case 'J' : {
                env->SetLongField(obj, jf.getJField(), value);
                break;
            }
            case 'F' : {
                env->SetFloatField(obj, jf.getJField(), value);
                break;
            }
            case 'D' : {
                env->SetDoubleField(obj, jf.getJField(), value);
                break;
            }
            default : {
                env->SetObjectField(obj, jf.getJField(), value);
                break;
            }
        }

        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            throw jnio_exception("An error occurred.");
        }
    }

    void JavaObject::edit(const JavaField& jf, const JValue& value) {
        return JavaObject::_edit(this->env, this->obj, jf, value);
    }

    JavaClass JavaObject::getClass() const {
        if (this->getJObject() == nullptr) {
            throw std::invalid_argument("Unable to call .getClass() method on a null JavaObject.");
        }

        return JavaClass(this->env, env->GetObjectClass(this->obj));
    }

    JavaObject::operator const jobject&() const noexcept {
        return this->obj;
    }

    jobject JavaObject::getJObject() const noexcept {
        return env->NewLocalRef(this->obj);
    }

	static jmethodID TO_STRING;

    std::string JavaObject::string() const noexcept {
        jclass clazz = env->GetObjectClass(this->obj);

		if (TO_STRING == nullptr) {
			TO_STRING = env->GetMethodID(clazz, "toString", sign::TO_STRING);
		}

        JavaString str(this->env, (jstring) env->CallObjectMethod(this->obj, TO_STRING));
        std::string res = str.string();
        env->DeleteLocalRef(clazz);

        return res;
    }

	const char* JavaObject::c_str() const noexcept {
        return this->string().c_str();
    }

	static jmethodID EQUALS;

    bool JavaObject::operator == (const jobject& other) const noexcept {
        jclass clazz = env->GetObjectClass(this->obj);
        
		if (EQUALS == nullptr) {
			EQUALS = env->GetMethodID(clazz, "equals", sign::EQUALS);
		}

        jboolean res = env->CallBooleanMethod(this->obj, EQUALS, obj);
        bool eq = (res == 1) ? true : false;
        env->DeleteLocalRef(clazz);

        return eq;
    }
	
    bool JavaObject::sameType(const jobject& obj) const noexcept {
        return (env->IsInstanceOf(this->obj, env->GetObjectClass(obj)) == 0 ? false : true);
    }

    bool JavaObject::isInstanceof(const jclass& clazz) const noexcept {
        return (env->IsInstanceOf(this->obj, clazz) == 0 ? false : true);
    }

    JavaObjectArrayElement::JavaObjectArrayElement(JavaObjectArray* ref, size_t refIndex)
		: JavaObject(ref->env, env->GetObjectArrayElement(ref->arr, refIndex)) {
        this->ref = ref;
		this->refIndex = refIndex;
    }

    JavaObjectArrayElement::~JavaObjectArrayElement() {
        if (this->hasChanged) {
            env->SetObjectArrayElement(this->ref->arr, this->refIndex, this->obj);
        }
    }

	JavaObjectArrayElement& JavaObjectArrayElement::operator = (const JavaObject& obj) {
        this->hasChanged = true;
        if (this->obj != nullptr) {
            env->DeleteWeakGlobalRef(this->obj);
        }
        this->obj = env->NewWeakGlobalRef(obj);
        
        return *this;
    }

    JavaObjectArrayElement& JavaObjectArrayElement::operator = (const jobject& obj) {
        this->hasChanged = true;
        if (this->obj != nullptr) {
            env->DeleteWeakGlobalRef(this->obj);
        }
        this->obj = env->NewWeakGlobalRef(obj);
        
        return *this;
    }

    JavaObjectArray::JavaObjectArray(JNIEnv* env, const jobjectArray& arr) {
        this->env = env;
        this->arr = (jobjectArray) env->NewWeakGlobalRef(arr);
    }

    JavaObjectArray::JavaObjectArray(const JavaObjectArray& arr) {
		this->env = env;
        this->arr = (jobjectArray) env->NewWeakGlobalRef(arr.arr);
    }

	JavaObjectArray& JavaObjectArray::operator = (const jobjectArray& arr) {
        if (this->arr != nullptr) {
            env->DeleteWeakGlobalRef(this->arr);
        }
        this->arr = (jobjectArray) env->NewWeakGlobalRef(arr);

        return *this;
    }

	JavaObjectArray& JavaObjectArray::operator = (const JavaObjectArray& arr) {
        if (this->arr != nullptr) {
            env->DeleteWeakGlobalRef(this->arr);
        }
        this->env = arr.env;
        this->arr = (jobjectArray) env->NewWeakGlobalRef(arr);

        return *this;
    }

    JavaObjectArray::~JavaObjectArray() {
        if (this->currentElement != nullptr) {
            delete this->currentElement;
        }

		if (this->arr != nullptr) {
			env->DeleteWeakGlobalRef(this->arr);
		}
    }

    JavaObjectArray::operator const jobjectArray&() const noexcept {
        return this->arr;
    }

    jobjectArray JavaObjectArray::getJObjectArray() const noexcept {
        return (jobjectArray) env->NewLocalRef(this->arr);
    }

    JavaObject JavaObjectArray::asObject() const noexcept {
        return JavaObject(this->env, this->arr);
    }

    JavaObjectArrayElement& JavaObjectArray::operator [] (size_t index) {
        if (index >= this->length()) {
            throw std::out_of_range("The given index goes out of bounds for this JavaObjectArray.");
        }

        if (this->currentElement != nullptr) {
            delete this->currentElement;
        }
        this->currentElement = new JavaObjectArrayElement(this, index);
        
        return *this->currentElement;
    }

    size_t JavaObjectArray::length() const noexcept {
        return env->GetArrayLength(this->arr);
    }

	static JavaStaticMethod PRINT_ARRAY;

	static JavaStaticMethod ARRAY_EQUALS;

    std::string JavaObjectArray::string() const noexcept {
        if (PRINT_ARRAY.string().empty()) {
            JavaClass clazz(this->env, "java/util/Arrays");
            PRINT_ARRAY = JavaStaticMethod(this->env, "toString", clazz,
				sign::Method(sign::STRING, { sign::OBJECT_ARRAY }));
        }

        JavaString str(this->env, (jstring) PRINT_ARRAY.call({ this->arr }));
        return str.string();
    }

    bool JavaObjectArray::operator == (const jobjectArray& arr) const noexcept {
        if (ARRAY_EQUALS.string().empty()) {
            JavaClass clazz(this->env, "java/util/Arrays");
            ARRAY_EQUALS = JavaStaticMethod(this->env, "equals", clazz, 
				sign::Method(sign::BOOLEAN, { sign::OBJECT_ARRAY, sign::OBJECT_ARRAY}));
        }

        bool eq = ((jboolean) ARRAY_EQUALS.call({ this->arr, arr }) == 1) ? true : false;
        return eq;
    }
}
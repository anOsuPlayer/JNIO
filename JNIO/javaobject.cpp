#include "javaobject.hpp"

namespace jnio {

    java_object::java_object(JNIEnv* env, const jobject& obj) {
        this->env = env;
        this->obj = env->NewWeakGlobalRef(obj);
    }

    java_object::~java_object() {
        if (this->obj != nullptr) {
            env->DeleteWeakGlobalRef(this->obj);
        }
    }

	java_object::java_object(const java_object& obj) {
        this->env = obj.env;
		this->obj = env->NewWeakGlobalRef(obj.obj);
    }

	java_object& java_object::operator = (const java_object& other) {
        if (this->obj != nullptr) {
            env->DeleteWeakGlobalRef(this->obj);
        }
		this->env = other.env;
        this->obj = env->NewWeakGlobalRef(other);
        
        return *this;
    }

    java_object& java_object::operator = (const jobject& other) {
        if (this->obj != nullptr) {
            env->DeleteWeakGlobalRef(this->obj);
        }
        this->obj = env->NewWeakGlobalRef(other);
        
        return *this;
    }

    value java_object::_call(JNIEnv* env, jobject obj, const java_method& jm, std::initializer_list<value> args) {
        sign::signature ret = jm.get_signature().return_type();
        value r;

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

    value java_object::call(const java_method& jm, std::initializer_list<value> args) const {
        return java_object::_call(this->env, this->obj, jm, args);
    }

    value java_object::_access(JNIEnv* env, jobject obj, const java_field& jf) {
        const char id = jf.get_signature()[0];
        value r;

        switch (id) {
            case 'Z' : {
                r = env->GetBooleanField(obj, jf.get_jfield());
                break;
            }
            case 'B' : {
                r = env->GetByteField(obj, jf.get_jfield());
                break;
            }
            case 'S' : {
                r = env->GetShortField(obj, jf.get_jfield());
                break;
            }
            case 'C' : {
                r = env->GetCharField(obj, jf.get_jfield());
                break;
            }
            case 'I' : {
                r = env->GetIntField(obj, jf.get_jfield());
                break;
            }
            case 'J' : {
                r = env->GetLongField(obj, jf.get_jfield());
                break;
            }
            case 'F' : {
                r = env->GetFloatField(obj, jf.get_jfield());
                break;
            }
            case 'D' : {
                r = env->GetDoubleField(obj, jf.get_jfield());
                break;
            }
            default : {
                r = env->GetObjectField(obj, jf.get_jfield());
                break;
            }
        }

        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            throw jnio_exception("An error occurred.");
        }
        return r;
    }

    value java_object::access(const java_field& jf) const {
        return java_object::_access(this->env, this->obj, jf);
    }

    void java_object::_edit(JNIEnv* env, jobject obj, const java_field& jf, const value& value) {
        const char id = jf.get_signature()[0];

        switch (id) {
            case 'Z' : {
                env->SetBooleanField(obj, jf.get_jfield(), value);
                break;
            }
            case 'B' : {
                env->SetByteField(obj, jf.get_jfield(), value);
                break;
            }
            case 'S' : {
                env->SetShortField(obj, jf.get_jfield(), value);
                break;
            }
            case 'C' : {
                env->SetCharField(obj, jf.get_jfield(), value);
                break;
            }
            case 'I' : {
                env->SetIntField(obj, jf.get_jfield(), value);
                break;
            }
            case 'J' : {
                env->SetLongField(obj, jf.get_jfield(), value);
                break;
            }
            case 'F' : {
                env->SetFloatField(obj, jf.get_jfield(), value);
                break;
            }
            case 'D' : {
                env->SetDoubleField(obj, jf.get_jfield(), value);
                break;
            }
            default : {
                env->SetObjectField(obj, jf.get_jfield(), value);
                break;
            }
        }

        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            throw jnio_exception("An error occurred.");
        }
    }

    void java_object::edit(const java_field& jf, const value& value) {
        return java_object::_edit(this->env, this->obj, jf, value);
    }

    java_class java_object::get_class() const {
        if (this->get_jobject() == nullptr) {
            throw std::invalid_argument("Unable to call .get_class() method on a null java_object.");
        }

        return java_class(this->env, env->GetObjectClass(this->obj));
    }

    java_object::operator const jobject&() const noexcept {
        return this->obj;
    }

    jobject java_object::get_jobject() const noexcept {
        return env->NewLocalRef(this->obj);
    }

	static jmethodID TO_STRING;

    std::string java_object::string() const noexcept {
        jclass clazz = env->GetObjectClass(this->obj);

		if (TO_STRING == nullptr) {
			TO_STRING = env->GetMethodID(clazz, "toString", sign::TO_STRING);
		}

        java_string str(this->env, (jstring) env->CallObjectMethod(this->obj, TO_STRING));
        std::string res = str.string();
        env->DeleteLocalRef(clazz);

        return res;
    }

	const char* java_object::c_str() const noexcept {
        return this->string().c_str();
    }

	static jmethodID EQUALS;

    bool java_object::operator == (const jobject& other) const noexcept {
        jclass clazz = env->GetObjectClass(this->obj);
        
		if (EQUALS == nullptr) {
			EQUALS = env->GetMethodID(clazz, "equals", sign::EQUALS);
		}

        jboolean res = env->CallBooleanMethod(this->obj, EQUALS, obj);
        bool eq = (res == 1) ? true : false;
        env->DeleteLocalRef(clazz);

        return eq;
    }
	
    bool java_object::same_type(const jobject& obj) const noexcept {
        return (env->IsInstanceOf(this->obj, env->GetObjectClass(obj)) == 0 ? false : true);
    }

    bool java_object::is_instanceof(const jclass& clazz) const noexcept {
        return (env->IsInstanceOf(this->obj, clazz) == 0 ? false : true);
    }

    java_object_array_element::java_object_array_element(java_object_array* ref, size_t refIndex)
		: java_object(ref->env, env->GetObjectArrayElement(ref->arr, refIndex)) {
        this->ref = ref;
		this->refIndex = refIndex;
    }

    java_object_array_element::~java_object_array_element() {
        if (this->hasChanged) {
            env->SetObjectArrayElement(this->ref->arr, this->refIndex, this->obj);
        }
    }

	java_object_array_element& java_object_array_element::operator = (const java_object& obj) {
        this->hasChanged = true;
        if (this->obj != nullptr) {
            env->DeleteWeakGlobalRef(this->obj);
        }
        this->obj = env->NewWeakGlobalRef(obj);
        
        return *this;
    }

    java_object_array_element& java_object_array_element::operator = (const jobject& obj) {
        this->hasChanged = true;
        if (this->obj != nullptr) {
            env->DeleteWeakGlobalRef(this->obj);
        }
        this->obj = env->NewWeakGlobalRef(obj);
        
        return *this;
    }

    java_object_array::java_object_array(JNIEnv* env, const jobjectArray& arr) {
        this->env = env;
        this->arr = (jobjectArray) env->NewWeakGlobalRef(arr);
    }

    java_object_array::java_object_array(const java_object_array& arr) {
		this->env = env;
        this->arr = (jobjectArray) env->NewWeakGlobalRef(arr.arr);
    }

	java_object_array& java_object_array::operator = (const jobjectArray& arr) {
        if (this->arr != nullptr) {
            env->DeleteWeakGlobalRef(this->arr);
        }
        this->arr = (jobjectArray) env->NewWeakGlobalRef(arr);

        return *this;
    }

	java_object_array& java_object_array::operator = (const java_object_array& arr) {
        if (this->arr != nullptr) {
            env->DeleteWeakGlobalRef(this->arr);
        }
        this->env = arr.env;
        this->arr = (jobjectArray) env->NewWeakGlobalRef(arr);

        return *this;
    }

    java_object_array::~java_object_array() {
        if (this->currentElement != nullptr) {
            delete this->currentElement;
        }

		if (this->arr != nullptr) {
			env->DeleteWeakGlobalRef(this->arr);
		}
    }

    java_object_array::operator const jobjectArray&() const noexcept {
        return this->arr;
    }

    jobjectArray java_object_array::getJObjectArray() const noexcept {
        return (jobjectArray) env->NewLocalRef(this->arr);
    }

    java_object java_object_array::as_object() const noexcept {
        return java_object(this->env, this->arr);
    }

    java_object_array_element& java_object_array::operator [] (size_t index) {
        if (index >= this->length()) {
            throw std::out_of_range("The given index goes out of bounds for this java_object_array.");
        }

        if (this->currentElement != nullptr) {
            delete this->currentElement;
        }
        this->currentElement = new java_object_array_element(this, index);
        
        return *this->currentElement;
    }

    size_t java_object_array::length() const noexcept {
        return env->GetArrayLength(this->arr);
    }

	static java_static_method PRINT_ARRAY;

	static java_static_method ARRAY_EQUALS;

    std::string java_object_array::string() const noexcept {
        if (PRINT_ARRAY.string().empty()) {
            java_class clazz(this->env, "java/util/Arrays");
            PRINT_ARRAY = java_static_method(this->env, "toString", clazz,
				sign::method(sign::STRING, { sign::OBJECT_ARRAY }));
        }

        java_string str(this->env, (jstring) PRINT_ARRAY.call({ this->arr }));
        return str.string();
    }

    bool java_object_array::operator == (const jobjectArray& arr) const noexcept {
        if (ARRAY_EQUALS.string().empty()) {
            java_class clazz(this->env, "java/util/Arrays");
            ARRAY_EQUALS = java_static_method(this->env, "equals", clazz, 
				sign::method(sign::BOOLEAN, { sign::OBJECT_ARRAY, sign::OBJECT_ARRAY}));
        }

        bool eq = ((jboolean) ARRAY_EQUALS.call({ this->arr, arr }) == 1) ? true : false;
        return eq;
    }
}
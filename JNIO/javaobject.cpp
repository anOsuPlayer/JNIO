#include "javaobject.hpp"

namespace jnio {

    java_object::java_object(const jobject& obj) {
        this->obj = JNIOEnv->NewWeakGlobalRef(obj);
    }

    java_object::~java_object() {
        if (this->obj != nullptr) {
            JNIOEnv->DeleteWeakGlobalRef(this->obj);
        }
    }

	java_object::java_object(const java_object& obj) {
		this->obj = JNIOEnv->NewWeakGlobalRef(obj.obj);
    }

	java_object& java_object::operator = (const java_object& other) {
        if (this->obj != nullptr) {
            JNIOEnv->DeleteWeakGlobalRef(this->obj);
        }
        this->obj = JNIOEnv->NewWeakGlobalRef(other);
        
        return *this;
    }

    java_object& java_object::operator = (const jobject& other) {
        if (this->obj != nullptr) {
            JNIOEnv->DeleteWeakGlobalRef(this->obj);
        }
        this->obj = JNIOEnv->NewWeakGlobalRef(other);
        
        return *this;
    }

    value java_object::_call(jobject obj, const java_method& jm, std::initializer_list<value> args) {
        sign::signature ret = jm.get_signature().return_type();
        value r;

        switch (ret[0]) {
            case 'Z' : {
                if (args.size() == 0) {
                    r = JNIOEnv->CallBooleanMethodA(obj, jm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = JNIOEnv->CallBooleanMethod(obj, jm.getJMethod());
                }
                break;
            }
            case 'B' : {
                if (args.size() == 0) {
                    r = JNIOEnv->CallByteMethodA(obj, jm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = JNIOEnv->CallByteMethod(obj, jm.getJMethod());
                }
                break;
            }
            case 'S' : {
                if (args.size() == 0) {
                    r = JNIOEnv->CallShortMethodA(obj, jm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = JNIOEnv->CallShortMethod(obj, jm.getJMethod());
                }
                break;
            }
            case 'C' : {
                if (args.size() == 0) {
                    r = JNIOEnv->CallCharMethodA(obj, jm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = JNIOEnv->CallCharMethod(obj, jm.getJMethod());
                }
                break;
            }
            case 'I' : {
                if (args.size() == 0) {
                    r = JNIOEnv->CallIntMethodA(obj, jm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = JNIOEnv->CallIntMethod(obj, jm.getJMethod());
                }
                break;
            }
            case 'J' : {
                if (args.size() == 0) {
                    r = JNIOEnv->CallLongMethodA(obj, jm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = JNIOEnv->CallLongMethod(obj, jm.getJMethod());
                }
                break;
            }
            case 'F' : {
                if (args.size() == 0) {
                    r = JNIOEnv->CallFloatMethodA(obj, jm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = JNIOEnv->CallFloatMethod(obj, jm.getJMethod());
                }
                break;
            }
            case 'D' : {
                if (args.size() == 0) {
                    r = JNIOEnv->CallDoubleMethodA(obj, jm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = JNIOEnv->CallDoubleMethod(obj, jm.getJMethod());
                }
                break;
            }
            case 'V' : {
                if (args.size() == 0) {
                    JNIOEnv->CallVoidMethodA(obj, jm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    JNIOEnv->CallVoidMethod(obj, jm.getJMethod());
                }
                break;
            }
            default : {
                if (args.size() == 0) {
                    r = JNIOEnv->CallObjectMethodA(obj, jm.getJMethod(), (jvalue*) args.begin());
                }
                else {
                    r = JNIOEnv->CallObjectMethod(obj, jm.getJMethod());
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

    value java_object::call(const java_method& jm, std::initializer_list<value> args) const {
        return java_object::_call(this->obj, jm, args);
    }

    value java_object::_access(jobject obj, const java_field& jf) {
        const char id = jf.get_signature()[0];
        value r;

        switch (id) {
            case 'Z' : {
                r = JNIOEnv->GetBooleanField(obj, jf.get_jfield());
                break;
            }
            case 'B' : {
                r = JNIOEnv->GetByteField(obj, jf.get_jfield());
                break;
            }
            case 'S' : {
                r = JNIOEnv->GetShortField(obj, jf.get_jfield());
                break;
            }
            case 'C' : {
                r = JNIOEnv->GetCharField(obj, jf.get_jfield());
                break;
            }
            case 'I' : {
                r = JNIOEnv->GetIntField(obj, jf.get_jfield());
                break;
            }
            case 'J' : {
                r = JNIOEnv->GetLongField(obj, jf.get_jfield());
                break;
            }
            case 'F' : {
                r = JNIOEnv->GetFloatField(obj, jf.get_jfield());
                break;
            }
            case 'D' : {
                r = JNIOEnv->GetDoubleField(obj, jf.get_jfield());
                break;
            }
            default : {
                r = JNIOEnv->GetObjectField(obj, jf.get_jfield());
                break;
            }
        }

        if (JNIOEnv->ExceptionCheck()) {
            JNIOEnv->ExceptionDescribe();
            throw jnio_exception("An error occurred.");
        }
        return r;
    }

    value java_object::access(const java_field& jf) const {
        return java_object::_access(this->obj, jf);
    }

    void java_object::_edit(jobject obj, const java_field& jf, const value& value) {
        const char id = jf.get_signature()[0];

        switch (id) {
            case 'Z' : {
                JNIOEnv->SetBooleanField(obj, jf.get_jfield(), value);
                break;
            }
            case 'B' : {
                JNIOEnv->SetByteField(obj, jf.get_jfield(), value);
                break;
            }
            case 'S' : {
                JNIOEnv->SetShortField(obj, jf.get_jfield(), value);
                break;
            }
            case 'C' : {
                JNIOEnv->SetCharField(obj, jf.get_jfield(), value);
                break;
            }
            case 'I' : {
                JNIOEnv->SetIntField(obj, jf.get_jfield(), value);
                break;
            }
            case 'J' : {
                JNIOEnv->SetLongField(obj, jf.get_jfield(), value);
                break;
            }
            case 'F' : {
                JNIOEnv->SetFloatField(obj, jf.get_jfield(), value);
                break;
            }
            case 'D' : {
                JNIOEnv->SetDoubleField(obj, jf.get_jfield(), value);
                break;
            }
            default : {
                JNIOEnv->SetObjectField(obj, jf.get_jfield(), value);
                break;
            }
        }

        if (JNIOEnv->ExceptionCheck()) {
            JNIOEnv->ExceptionDescribe();
            throw jnio_exception("An error occurred.");
        }
    }

    void java_object::edit(const java_field& jf, const value& value) {
        return java_object::_edit(this->obj, jf, value);
    }

    java_class java_object::get_class() const {
        if (this->get_jobject() == nullptr) {
            throw std::invalid_argument("Unable to call .get_class() method on a null java_object.");
        }

        return java_class(JNIOEnv->GetObjectClass(this->obj));
    }

    java_object::operator const jobject&() const noexcept {
        return this->obj;
    }

    jobject java_object::get_jobject() const noexcept {
        return JNIOEnv->NewLocalRef(this->obj);
    }

	static jmethodID TO_STRING;

    std::string java_object::string() const noexcept {
        jclass clazz = JNIOEnv->GetObjectClass(this->obj);

		if (TO_STRING == nullptr) {
			TO_STRING = JNIOEnv->GetMethodID(clazz, "toString", sign::TO_STRING);
		}

        java_string str((jstring) JNIOEnv->CallObjectMethod(this->obj, TO_STRING));
        std::string res = str.string();
        JNIOEnv->DeleteLocalRef(clazz);

        return res;
    }

	const char* java_object::c_str() const noexcept {
        return this->string().c_str();
    }

	static jmethodID EQUALS;

    bool java_object::operator == (const jobject& other) const noexcept {
        jclass clazz = JNIOEnv->GetObjectClass(this->obj);
        
		if (EQUALS == nullptr) {
			EQUALS = JNIOEnv->GetMethodID(clazz, "equals", sign::EQUALS);
		}

        jboolean res = JNIOEnv->CallBooleanMethod(this->obj, EQUALS, obj);
        bool eq = (res == 1) ? true : false;
        JNIOEnv->DeleteLocalRef(clazz);

        return eq;
    }
	
    bool java_object::same_type(const jobject& obj) const noexcept {
        return (JNIOEnv->IsInstanceOf(this->obj, JNIOEnv->GetObjectClass(obj)) == 0 ? false : true);
    }

    bool java_object::is_instanceof(const jclass& clazz) const noexcept {
        return (JNIOEnv->IsInstanceOf(this->obj, clazz) == 0 ? false : true);
    }

    java_object_array_element::java_object_array_element(java_object_array* ref, size_t refIndex)
		: java_object(JNIOEnv->GetObjectArrayElement(ref->arr, refIndex)) {
        this->ref = ref;
		this->refIndex = refIndex;
    }

    java_object_array_element::~java_object_array_element() {
        if (this->hasChanged) {
            JNIOEnv->SetObjectArrayElement(this->ref->arr, this->refIndex, this->obj);
        }
    }

	java_object_array_element& java_object_array_element::operator = (const java_object& obj) {
        this->hasChanged = true;
        if (this->obj != nullptr) {
            JNIOEnv->DeleteWeakGlobalRef(this->obj);
        }
        this->obj = JNIOEnv->NewWeakGlobalRef(obj);
        
        return *this;
    }

    java_object_array_element& java_object_array_element::operator = (const jobject& obj) {
        this->hasChanged = true;
        if (this->obj != nullptr) {
            JNIOEnv->DeleteWeakGlobalRef(this->obj);
        }
        this->obj = JNIOEnv->NewWeakGlobalRef(obj);
        
        return *this;
    }

    java_object_array::java_object_array(const jobjectArray& arr) {
        this->arr = (jobjectArray) JNIOEnv->NewWeakGlobalRef(arr);
    }

    java_object_array::java_object_array(const java_object_array& arr) {
        this->arr = (jobjectArray) JNIOEnv->NewWeakGlobalRef(arr.arr);
    }

	java_object_array& java_object_array::operator = (const jobjectArray& arr) {
        if (this->arr != nullptr) {
            JNIOEnv->DeleteWeakGlobalRef(this->arr);
        }
        this->arr = (jobjectArray) JNIOEnv->NewWeakGlobalRef(arr);

        return *this;
    }

	java_object_array& java_object_array::operator = (const java_object_array& arr) {
        if (this->arr != nullptr) {
            JNIOEnv->DeleteWeakGlobalRef(this->arr);
        }
        this->arr = (jobjectArray) JNIOEnv->NewWeakGlobalRef(arr);

        return *this;
    }

    java_object_array::~java_object_array() {
        if (this->currentElement != nullptr) {
            delete this->currentElement;
        }

		if (this->arr != nullptr) {
			JNIOEnv->DeleteWeakGlobalRef(this->arr);
		}
    }

    java_object_array::operator const jobjectArray&() const noexcept {
        return this->arr;
    }

    jobjectArray java_object_array::getJObjectArray() const noexcept {
        return (jobjectArray) JNIOEnv->NewLocalRef(this->arr);
    }

    java_object java_object_array::as_object() const noexcept {
        return java_object(this->arr);
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
        return JNIOEnv->GetArrayLength(this->arr);
    }

	static java_static_method PRINT_ARRAY;

	static java_static_method ARRAY_EQUALS;

    std::string java_object_array::string() const noexcept {
        if (PRINT_ARRAY.string().empty()) {
            java_class clazz("java/util/Arrays");
            PRINT_ARRAY = java_static_method("toString", clazz,
				sign::method(sign::STRING, { sign::OBJECT_ARRAY }));
        }

        java_string str((jstring) PRINT_ARRAY.call({ this->arr }));
        return str.string();
    }

    bool java_object_array::operator == (const jobjectArray& arr) const noexcept {
        if (ARRAY_EQUALS.string().empty()) {
            java_class clazz("java/util/Arrays");
            ARRAY_EQUALS = java_static_method("equals", clazz, 
				sign::method(sign::BOOLEAN, { sign::OBJECT_ARRAY, sign::OBJECT_ARRAY}));
        }

        bool eq = ((jboolean) ARRAY_EQUALS.call({ this->arr, arr }) == 1) ? true : false;
        return eq;
    }
}
#include "javaarray.hpp"
#include "javaobject.hpp"

namespace jnio {

    JavaBooleanArray::JavaBooleanArray(JNIEnv* env, jbooleanArray arr) : JavaArray(env, env->GetArrayLength(arr)) {
        env->GetBooleanArrayRegion(arr, 0, env->GetArrayLength(arr), this->elements);
    }

    JavaBooleanArray::JavaBooleanArray(JNIEnv* env, size_t size, jboolean* elements) : JavaArray(env, size) {
        if (elements != nullptr) {
            for (size_t i = 0; i < size; i++) {
                this->elements[i] = elements[i];
            }
        }
    }

    JavaBooleanArray::JavaBooleanArray(const JavaBooleanArray& arr) : JavaArray(arr.env, arr.length()) {
        for (size_t i = 0; i < this->size; i++) {
            this->elements[i] = arr.elements[i];
        }
    }

    JavaObject JavaBooleanArray::asObject() const noexcept {
        return JavaObject(this->env, this->getJArray());
    }

    JavaBooleanArray& JavaBooleanArray::operator = (jbooleanArray& arr) noexcept {
        if (this->elements != nullptr) {
            delete[] this->elements;
        }
        this->size = env->GetArrayLength(arr);
        this->elements = new jboolean[this->size];
        env->GetBooleanArrayRegion(arr, 0, this->size, this->elements);

        return *this;
    }

    JavaBooleanArray JavaBooleanArray::region(size_t begin, size_t len) const {
        if (begin >= this->length() || len >= this->length() || begin+len >= this->length()) {
            throw std::out_of_range("The given index goes out of bounds for this JavaBooleanArray.");
        }
        JavaBooleanArray arr(this->env, len);
        for (size_t i = 0; i < len; i++) {
            arr[i] = this->elements[begin+i];
        }

        return arr;
    }

    jbooleanArray JavaBooleanArray::getJArray() const noexcept {
        jbooleanArray arr = env->NewBooleanArray(this->length());
        env->SetBooleanArrayRegion(arr, 0, this->length(), this->elements);
        return arr;
    }

    JavaBooleanArray::operator jbooleanArray() const noexcept {
        return this->getJArray();
    }

    JavaByteArray::JavaByteArray(JNIEnv* env, jbyteArray arr) : JavaArray(env, env->GetArrayLength(arr)) {
        env->GetByteArrayRegion(arr, 0, env->GetArrayLength(arr), this->elements);
    }

    JavaByteArray::JavaByteArray(JNIEnv* env, size_t size, jbyte* elements) : JavaArray(env, size) {
        if (elements != nullptr) {
            for (size_t i = 0; i < size; i++) {
                this->elements[i] = elements[i];
            }
        }
    }

    JavaByteArray::JavaByteArray(const JavaByteArray& arr) : JavaArray(arr.env, arr.length()) {
        for (size_t i = 0; i < this->size; i++) {
            this->elements[i] = arr.elements[i];
        }
    }

    JavaObject JavaByteArray::asObject() const noexcept {
        return JavaObject(this->env, this->getJArray());
    }

    JavaByteArray& JavaByteArray::operator = (jbyteArray& arr) noexcept {
        if (this->elements != nullptr) {
            delete[] this->elements;
        }
        this->size = env->GetArrayLength(arr);
        this->elements = new jbyte[this->size];
        env->GetByteArrayRegion(arr, 0, this->size, this->elements);

        return *this;
    }

    JavaByteArray JavaByteArray::region(size_t begin, size_t len) const {
        if (begin >= this->length() || len >= this->length() || begin+len >= this->length()) {
            throw std::out_of_range("The given index goes out of bounds for this JavaByteArray.");
        }
        JavaByteArray arr(this->env, len);
        for (size_t i = 0; i < len; i++) {
            arr[i] = this->elements[begin+i];
        }

        return arr;
    }

    jbyteArray JavaByteArray::getJArray() const noexcept {
        jbyteArray arr = env->NewByteArray(this->length());
        env->SetByteArrayRegion(arr, 0, this->length(), this->elements);
        return arr;
    }

    JavaByteArray::operator jbyteArray() const noexcept {
        return this->getJArray();
    }

    JavaCharArray::JavaCharArray(JNIEnv* env, jcharArray arr) : JavaArray(env, env->GetArrayLength(arr)) {
        env->GetCharArrayRegion(arr, 0, env->GetArrayLength(arr), this->elements);
    }
	
    JavaCharArray::JavaCharArray(JNIEnv* env, size_t size, jchar* elements) : JavaArray(env, size) {
        if (elements != nullptr) {
            for (size_t i = 0; i < size; i++) {
                this->elements[i] = elements[i];
            }
        }
    }

    JavaCharArray::JavaCharArray(JNIEnv* env, size_t size, const char* elements) : JavaArray(env, size) {
        if (elements != nullptr) {
            for (size_t i = 0; i < size; i++) {
                this->elements[i] = elements[i];
            }
        }
    }

    JavaCharArray::JavaCharArray(const JavaCharArray& arr) : JavaArray(arr.env, arr.length()) {
        for (size_t i = 0; i < this->size; i++) {
            this->elements[i] = arr.elements[i];
        }
    }

    JavaObject JavaCharArray::asObject() const noexcept {
        return JavaObject(this->env, this->getJArray());
    }

    JavaCharArray& JavaCharArray::operator = (jcharArray& arr) noexcept {
        if (this->elements != nullptr) {
            delete[] this->elements;
        }
        this->size = env->GetArrayLength(arr);
        this->elements = new jchar[this->size];
        env->GetCharArrayRegion(arr, 0, this->size, this->elements);

        return *this;
    }

    JavaCharArray JavaCharArray::region(size_t begin, size_t len) const {
        if (begin >= this->length() || len >= this->length() || begin+len >= this->length()) {
            throw std::out_of_range("The given index goes out of bounds for this JavaCharArray.");
        }
        JavaCharArray arr(this->env, len);
        for (size_t i = 0; i < len; i++) {
            arr[i] = this->elements[begin+i];
        }

        return arr;
    }

    jcharArray JavaCharArray::getJArray() const noexcept {
        jcharArray arr = env->NewCharArray(this->length());
        env->SetCharArrayRegion(arr, 0, this->length(), this->elements);
        return arr;
    }

    JavaCharArray::operator jcharArray() const noexcept {
        return this->getJArray();
    }

    JavaIntArray::JavaIntArray(JNIEnv* env, jintArray arr) : JavaArray(env, env->GetArrayLength(arr)) {
        env->GetIntArrayRegion(arr, 0, env->GetArrayLength(arr), this->elements);
    }

    JavaIntArray::JavaIntArray(JNIEnv* env, size_t size, jint* elements) : JavaArray(env, size) {
        if (elements != nullptr) {
            for (size_t i = 0; i < size; i++) {
                this->elements[i] = elements[i];
            }
        }
    }

    JavaIntArray::JavaIntArray(const JavaIntArray& arr) : JavaArray(arr.env, arr.length()) {
        for (size_t i = 0; i < this->size; i++) {
            this->elements[i] = arr.elements[i];
        }
    }

    JavaObject JavaIntArray::asObject() const noexcept {
        return JavaObject(this->env, this->getJArray());
    }

    JavaIntArray& JavaIntArray::operator = (jintArray& arr) noexcept {
        if (this->elements != nullptr) {
            delete[] this->elements;
        }
        this->size = env->GetArrayLength(arr);
        this->elements = new jint[this->size];
        env->GetIntArrayRegion(arr, 0, this->size, this->elements);

        return *this;
    }

    JavaIntArray JavaIntArray::region(size_t begin, size_t len) const {
        if (begin >= this->length() || len >= this->length() || begin+len >= this->length()) {
            throw std::out_of_range("The given index goes out of bounds for this JavaIntArray.");
        }
        JavaIntArray arr(this->env, len);
        for (size_t i = 0; i < len; i++) {
            arr[i] = this->elements[begin+i];
        }

        return arr;
    }

    jintArray JavaIntArray::getJArray() const noexcept {
        jintArray arr = env->NewIntArray(this->length());
        env->SetIntArrayRegion(arr, 0, this->length(), this->elements);
        return arr;
    }

    JavaIntArray::operator jintArray() const noexcept {
        return this->getJArray();
    }

    JavaLongArray::JavaLongArray(JNIEnv* env, jlongArray arr) : JavaArray(env, env->GetArrayLength(arr)) {
        env->GetLongArrayRegion(arr, 0, env->GetArrayLength(arr), this->elements);
    }
	
    JavaLongArray::JavaLongArray(JNIEnv* env, size_t size, jlong* elements) : JavaArray(env, size) {
        if (elements != nullptr) {
            for (size_t i = 0; i < size; i++) {
                this->elements[i] = elements[i];
            }
        }
    }

    JavaLongArray::JavaLongArray(const JavaLongArray& arr) : JavaArray(arr.env, arr.length()) {
        for (size_t i = 0; i < this->size; i++) {
            this->elements[i] = arr.elements[i];
        }
    }

    JavaObject JavaLongArray::asObject() const noexcept {
        return JavaObject(this->env, this->getJArray());
    }

    JavaLongArray& JavaLongArray::operator = (jlongArray& arr) noexcept {
        if (this->elements != nullptr) {
            delete[] this->elements;
        }
        this->size = env->GetArrayLength(arr);
        this->elements = new jlong[this->size];
        env->GetLongArrayRegion(arr, 0, this->size, this->elements);

        return *this;
    }

    JavaLongArray JavaLongArray::region(size_t begin, size_t len) const {
        if (begin >= this->length() || len >= this->length() || begin+len >= this->length()) {
            throw std::out_of_range("The given index goes out of bounds for this JavaLongArray.");
        }
        JavaLongArray arr(this->env, len);
        for (size_t i = 0; i < len; i++) {
            arr[i] = this->elements[begin+i];
        }

        return arr;
    }

    jlongArray JavaLongArray::getJArray() const noexcept {
        jlongArray arr = env->NewLongArray(this->length());
        env->SetLongArrayRegion(arr, 0, this->length(), this->elements);
        return arr;
    }

    JavaLongArray::operator jlongArray() const noexcept {
        return this->getJArray();
    }

    JavaFloatArray::JavaFloatArray(JNIEnv* env, jfloatArray arr) : JavaArray(env, env->GetArrayLength(arr)) {
        env->GetFloatArrayRegion(arr, 0, env->GetArrayLength(arr), this->elements);
    }
	
    JavaFloatArray::JavaFloatArray(JNIEnv* env, size_t size, jfloat* elements) : JavaArray(env, size) {
        if (elements != nullptr) {
            for (size_t i = 0; i < size; i++) {
                this->elements[i] = elements[i];
            }
        }
    }

    JavaFloatArray::JavaFloatArray(const JavaFloatArray& arr) : JavaArray(arr.env, arr.length()) {
        for (size_t i = 0; i < this->size; i++) {
            this->elements[i] = arr.elements[i];
        }
    }
    
    JavaObject JavaFloatArray::asObject() const noexcept {
        return JavaObject(this->env, this->getJArray());
    }

    JavaFloatArray& JavaFloatArray::operator = (jfloatArray& arr) noexcept {
        if (this->elements != nullptr) {
            delete[] this->elements;
        }
        this->size = env->GetArrayLength(arr);
        this->elements = new jfloat[this->size];
        env->GetFloatArrayRegion(arr, 0, this->size, this->elements);

        return *this;
    }

    JavaFloatArray JavaFloatArray::region(size_t begin, size_t len) const {
        if (begin >= this->length() || len >= this->length() || begin+len >= this->length()) {
            throw std::out_of_range("The given index goes out of bounds for this JavaFloatArray.");
        }
        JavaFloatArray arr(this->env, len);
        for (size_t i = 0; i < len; i++) {
            arr[i] = this->elements[begin+i];
        }

        return arr;
    }

    jfloatArray JavaFloatArray::getJArray() const noexcept {
        jfloatArray arr = env->NewFloatArray(this->length());
        env->SetFloatArrayRegion(arr, 0, this->length(), this->elements);
        return arr;
    }

    JavaFloatArray::operator jfloatArray() const noexcept {
        return this->getJArray();
    }

    JavaDoubleArray::JavaDoubleArray(JNIEnv* env, jdoubleArray arr) : JavaArray(env, env->GetArrayLength(arr)) {
        env->GetDoubleArrayRegion(arr, 0, env->GetArrayLength(arr), this->elements);
    }

    JavaDoubleArray::JavaDoubleArray(JNIEnv* env, size_t size, jdouble* elements) : JavaArray(env, size) {
        if (elements != nullptr) {
            for (size_t i = 0; i < size; i++) {
                this->elements[i] = elements[i];
            }
        }
    }

    JavaDoubleArray::JavaDoubleArray(const JavaDoubleArray& arr) : JavaArray(arr.env, arr.length()) {
        for (size_t i = 0; i < this->size; i++) {
            this->elements[i] = arr.elements[i];
        }
    }

    JavaObject JavaDoubleArray::asObject() const noexcept {
        return JavaObject(this->env, this->getJArray());
    }

    JavaDoubleArray& JavaDoubleArray::operator = (jdoubleArray& arr) noexcept {
        if (this->elements != nullptr) {
            delete[] this->elements;
        }
        this->size = env->GetArrayLength(arr);
        this->elements = new jdouble[this->size];
        env->GetDoubleArrayRegion(arr, 0, this->size, this->elements);

        return *this;
    }

    JavaDoubleArray JavaDoubleArray::region(size_t begin, size_t len) const {
        if (begin >= this->length() || len >= this->length() || begin+len >= this->length()) {
            throw std::out_of_range("The given index goes out of bounds for this JavaDoubleArray.");
        }
        JavaDoubleArray arr(this->env, len);
        for (size_t i = 0; i < len; i++) {
            arr[i] = this->elements[begin+i];
        }

        return arr;
    }

    jdoubleArray JavaDoubleArray::getJArray() const noexcept {
        jdoubleArray arr = env->NewDoubleArray(this->length());
        env->SetDoubleArrayRegion(arr, 0, this->length(), this->elements);
        return arr;
    }

    JavaDoubleArray::operator jdoubleArray() const noexcept {
        return this->getJArray();
    }
}
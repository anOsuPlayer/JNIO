#include "javaarray.hpp"
#include "javaobject.hpp"

namespace jnio {

	void java_boolean_array::release_elements() const noexcept {
		if (this->elements != nullptr) {
			JNIOEnv->SetBooleanArrayRegion(this->arr, 0, JNIOEnv->GetArrayLength(this->arr), this->elements);
		}
	}

	java_boolean_array::java_boolean_array() : java_boolean_array((size_t) 0) {

	}
	
	java_boolean_array::java_boolean_array(const jbooleanArray& arr) : java_array() {
		this->arr = arr;

		size_t size = JNIOEnv->GetArrayLength(arr);
		this->elements = (jboolean*) malloc(size * sizeof(jboolean));
		JNIOEnv->GetBooleanArrayRegion(arr, 0, size, this->elements);
	}

	java_boolean_array::java_boolean_array(size_t size, const jboolean* args) : java_array() {
		this->arr = JNIOEnv->NewBooleanArray(size);

		this->elements = (jboolean*) malloc(size * sizeof(jboolean));
		if (args != nullptr) {
			memcpy(this->elements, args, size * sizeof(jboolean));
		}

		for (size_t i = 0; i < size; i++) {
			this->elements[i] = 0;
		}
	}

	java_boolean_array::java_boolean_array(std::initializer_list<jboolean> args) : java_array() {
		this->arr = JNIOEnv->NewBooleanArray(args.size());

		this->elements = (jboolean*) malloc(args.size() * sizeof(jboolean));
		memcpy(this->elements, args.begin(), args.size() * sizeof(jboolean));
	}

	java_boolean_array::java_boolean_array(const java_boolean_array& arr) : java_boolean_array(arr.length(), arr.elements) {
		
	}
	
	java_boolean_array& java_boolean_array::operator = (const java_boolean_array& arr) {
		size_t size = arr.length();
		if (this->elements != nullptr) {
			free(this->elements);
		}
		this->elements = (jboolean*) malloc(size * sizeof(jboolean));
		memcpy(this->elements, arr.get_elements(), size * sizeof(jboolean));

		return *this;
	}

	java_boolean_array& java_boolean_array::operator = (const jbooleanArray& arr) {
		size_t size = JNIOEnv->GetArrayLength(arr);
		if (this->elements != nullptr) {
			free(this->elements);
		}
		this->elements = (jboolean*) malloc(size * sizeof(jboolean));
		JNIOEnv->GetBooleanArrayRegion(arr, 0, size, this->elements);

		return *this;
	}

	java_boolean_array::operator java_object() const noexcept {
		return java_object((jbooleanArray) *this);
	}

	void java_byte_array::release_elements() const noexcept {
		if (this->elements != nullptr) {
			JNIOEnv->SetByteArrayRegion(this->arr, 0, JNIOEnv->GetArrayLength(this->arr), this->elements);
		}
	}

	java_byte_array::java_byte_array() : java_byte_array((size_t) 0) {

	}
	
	java_byte_array::java_byte_array(const jbyteArray& arr) : java_array() {
		this->arr = arr;

		size_t size = JNIOEnv->GetArrayLength(arr);
		this->elements = (jbyte*) malloc(size * sizeof(jbyte));
		JNIOEnv->GetByteArrayRegion(arr, 0, size, this->elements);
	}

	java_byte_array::java_byte_array(size_t size, const jbyte* args) : java_array() {
		this->arr = JNIOEnv->NewByteArray(size);

		this->elements = (jbyte*) malloc(size * sizeof(jbyte));
		if (args != nullptr) {
			memcpy(this->elements, args, size * sizeof(jbyte));
		}

		for (size_t i = 0; i < size; i++) {
			this->elements[i] = 0;
		}
	}

	java_byte_array::java_byte_array(std::initializer_list<jbyte> args) : java_array() {
		this->arr = JNIOEnv->NewByteArray(args.size());

		this->elements = (jbyte*) malloc(args.size() * sizeof(jbyte));
		memcpy(this->elements, args.begin(), args.size() * sizeof(jbyte));
	}

	java_byte_array::java_byte_array(const java_byte_array& arr) : java_byte_array(arr.length(), arr.elements) {
		
	}

	java_byte_array& java_byte_array::operator = (const java_byte_array& arr) {
		size_t size = arr.length();
		if (this->elements != nullptr) {
			free(this->elements);
		}
		this->elements = (jbyte*) malloc(size * sizeof(jbyte));
		memcpy(this->elements, arr.get_elements(), size * sizeof(jbyte));

		return *this;
	}

	java_byte_array& java_byte_array::operator = (const jbyteArray& arr) {
		size_t size = JNIOEnv->GetArrayLength(arr);
		if (this->elements != nullptr) {
			free(this->elements);
		}
		this->elements = (jbyte*) malloc(size * sizeof(jbyte));
		JNIOEnv->GetByteArrayRegion(arr, 0, size, this->elements);

		return *this;
	}

	java_byte_array::operator java_object() const noexcept {
		return java_object((jbyteArray) *this);
	}

	void java_short_array::release_elements() const noexcept {
		if (this->elements != nullptr) {
			JNIOEnv->SetShortArrayRegion(this->arr, 0, JNIOEnv->GetArrayLength(this->arr), this->elements);
		}
	}

	java_short_array::java_short_array() : java_short_array((size_t) 0) {

	}
	
	java_short_array::java_short_array(const jshortArray& arr) : java_array() {
		this->arr = arr;

		size_t size = JNIOEnv->GetArrayLength(arr);
		this->elements = (jshort*) malloc(size * sizeof(jshort));
		JNIOEnv->GetShortArrayRegion(arr, 0, size, this->elements);
	}

	java_short_array::java_short_array(size_t size, const jshort* args) : java_array() {
		this->arr = JNIOEnv->NewShortArray(size);

		this->elements = (jshort*) malloc(size * sizeof(jshort));
		if (args != nullptr) {
			memcpy(this->elements, args, size * sizeof(jshort));
		}

		for (size_t i = 0; i < size; i++) {
			this->elements[i] = 0;
		}
	}

	java_short_array::java_short_array(std::initializer_list<jshort> args) : java_array() {
		this->arr = JNIOEnv->NewShortArray(args.size());

		this->elements = (jshort*) malloc(args.size() * sizeof(jshort));
		memcpy(this->elements, args.begin(), args.size() * sizeof(jshort));
	}

	java_short_array::java_short_array(const java_short_array& arr) : java_short_array(arr.length(), arr.elements) {
		
	}

	java_short_array& java_short_array::operator = (const java_short_array& arr) {
		size_t size = arr.length();
		if (this->elements != nullptr) {
			free(this->elements);
		}
		this->elements = (jshort*) malloc(size * sizeof(jshort));
		memcpy(this->elements, arr.get_elements(), size * sizeof(jshort));

		return *this;
	}

	java_short_array& java_short_array::operator = (const jshortArray& arr) {
		size_t size = JNIOEnv->GetArrayLength(arr);
		if (this->elements != nullptr) {
			free(this->elements);
		}
		this->elements = (jshort*) malloc(size * sizeof(jshort));
		JNIOEnv->GetShortArrayRegion(arr, 0, size, this->elements);

		return *this;
	}

	java_short_array::operator java_object() const noexcept {
		return java_object((jshortArray) *this);
	}

	void java_char_array::release_elements() const noexcept {
		if (this->elements != nullptr) {
			JNIOEnv->SetCharArrayRegion(this->arr, 0, JNIOEnv->GetArrayLength(this->arr), this->elements);
		}
	}

	java_char_array::java_char_array() : java_char_array((size_t) 0, (jchar*) nullptr) {

	}
	
	java_char_array::java_char_array(const jcharArray& arr) : java_array() {
		this->arr = arr;

		size_t size = JNIOEnv->GetArrayLength(arr);
		this->elements = (jchar*) malloc(size * sizeof(jchar));
		JNIOEnv->GetCharArrayRegion(arr, 0, size, this->elements);
	}

	java_char_array::java_char_array(size_t size, const jchar* args) : java_array() {
		this->arr = JNIOEnv->NewCharArray(size);

		this->elements = (jchar*) malloc(size * sizeof(jchar));
		if (args != nullptr) {
			memcpy(this->elements, args, size * sizeof(jchar));
		}

		for (size_t i = 0; i < size; i++) {
			this->elements[i] = 0;
		}
	}
	
	java_char_array::java_char_array(size_t size, const wchar_t* args) : java_array() {
		this->arr = JNIOEnv->NewCharArray(size);

		this->elements = (jchar*) malloc(size * sizeof(jchar));
		if (args != nullptr) {
			memcpy(this->elements, args, size * sizeof(jchar));
		}

		for (size_t i = 0; i < size; i++) {
			this->elements[i] = 0;
		}
	}

	java_char_array::java_char_array(std::initializer_list<jchar> args) : java_array() {
		this->arr = JNIOEnv->NewCharArray(args.size());

		this->elements = (jchar*) malloc(args.size() * sizeof(jchar));
		memcpy(this->elements, args.begin(), args.size() * sizeof(jchar));
	}

	java_char_array::java_char_array(const java_char_array& arr) : java_char_array(arr.length(), arr.elements) {
		
	}

	java_char_array& java_char_array::operator = (const java_char_array& arr) {
		size_t size = arr.length();
		if (this->elements != nullptr) {
			free(this->elements);
		}
		this->elements = (jchar*) malloc(size * sizeof(jchar));
		memcpy(this->elements, arr.get_elements(), size * sizeof(jchar));

		return *this;
	}

	java_char_array& java_char_array::operator = (const jcharArray& arr) {
		size_t size = JNIOEnv->GetArrayLength(arr);
		if (this->elements != nullptr) {
			free(this->elements);
		}
		this->elements = (jchar*) malloc(size * sizeof(jchar));
		JNIOEnv->GetCharArrayRegion(arr, 0, size, this->elements);
		
		return *this;
	}

	java_char_array::operator java_object() const noexcept {
		return java_object((jcharArray) *this);
	}

	void java_int_array::release_elements() const noexcept {
		if (this->elements != nullptr) {
			JNIOEnv->SetIntArrayRegion(this->arr, 0, JNIOEnv->GetArrayLength(this->arr), this->elements);
		}
	}

	java_int_array::java_int_array() : java_int_array((size_t) 0) {

	}
	
	java_int_array::java_int_array(const jintArray& arr) : java_array() {
		this->arr = arr;

		size_t size = JNIOEnv->GetArrayLength(arr);
		this->elements = (jint*) malloc(size * sizeof(jint));
		JNIOEnv->GetIntArrayRegion(arr, 0, size, this->elements);
	}

	java_int_array::java_int_array(size_t size, const jint* args) : java_array() {
		this->arr = JNIOEnv->NewIntArray(size);

		this->elements = (jint*) malloc(size * sizeof(jint));
		if (args != nullptr) {
			memcpy(this->elements, args, size * sizeof(jint));
		}

		for (size_t i = 0; i < size; i++) {
			this->elements[i] = 0;
		}
	}

	java_int_array::java_int_array(std::initializer_list<jint> args) : java_array() {
		this->arr = JNIOEnv->NewIntArray(args.size());

		this->elements = (jint*) malloc(args.size() * sizeof(jint));
		memcpy(this->elements, args.begin(), args.size() * sizeof(jint));
	}

	java_int_array::java_int_array(const java_int_array& arr) : java_int_array(arr.length(), arr.elements) {
		
	}

	java_int_array& java_int_array::operator = (const java_int_array& arr) {
		size_t size = arr.length();
		if (this->elements != nullptr) {
			free(this->elements);
		}
		this->elements = (jint*) malloc(size * sizeof(jint));
		memcpy(this->elements, arr.get_elements(), size * sizeof(jint));

		return *this;
	}

	java_int_array& java_int_array::operator = (const jintArray& arr) {
		size_t size = JNIOEnv->GetArrayLength(arr);
		if (this->elements != nullptr) {
			free(this->elements);
		}
		this->elements = (jint*) malloc(size * sizeof(jint));
		JNIOEnv->GetIntArrayRegion(arr, 0, size, this->elements);

		return *this;
	}

	java_int_array::operator java_object() const noexcept {
		return java_object((jintArray) *this);
	}

	void java_long_array::release_elements() const noexcept {
		if (this->elements != nullptr) {
			JNIOEnv->SetLongArrayRegion(this->arr, 0, JNIOEnv->GetArrayLength(this->arr), this->elements);
		}
	}

	java_long_array::java_long_array() : java_long_array((size_t) 0) {

	}
	
	java_long_array::java_long_array(const jlongArray& arr) : java_array() {
		this->arr = arr;

		size_t size = JNIOEnv->GetArrayLength(arr);
		this->elements = (jlong*) malloc(size * sizeof(jlong));
		JNIOEnv->GetLongArrayRegion(arr, 0, size, this->elements);
	}

	java_long_array::java_long_array(size_t size, const jlong* args) : java_array() {
		this->arr = JNIOEnv->NewLongArray(size);

		this->elements = (jlong*) malloc(size * sizeof(jlong));
		if (args != nullptr) {
			memcpy(this->elements, args, size * sizeof(jlong));
		}

		for (size_t i = 0; i < size; i++) {
			this->elements[i] = 0;
		}
	}

	java_long_array::java_long_array(std::initializer_list<jlong> args) : java_array() {
		this->arr = JNIOEnv->NewLongArray(args.size());

		this->elements = (jlong*) malloc(args.size() * sizeof(jlong));
		memcpy(this->elements, args.begin(), args.size() * sizeof(jlong));
	}

	java_long_array::java_long_array(const java_long_array& arr) : java_long_array(arr.length(), arr.elements) {
		
	}

	java_long_array& java_long_array::operator = (const java_long_array& arr) {
		size_t size = arr.length();
		if (this->elements != nullptr) {
			free(this->elements);
		}
		this->elements = (jlong*) malloc(size * sizeof(jlong));
		memcpy(this->elements, arr.get_elements(), size * sizeof(jlong));

		return *this;
	}

	java_long_array& java_long_array::operator = (const jlongArray& arr) {
		size_t size = JNIOEnv->GetArrayLength(arr);
		if (this->elements != nullptr) {
			free(this->elements);
		}
		this->elements = (jlong*) malloc(size * sizeof(jlong));
		JNIOEnv->GetLongArrayRegion(arr, 0, size, this->elements);

		return *this;
	}

	java_long_array::operator java_object() const noexcept {
		return java_object((jlongArray) *this);
	}

	void java_float_array::release_elements() const noexcept {
		if (this->elements != nullptr) {
			JNIOEnv->SetFloatArrayRegion(this->arr, 0, JNIOEnv->GetArrayLength(this->arr), this->elements);
		}
	}

	java_float_array::java_float_array() : java_float_array((size_t) 0) {

	}
	
	java_float_array::java_float_array(const jfloatArray& arr) : java_array() {
		this->arr = arr;

		size_t size = JNIOEnv->GetArrayLength(arr);
		this->elements = (jfloat*) malloc(size * sizeof(jfloat));
		JNIOEnv->GetFloatArrayRegion(arr, 0, size, this->elements);
	}

	java_float_array::java_float_array(size_t size, const jfloat* args) : java_array() {
		this->arr = JNIOEnv->NewFloatArray(size);

		this->elements = (jfloat*) malloc(size * sizeof(jfloat));
		if (args != nullptr) {
			memcpy(this->elements, args, size * sizeof(jfloat));
		}

		for (size_t i = 0; i < size; i++) {
			this->elements[i] = 0;
		}
	}

	java_float_array::java_float_array(std::initializer_list<jfloat> args) : java_array() {
		this->arr = JNIOEnv->NewFloatArray(args.size());

		this->elements = (jfloat*) malloc(args.size() * sizeof(jfloat));
		memcpy(this->elements, args.begin(), args.size() * sizeof(jfloat));
	}

	java_float_array::java_float_array(const java_float_array& arr) : java_float_array(arr.length(), arr.elements) {
		
	}

	java_float_array& java_float_array::operator = (const java_float_array& arr) {
		size_t size = arr.length();
		if (this->elements != nullptr) {
			free(this->elements);
		}
		this->elements = (jfloat*) malloc(size * sizeof(jfloat));
		memcpy(this->elements, arr.get_elements(), size * sizeof(jfloat));

		return *this;
	}

	java_float_array& java_float_array::operator = (const jfloatArray& arr) {
		size_t size = JNIOEnv->GetArrayLength(arr);
		if (this->elements != nullptr) {
			free(this->elements);
		}
		this->elements = (jfloat*) malloc(size * sizeof(jfloat));
		JNIOEnv->GetFloatArrayRegion(arr, 0, size, this->elements);

		return *this;
	}

	java_float_array::operator java_object() const noexcept {
		return java_object((jfloatArray) *this);
	}

	void java_double_array::release_elements() const noexcept {
		if (this->elements != nullptr) {
			JNIOEnv->SetDoubleArrayRegion(this->arr, 0, JNIOEnv->GetArrayLength(this->arr), this->elements);
		}
	}

	java_double_array::java_double_array() : java_double_array((size_t) 0) {

	}
	
	java_double_array::java_double_array(const jdoubleArray& arr) : java_array() {
		this->arr = arr;

		size_t size = JNIOEnv->GetArrayLength(arr);
		this->elements = (jdouble*) malloc(size * sizeof(jdouble));
		JNIOEnv->GetDoubleArrayRegion(arr, 0, size, this->elements);
	}

	java_double_array::java_double_array(size_t size, const jdouble* args) : java_array() {
		this->arr = JNIOEnv->NewDoubleArray(size);

		this->elements = (jdouble*) malloc(size * sizeof(jdouble));
		if (args != nullptr) {
			memcpy(this->elements, args, size * sizeof(jdouble));
		}

		for (size_t i = 0; i < size; i++) {
			this->elements[i] = 0;
		}
	}

	java_double_array::java_double_array(std::initializer_list<jdouble> args) : java_array() {
		this->arr = JNIOEnv->NewDoubleArray(args.size());

		this->elements = (jdouble*) malloc(args.size() * sizeof(jdouble));
		memcpy(this->elements, args.begin(), args.size() * sizeof(jdouble));
	}

	java_double_array::java_double_array(const java_double_array& arr) : java_double_array(arr.length(), arr.elements) {
		
	}
	
	java_double_array& java_double_array::operator = (const java_double_array& arr) {
		size_t size = arr.length();
		if (this->elements != nullptr) {
			free(this->elements);
		}
		this->elements = (jdouble*) malloc(size * sizeof(jdouble));
		memcpy(this->elements, arr.get_elements(), size * sizeof(jdouble));

		return *this;
	}

	java_double_array& java_double_array::operator = (const jdoubleArray& arr) {
		size_t size = JNIOEnv->GetArrayLength(arr);
		if (this->elements != nullptr) {
			free(this->elements);
		}
		this->elements = (jdouble*) malloc(size * sizeof(jdouble));
		JNIOEnv->GetDoubleArrayRegion(arr, 0, size, this->elements);

		return *this;
	}

	java_double_array::operator java_object() const noexcept {
		return java_object((jdoubleArray) *this);
	}
}
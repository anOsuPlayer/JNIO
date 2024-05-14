#ifndef JNIO_ARRAYS
    #define JNIO_ARRAYS

    #include <concepts>

    #include "jni.h"

    #include "javavalue.hpp"
    #include "jnioexception.hpp"

    namespace jnio {

        class java_object;

        template <typename A> concept jnio_arraytype = requires { std::is_base_of<jarray, A>(); };

        template <jnio_arraytype A, typename T> class java_array {
            protected:
                T* elements;
                mutable size_t size;

                java_array(size_t size) {
                    this->elements = new T[size];
                    this->size = size;
                }

            public:
                virtual ~java_array() {
                    delete[] this->elements;
                }

                virtual java_array<A, T>& operator = (const java_array<A, T>& arr) noexcept final {
                    if (this->elements != nullptr) {
                        delete[] this->elements;
                    }
                    this->size = arr.length();
                    this->elements = new T[size];
                    for (size_t i = 0; i < size; i++) {
                        this->elements[i] = arr.elements[i];
                    }

                    return *this;
                }
                virtual java_array<A, T>& operator = (A& arr) noexcept = 0;

                virtual T& operator [] (size_t index) final {
                    if (index >= this->length()) {
                        throw jnio_exception("The given index goes out of bounds for this JavaArray.");
                    }
                    return this->elements[index];
                }

                virtual A get_jarray() const noexcept = 0;
                virtual operator A() const noexcept = 0;

                virtual java_value get_jvalue() const noexcept {
                    return JValue(*this);
                }
                virtual operator java_value() const noexcept {
                    return java_value(*this);
                }

                virtual java_object as_object() const noexcept = 0;
                
                size_t length() const noexcept {
                    return this->size;
                }
        };

        class java_boolean_array : public java_array<jbooleanArray, jboolean> {
            protected:
                java_boolean_array() = default;

            public:
                java_boolean_array(jbooleanArray arr);
                java_boolean_array(const java_boolean_array& arr);
                java_boolean_array(size_t size, jboolean* elements = nullptr);
                virtual ~java_boolean_array() = default;

                virtual java_object as_object() const noexcept override final;

                virtual java_boolean_array& operator = (jbooleanArray& arr) noexcept override final;

                java_boolean_array region(size_t begin, size_t end) const;

                virtual jbooleanArray get_jarray() const noexcept override final;
                virtual operator jbooleanArray() const noexcept override final;
        };
        class java_byte_array : public java_array<jbyteArray, jbyte> {
            protected:
                java_byte_array() = default;

            public:
                java_byte_array(jbyteArray arr);
                java_byte_array(const java_byte_array& arr);
                java_byte_array(size_t size, jbyte* elements = nullptr);
                virtual ~java_byte_array() = default;

                virtual java_object as_object() const noexcept override final;

                virtual java_byte_array& operator = (jbyteArray& arr) noexcept override final;

                java_byte_array region(size_t begin, size_t end) const;

                virtual jbyteArray get_jarray() const noexcept override final;
                virtual operator jbyteArray() const noexcept override final;
        };
        class java_char_array : public java_array<jcharArray, jchar> {
            protected:
                java_char_array() = default;

            public:
                java_char_array(jcharArray arr);
                java_char_array(const java_char_array& arr);
                java_char_array(size_t size, jchar* elements = nullptr);
                java_char_array(size_t size, const char* elements);
                virtual ~java_char_array() = default;

                virtual java_object as_object() const noexcept override final;

                virtual java_char_array& operator = (jcharArray& arr) noexcept override final;

                java_char_array region(size_t begin, size_t end) const;

                virtual jcharArray get_jarray() const noexcept override final;
                virtual operator jcharArray() const noexcept override final;
        };
        class java_int_array : public java_array<jintArray, jint> {
            protected:
                java_int_array() = default;

            public:
                java_int_array(jintArray arr);
                java_int_array(const java_int_array& arr);
                java_int_array(size_t size, jint* elements = nullptr);
                virtual ~java_int_array() = default;

                virtual java_object as_object() const noexcept override final;

                virtual java_int_array& operator = (jintArray& arr) noexcept override final;

                java_int_array region(size_t begin, size_t end) const;

                virtual jintArray get_jarray() const noexcept override final;
                virtual operator jintArray() const noexcept override final;
        };
        class java_long_array : public java_array<jlongArray, jlong> {
            protected:
                java_long_array() = default;

            public:
                java_long_array(jlongArray arr);
                java_long_array(const java_long_array& arr);
                java_long_array(size_t size, jlong* elements = nullptr);
                virtual ~java_long_array() = default;

                virtual java_object as_object() const noexcept override final;

                virtual java_long_array& operator = (jlongArray& arr) noexcept override final;

                java_long_array region(size_t begin, size_t end) const;

                virtual jlongArray get_jarray() const noexcept override final;
                virtual operator jlongArray() const noexcept override final;
        };
        class java_float_array : public java_array<jfloatArray, jfloat> {
            protected:
                java_float_array() = default;

            public:
                java_float_array(jfloatArray arr);
                java_float_array(const java_float_array& arr);
                java_float_array(size_t size, jfloat* elements = nullptr);
                virtual ~java_float_array() = default;

                virtual java_object as_object() const noexcept override final;

                virtual java_float_array& operator = (jfloatArray& arr) noexcept override final;

                java_float_array region(size_t begin, size_t end) const;

                virtual jfloatArray get_jarray() const noexcept override final;
                virtual operator jfloatArray() const noexcept override final;
        };
        class java_double_array : public java_array<jdoubleArray, jdouble> {
            protected:
                java_double_array() = default;

            public:
                java_double_array(jdoubleArray arr);
                java_double_array(const java_double_array& arr);
                java_double_array(size_t size, jdouble* elements = nullptr);
                virtual ~java_double_array() = default;

                virtual java_object as_object() const noexcept override final;

                virtual java_double_array& operator = (jdoubleArray& arr) noexcept override final;

                java_double_array region(size_t begin, size_t end) const;

                virtual jdoubleArray get_jarray() const noexcept override final;
                virtual operator jdoubleArray() const noexcept override final;
        };
    }

#endif
#ifndef JNIO_SIGNATURE
	#define JNIO_SIGNATURE

	#include <jni.h>
	#include <string>

	#include "jnioexception.hpp"

	namespace jnio::sign {

		class pure_signature {
			protected:
				std::string sign;
				pure_signature() = default;
				pure_signature(const std::string& signature);

			public:
				~pure_signature() = default;

				pure_signature(const pure_signature& s) = default;
				pure_signature& operator = (const pure_signature& s) = default;

				const std::string& string() const noexcept;
				operator const char*() const noexcept;
				bool operator == (const pure_signature& other) const noexcept;
		};

		class signature : public pure_signature {
			protected:
				signature() = default;

			public:
				signature(const std::string& signature);

				~signature() = default;

				signature(const signature& s) = default;
				signature& operator = (const signature& s) = default;
		};

		const signature BOOLEAN("Z");
		const signature BYTE("B");
		const signature CHAR("C");
		const signature SHORT("S");
		const signature INT("I");
		const signature LONG("J");
		const signature FLOAT("F");
		const signature DOUBLE("D");

		const signature VOID("V");

		class args : public signature {
			protected:
				args() = default;

			public:
				args(std::initializer_list<signature> s);

				~args() = default;

				args(const args& s) = default;
				args& operator = (const args& s) = default;

				args& operator + (const signature& ps);
				args& operator += (const signature& ps);
		};

		class object : public signature {
			protected:
				object() = default;

			public:
				object(const std::string& obj);

				~object() = default;

				object(const object& os) = default;
				object& operator = (const object& os) = default; 
		};

		const object STRING("java/lang/String");
		const object OBJECT("java/lang/object");

		class array : public signature {
			protected:
				size_t order;

			public:
				array() = default;
				explicit array(const signature& base, size_t order = 1);
				
				~array() = default;

				array(const array& os) = default;
				array& operator = (const array& os) = default; 

				size_t get_order() const noexcept;
				signature getBasesignature() const noexcept;
		};

		const array BOOLEAN_ARRAY(BOOLEAN);
		const array BYTE_ARRAY(BYTE);
		const array CHAR_ARRAY(CHAR);
		const array SHORT_ARRAY(SHORT);
		const array INT_ARRAY(INT);
		const array LONG_ARRAY(LONG);
		const array FLOAT_ARRAY(FLOAT);
		const array DOUBLE_ARRAY(DOUBLE);

		const array STRING_ARRAY(STRING);
		const array OBJECT_ARRAY(OBJECT);

		class method : public signature {
			public:
				method() = default;
				method(const std::string& signature);
				explicit method(const signature& returntype);
				explicit method(const signature& returntype, const args& args);

				~method() = default;

				method(const method& os) = default;
				method& operator = (const method& os) = default; 

				signature returnType() const noexcept;
			
			friend class constructor;
		};

		const method BOOLEAN_METHOD(BOOLEAN);
		const method BYTE_METHOD(BYTE);
		const method SHORT_METHOD(SHORT);
		const method CHAR_METHOD(CHAR);
		const method INT_METHOD(INT);
		const method LONG_METHOD(LONG);
		const method FLOAT_METHOD(FLOAT);
		const method DOUBLE_METHOD(DOUBLE);
		
		const method VOID_METHOD(VOID);

		const method STRING_METHOD(STRING);

		const method MAIN(VOID, { STRING_ARRAY });

		const method TO_STRING(STRING);
		const method EQUALS(BOOLEAN, { OBJECT });
		const method HASH_CODE(INT);
		const method WAIT(VOID);
		const method NOTIFY(VOID);

		class constructor : public method {
			public:
				constructor();
				constructor(const std::string& signature);
				explicit constructor(const args& args);

				~constructor() = default;

				constructor(const constructor& cs) = default;
				constructor& operator = (const constructor& os) = default; 
		};

		const constructor DEFAULT;

		class field : public signature {
			public:
				field() = default;
				field(const std::string& signature);
				explicit field(const signature& type);
				
				~field() = default;

				field(const field& cs) = default;
				field& operator = (const field& os) = default; 
		};

		const field BOOLEAN_FIELD(BOOLEAN);
		const field BYTE_FIELD(BYTE);
		const field SHORT_FIELD(SHORT);
		const field CHAR_FIELD(CHAR);
		const field INT_FIELD(INT);
		const field LONG_FIELD(LONG);
		const field FLOAT_FIELD(FLOAT);
		const field DOUBLE_FIELD(DOUBLE);

		const field STRING_FIELD(STRING);
		const field OBJECT_FIELD(OBJECT);
	}

#endif
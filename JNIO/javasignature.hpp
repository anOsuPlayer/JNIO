#ifndef JNIO_SIGNATURE
	#define JNIO_SIGNATURE

	#include <jni.h>
	#include <string>

	#include "jnioexception.hpp"

	namespace jnio::sign {

		class PureSignature {
			protected:
				std::string signature;
				PureSignature() = default;
				PureSignature(const std::string& signature);

			public:
				~PureSignature() = default;

				PureSignature(const PureSignature& s) = default;
				PureSignature& operator = (const PureSignature& s) = default;

				const std::string& string() const noexcept;
				operator const char*() const noexcept;
				bool operator == (const PureSignature& other) const noexcept;
		};

		class Signature : public PureSignature {
			protected:
				Signature() = default;

			public:
				Signature(const std::string& signature);

				~Signature() = default;

				Signature(const Signature& s) = default;
				Signature& operator = (const Signature& s) = default;
		};

		const Signature BOOLEAN("Z");
		const Signature BYTE("B");
		const Signature CHAR("C");
		const Signature SHORT("S");
		const Signature INT("I");
		const Signature LONG("J");
		const Signature FLOAT("F");
		const Signature DOUBLE("D");

		const Signature VOID("V");

		class Args : public Signature {
			protected:
				Args() = default;

			public:
				Args(std::initializer_list<Signature> s);

				~Args() = default;

				Args(const Args& s) = default;
				Args& operator = (const Args& s) = default;

				Args& operator + (const Signature& ps);
				Args& operator += (const Signature& ps);
		};

		class Object : public Signature {
			protected:
				Object() = default;

			public:
				Object(const std::string& obj);

				~Object() = default;

				Object(const Object& os) = default;
				Object& operator = (const Object& os) = default; 
		};

		const Object STRING("java/lang/String");
		const Object OBJECT("java/lang/Object");

		class Array : public Signature {
			protected:
				size_t order;

			public:
				Array() = default;
				explicit Array(const Signature& base, size_t order = 1);
				
				~Array() = default;

				Array(const Array& os) = default;
				Array& operator = (const Array& os) = default; 

				size_t get_order() const noexcept;
				Signature getBaseSignature() const noexcept;
		};

		const Array BOOLEAN_ARRAY(BOOLEAN);
		const Array BYTE_ARRAY(BYTE);
		const Array CHAR_ARRAY(CHAR);
		const Array SHORT_ARRAY(SHORT);
		const Array INT_ARRAY(INT);
		const Array LONG_ARRAY(LONG);
		const Array FLOAT_ARRAY(FLOAT);
		const Array DOUBLE_ARRAY(DOUBLE);

		const Array STRING_ARRAY(STRING);
		const Array OBJECT_ARRAY(OBJECT);

		class Method : public Signature {
			public:
				Method() = default;
				Method(const std::string& signature);
				explicit Method(const Signature& returntype);
				explicit Method(const Signature& returntype, const Args& args);

				~Method() = default;

				Method(const Method& os) = default;
				Method& operator = (const Method& os) = default; 

				Signature returnType() const noexcept;
			
			friend class Constructor;
		};

		const Method BOOLEAN_METHOD(BOOLEAN);
		const Method BYTE_METHOD(BYTE);
		const Method SHORT_METHOD(SHORT);
		const Method CHAR_METHOD(CHAR);
		const Method INT_METHOD(INT);
		const Method LONG_METHOD(LONG);
		const Method FLOAT_METHOD(FLOAT);
		const Method DOUBLE_METHOD(DOUBLE);
		
		const Method VOID_METHOD(VOID);

		const Method STRING_METHOD(STRING);

		const Method MAIN(VOID, { STRING_ARRAY });

		const Method TO_STRING(STRING);
		const Method EQUALS(BOOLEAN, { OBJECT });
		const Method HASH_CODE(INT);
		const Method WAIT(VOID);
		const Method NOTIFY(VOID);

		class Constructor : public Method {
			public:
				Constructor();
				Constructor(const std::string& signature);
				explicit Constructor(const Args& args);

				~Constructor() = default;

				Constructor(const Constructor& cs) = default;
				Constructor& operator = (const Constructor& os) = default; 
		};

		const Constructor DEFAULT;

		class Field : public Signature {
			public:
				Field() = default;
				Field(const std::string& signature);
				explicit Field(const Signature& type);
				
				~Field() = default;

				Field(const Field& cs) = default;
				Field& operator = (const Field& os) = default; 
		};

		const Field BOOLEAN_FIELD(BOOLEAN);
		const Field BYTE_FIELD(BYTE);
		const Field SHORT_FIELD(SHORT);
		const Field CHAR_FIELD(CHAR);
		const Field INT_FIELD(INT);
		const Field LONG_FIELD(LONG);
		const Field FLOAT_FIELD(FLOAT);
		const Field DOUBLE_FIELD(DOUBLE);

		const Field STRING_FIELD(STRING);
		const Field OBJECT_FIELD(OBJECT);
	}

#endif
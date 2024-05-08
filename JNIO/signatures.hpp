#ifndef JNIO_SIGNATURES
    #define JNIO_SIGNATURES

    #include <string.h>

    #include "jnioexception.hpp"

    namespace jnio {

        class PureSignature {
            protected:
                char* signature;
                PureSignature() = default;
            
            public:
                explicit PureSignature(const char* signature);
                PureSignature(const PureSignature& ps);
                virtual ~PureSignature();

                virtual PureSignature& operator = (const PureSignature& ps2) noexcept;
                virtual bool operator == (const PureSignature& ps2) const noexcept;

                operator const char*() const noexcept;
                const char* getSignature() const noexcept;

            friend class ArraySignature;
        };

        class ComposedSignature : public PureSignature {
            public:
                explicit ComposedSignature(const char* signature);
                ComposedSignature(const PureSignature& ps);
                virtual ~ComposedSignature() = default;

                ComposedSignature& concat(const PureSignature& ps);
                ComposedSignature& operator + (const PureSignature& ps);
                ComposedSignature& operator += (const PureSignature& ps);
        };

        class Signature : public PureSignature {
            public:
                Signature() = delete;
                explicit Signature(const char* signature);
                Signature(const Signature& s);
                virtual ~Signature() = default;

                static const Signature BOOLEAN;
                static const Signature BYTE;
                static const Signature CHAR;
                static const Signature SHORT;
                static const Signature INT;
                static const Signature LONG;
                static const Signature FLOAT;
                static const Signature DOUBLE;

                static const Signature VOID;
        };

        class ObjectSignature : public PureSignature {
            public:
                ObjectSignature() = delete;
                ObjectSignature(const char* obj);
                ObjectSignature(const ObjectSignature& os);
                virtual ~ObjectSignature() = default;

                static const ObjectSignature STRING;
                static const ObjectSignature OBJECT;
        };

        class ArraySignature : public PureSignature {
            public:
                ArraySignature() = delete;
                ArraySignature(const char* obj, unsigned int order = 1);
                ArraySignature(const PureSignature& base, unsigned int order = 1);
                virtual ~ArraySignature() = default;

                static const ArraySignature BOOLEAN_ARRAY;
                static const ArraySignature BYTE_ARRAY;
                static const ArraySignature CHAR_ARRAY;
                static const ArraySignature SHORT_ARRAY;
                static const ArraySignature INT_ARRAY;
                static const ArraySignature LONG_ARRAY;
                static const ArraySignature FLOAT_ARRAY;
                static const ArraySignature DOUBLE_ARRAY;

                static const ArraySignature STRING_ARRAY;
                static const ArraySignature OBJECT_ARRAY;

                PureSignature getBaseSignature() const noexcept;
        };

        class MethodSignature {
            private:
                char* signature;

            public:
                MethodSignature() = default;
                explicit MethodSignature(const char* signature);
                MethodSignature(const PureSignature& returntype);
                MethodSignature(const PureSignature& returntype, const ComposedSignature& args);
                MethodSignature(const MethodSignature& ms);
                ~MethodSignature();

                static const MethodSignature BOOLEAN_METHOD;
                static const MethodSignature BYTE_METHOD;
                static const MethodSignature SHORT_METHOD;
                static const MethodSignature CHAR_METHOD;
                static const MethodSignature INT_METHOD;
                static const MethodSignature LONG_METHOD;
                static const MethodSignature FLOAT_METHOD;
                static const MethodSignature DOUBLE_METHOD;
                
                static const MethodSignature VOID_METHOD;

                static const MethodSignature STRING_METHOD;

                static const MethodSignature MAIN;

                static const MethodSignature TO_STRING;
                static const MethodSignature EQUALS;
                static const MethodSignature HASH_CODE;
                static const MethodSignature WAIT;
                static const MethodSignature NOTIFY;

                virtual MethodSignature& operator = (const MethodSignature& ms) noexcept;
                virtual bool operator == (const MethodSignature& ms) const noexcept;

                operator const char*() const noexcept;
                const char* getSignature() const noexcept;

                const PureSignature returnType() const noexcept;
            
            friend class ConstructorSignature;
        };

        class ConstructorSignature : public MethodSignature {
            public:
                ConstructorSignature();
                explicit ConstructorSignature(const char* signature);
                ConstructorSignature(const ComposedSignature& args);
                ConstructorSignature(const ConstructorSignature& cs);
                ~ConstructorSignature() = default;

                static const ConstructorSignature DEFAULT;
        };

        class FieldSignature {
            private:
                char* signature;

            public:
                FieldSignature() = default;
                explicit FieldSignature(const char* signature);
                FieldSignature(const PureSignature& type);
                FieldSignature(const FieldSignature& fs);
                ~FieldSignature();

                static const FieldSignature BOOLEAN_FIELD;
                static const FieldSignature BYTE_FIELD;
                static const FieldSignature SHORT_FIELD;
                static const FieldSignature CHAR_FIELD;
                static const FieldSignature INT_FIELD;
                static const FieldSignature LONG_FIELD;
                static const FieldSignature FLOAT_FIELD;
                static const FieldSignature DOUBLE_FIELD;

                static const FieldSignature STRING_FIELD;

                virtual FieldSignature& operator = (const FieldSignature& ms) noexcept;
                virtual bool operator == (const FieldSignature& ms) const noexcept;

                operator const char*() const noexcept;
                const char* getSignature() const noexcept;
        };
    }

#endif
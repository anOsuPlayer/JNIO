#include "signatures.hpp"

namespace jnio {

    PureSignature::PureSignature(const char* signature) {
        size_t len = strlen(signature);
        this->signature = new char[len+1];
        this->signature[len] = '\0';

        for (size_t i = 0; i < len; i++) {
            this->signature[i] = signature[i];
        }
    }
    PureSignature::PureSignature(const PureSignature& s) : PureSignature(s.getSignature()) {
    }

    PureSignature::~PureSignature() {
        delete[] this->signature;
    }

    PureSignature& PureSignature::operator = (const PureSignature& ps2) noexcept {
        const char* sign = ps2.getSignature();
        size_t len = strlen(sign);
        this->signature = new char[len+1]; this->signature[len] = '\0';

        for (size_t i = 0; i < len; i++) {
            this->signature[i] = sign[i];
        }

        return *this;
    }
    bool PureSignature::operator == (const PureSignature& ps2) const noexcept {
        return (strcmp(this->signature, ps2.signature) == 0);
    }

    PureSignature::operator const char*() const noexcept {
        return this->signature;
    }
    const char* PureSignature::getSignature() const noexcept {
        return this->signature;
    }

    ComposedSignature::ComposedSignature(const PureSignature& ps) : PureSignature(ps) {
    }
    ComposedSignature::ComposedSignature(const char* signature) : PureSignature(signature) {
    }

    ComposedSignature& ComposedSignature::concat(const PureSignature& ps) {
        if (ps == Signature::VOID) {
            throw jnio_exception("A Void Signature cannot be part of a ComposedSignature.");
        }

        size_t thislen = strlen(this->signature), len = strlen(ps.getSignature());
        char* newSign = new char[thislen+len+1]; newSign[thislen+len] = '\0';
        for (size_t i = 0; i < thislen; i++) {
            newSign[i] = this->signature[i];
        }
        for (size_t i = thislen; i < thislen+len; i++) {
            newSign[i] = ps.getSignature()[i-thislen];
        }
        delete[] this->signature;
        this->signature = newSign;

        return *this;
    }
    ComposedSignature& ComposedSignature::operator + (const PureSignature& ps) {
        return this->concat(ps);
    }
    ComposedSignature& ComposedSignature::operator += (const PureSignature& ps) {
        return this->concat(ps);
    }

    Signature::Signature(const char* signature) : PureSignature(signature) {
    }
    Signature::Signature(const Signature& s) : PureSignature(s) {
    }

    const Signature Signature::BOOLEAN = Signature("Z");
    const Signature Signature::BYTE = Signature("B");
    const Signature Signature::CHAR = Signature("C");
    const Signature Signature::SHORT = Signature("S");
    const Signature Signature::INT = Signature("I");
    const Signature Signature::LONG = Signature("J");
    const Signature Signature::FLOAT = Signature("F");
    const Signature Signature::DOUBLE = Signature("D");

    const Signature Signature::VOID = Signature("V");

    ObjectSignature::ObjectSignature(const char* obj) {
        if (obj[0] == 'L' || obj[0] == '[') {
            size_t len = strlen(obj);
            this->signature = new char[len+1]; this->signature[len] = '\0';
            for (size_t i = 0; i < len; i++) {
                this->signature[i] = obj[i];
            }
        }
        size_t len = strlen(obj);
        this->signature = new char[len+3];
        this->signature[0] = 'L';
        this->signature[len+1] = ';'; this->signature[len+2] = '\0';

        for (size_t i = 1; i < len+1; i++) {
            this->signature[i] = (obj[i-1] == '.') ? '/' : obj[i-1];
        }
    }
    ObjectSignature::ObjectSignature(const ObjectSignature& os) : PureSignature(os) {
    }

    const ObjectSignature ObjectSignature::STRING = ObjectSignature("java.lang.String");
    const ObjectSignature ObjectSignature::OBJECT = ObjectSignature("java.lang.Object");

    ArraySignature::ArraySignature(const char* obj, size_t order) {
        if (order == 0) {
            throw jnio_exception("Unable to create a Signature referring to a 0-dimensions array.");
        }

        size_t len = strlen(obj);
        this->signature = new char[len+3+order];
        for (size_t i = 0; i < order; i++) {
            this->signature[i] = '[';
        }
        this->signature[order] = 'L';
        this->signature[len+1+order] = ';'; this->signature[len+2+order] = '\0';

        for (size_t i = 1+order; i < len+1+order; i++) {
            this->signature[i] = (obj[i-1-order] == '.') ? '/' : obj[i-1-order];
        }
    }
    ArraySignature::ArraySignature(const PureSignature& base, size_t order) {
        if (order == 0) {
            throw jnio_exception("Unable to create a Signature referring to a 0-dimensions array.");
        }
        if (base == Signature::VOID) {
            throw jnio_exception("Cannot create an ArraySignature of a void array.");
        }

        const char* sign = base.getSignature();
        size_t len = strlen(sign);
        this->signature = new char[len+1+order];
        for (size_t i = 0; i < order; i++) {
            this->signature[i] = '[';
        }
        this->signature[len+order] = '\0';

        for (size_t i = order; i < len+order; i++) {
            this->signature[i] = sign[i-order];
        }
    }

    const ArraySignature ArraySignature::BOOLEAN_ARRAY = ArraySignature(Signature::BOOLEAN);
    const ArraySignature ArraySignature::BYTE_ARRAY = ArraySignature(Signature::BYTE);
    const ArraySignature ArraySignature::CHAR_ARRAY = ArraySignature(Signature::CHAR);
    const ArraySignature ArraySignature::SHORT_ARRAY = ArraySignature(Signature::SHORT);
    const ArraySignature ArraySignature::INT_ARRAY = ArraySignature(Signature::INT);
    const ArraySignature ArraySignature::LONG_ARRAY = ArraySignature(Signature::LONG);
    const ArraySignature ArraySignature::FLOAT_ARRAY = ArraySignature(Signature::FLOAT);
    const ArraySignature ArraySignature::DOUBLE_ARRAY = ArraySignature(Signature::DOUBLE);

    const ArraySignature ArraySignature::STRING_ARRAY = ArraySignature(ObjectSignature::STRING);
    const ArraySignature ArraySignature::OBJECT_ARRAY = ArraySignature(ObjectSignature::OBJECT);

    PureSignature ArraySignature::getBaseSignature() const noexcept {
        size_t i = 0, len = strlen(this->signature);
        for (const char* ch = this->signature; *ch == '['; ch++) { i++; }
        char sign[len-i+1];
        for (size_t e = 0; e < len-i+1; e++) {
            sign[e] = this->signature[e+i];
        }
        sign[len-i+1] = '\0';

        return PureSignature(sign);
    }

    MethodSignature::MethodSignature(const char* signature) {
        size_t len = strlen(signature);
        this->signature = new char[len+1]; this->signature[len] = '\0';
        for (size_t i = 0; i < len; i++) {
            this->signature[i] = signature[i];
        }
    }
    MethodSignature::MethodSignature(const PureSignature& returntype) {
        const char* sign = returntype.getSignature();
        size_t len = strlen(sign);
        char* fullname = new char[len+3];
        fullname[0] = '('; fullname[1] = ')';
        fullname[len+2] = '\0';

        for (size_t i = 2; i < len+2; i++) {
            fullname[i] = sign[i-2];
        }

        this->signature = fullname;
    }
    MethodSignature::MethodSignature(const PureSignature& returntype, const ComposedSignature& args) {
        size_t retlen = strlen(returntype), arglen = strlen(args);
        this->signature = new char[retlen+arglen+3]; this->signature[retlen+arglen+2] = '\0';
        this->signature[0] = '('; this->signature[arglen+1] = ')';

        for (size_t i = 1; i <= arglen; i++) {
            this->signature[i] = args[i-1];
        }
        for (size_t i = arglen+2; i < arglen+2+retlen; i++) {
            this->signature[i] = returntype[i-arglen-2];
        }
    }
    MethodSignature::MethodSignature(const MethodSignature& ms) {
        const char* sign = ms.getSignature();
        size_t len = strlen(sign);
        this->signature = new char[len+1]; this->signature[len] = '\0';

        for (size_t i = 0; i < len; i++) {
            this->signature[i] = sign[i];
        }
    }

    MethodSignature::~MethodSignature() {
        delete[] this->signature;
    }

    const MethodSignature MethodSignature::BOOLEAN_METHOD = MethodSignature(Signature::BOOLEAN);
    const MethodSignature MethodSignature::BYTE_METHOD = MethodSignature(Signature::BYTE);
    const MethodSignature MethodSignature::SHORT_METHOD = MethodSignature(Signature::SHORT);
    const MethodSignature MethodSignature::CHAR_METHOD = MethodSignature(Signature::CHAR);
    const MethodSignature MethodSignature::INT_METHOD = MethodSignature(Signature::INT);
    const MethodSignature MethodSignature::LONG_METHOD = MethodSignature(Signature::LONG);
    const MethodSignature MethodSignature::FLOAT_METHOD = MethodSignature(Signature::FLOAT);
    const MethodSignature MethodSignature::DOUBLE_METHOD = MethodSignature(Signature::DOUBLE);

    const MethodSignature MethodSignature::VOID_METHOD = MethodSignature(Signature::VOID);
    
    const MethodSignature MethodSignature::STRING_METHOD = MethodSignature(ObjectSignature::STRING);

    const MethodSignature MethodSignature::MAIN = MethodSignature(Signature::VOID, ComposedSignature(ArraySignature(ObjectSignature::STRING)));
    
    const MethodSignature MethodSignature::TO_STRING = MethodSignature(ObjectSignature::STRING);
    const MethodSignature MethodSignature::EQUALS = MethodSignature(Signature::BOOLEAN, ComposedSignature(ObjectSignature::OBJECT));
    const MethodSignature MethodSignature::HASH_CODE = MethodSignature(Signature::INT);
    const MethodSignature MethodSignature::WAIT = MethodSignature(Signature::VOID);
    const MethodSignature MethodSignature::NOTIFY = MethodSignature(Signature::VOID);

    MethodSignature& MethodSignature::operator = (const MethodSignature& ms) noexcept {
        const char* sign = ms.getSignature();
        size_t len = strlen(sign);
        this->signature = new char[len+1]; this->signature[len] = '\0';

        for (size_t i = 0; i < len; i++) {
            this->signature[i] = sign[i];
        }

        return *this;
    }
    bool MethodSignature::operator == (const MethodSignature& ms) const noexcept {
        return (strcmp(this->signature, ms.signature) == 0);
    }

    MethodSignature::operator const char*() const noexcept {
        return this->signature;
    }
    const char* MethodSignature::getSignature() const noexcept {
        return this->signature;
    }

    const PureSignature MethodSignature::returnType() const noexcept {
        size_t len = strlen(this->signature); char* begin = this->signature;
        for (int i = 0; *begin != ')'; i++) { begin++; }
        if (*(begin+1) == '[' || *(begin+1) == 'L') {
            return ObjectSignature("");
        }
        else {
            switch (*(begin+1)) {
                case 'Z' : return Signature::BOOLEAN;
                case 'B' : return Signature::BYTE;
                case 'S' : return Signature::SHORT;
                case 'C' : return Signature::BYTE;
                case 'I' : return Signature::INT;
                case 'J' : return Signature::LONG;
                case 'F' : return Signature::FLOAT;
                case 'D' : return Signature::DOUBLE;
                case 'V' : return Signature::VOID;
            }
        }
        return Signature::VOID;
    }

    ConstructorSignature::ConstructorSignature() : MethodSignature(Signature::VOID) {
    }
    ConstructorSignature::ConstructorSignature(const char* signature) : MethodSignature(signature) {
        if (signature[strlen(signature)-1] != 'V') {
            throw jnio_exception("ConstructorSignatures must not state any return type other than void: \"(...)V\"");
        }  
    }
    ConstructorSignature::ConstructorSignature(const ComposedSignature& args) : MethodSignature(Signature::VOID, args) {
    }
    ConstructorSignature::ConstructorSignature(const ConstructorSignature& cs) : MethodSignature(cs) {
    }

    const ConstructorSignature ConstructorSignature::DEFAULT = ConstructorSignature();

    FieldSignature::FieldSignature(const char* signature) {
        size_t len = strlen(signature);
        this->signature = new char[len+1]; this->signature[len] = '\0';
        
        bool isMethod = false;
        for (size_t i = 0; i < len; i++) {
            this->signature[i] = signature[i];
            if (signature[i] == '(' || signature[i] == ')') {
                isMethod = true;
                break;
            }
        }

        if (isMethod) {
            throw jnio_exception("FieldSignatures must not contain any method-like declaration.");
        }
    }
    FieldSignature::FieldSignature(const PureSignature& type) {
        const char* typeStr = type.getSignature();
        size_t len = strlen(type);
        this->signature = new char[len+1]; this->signature[len] = '\0';

        for (size_t i = 0; i < len; i++) {
            this->signature[i] = typeStr[i];
        }
    }
    FieldSignature::FieldSignature(const FieldSignature& fs) {
        this->signature = fs.signature;
    }

    FieldSignature::~FieldSignature() {
        delete[] this->signature;
    }

    const FieldSignature FieldSignature::BOOLEAN_FIELD = FieldSignature(Signature::BOOLEAN);
    const FieldSignature FieldSignature::BYTE_FIELD = FieldSignature(Signature::BYTE);
    const FieldSignature FieldSignature::SHORT_FIELD = FieldSignature(Signature::SHORT);
    const FieldSignature FieldSignature::CHAR_FIELD = FieldSignature(Signature::CHAR);
    const FieldSignature FieldSignature::INT_FIELD = FieldSignature(Signature::INT);
    const FieldSignature FieldSignature::LONG_FIELD = FieldSignature(Signature::LONG);
    const FieldSignature FieldSignature::FLOAT_FIELD = FieldSignature(Signature::FLOAT);
    const FieldSignature FieldSignature::DOUBLE_FIELD = FieldSignature(Signature::DOUBLE);

    const FieldSignature FieldSignature::STRING_FIELD = FieldSignature(ObjectSignature::STRING);

    FieldSignature& FieldSignature::operator = (const FieldSignature& ms) noexcept {
        const char* sign = ms.getSignature();
        size_t len = strlen(sign);
        this->signature = new char[len+1]; this->signature[len] = '\0';

        for (size_t i = 0; i < len; i++) {
            this->signature[i] = sign[i];
        }

        return *this;
    }
    bool FieldSignature::operator == (const FieldSignature& ms) const noexcept {
        return (strcmp(this->signature, ms.signature) == 0);
    }

    FieldSignature::operator const char*() const noexcept {
        return this->signature;
    }
    const char* FieldSignature::getSignature() const noexcept {
        return this->signature;
    }
}
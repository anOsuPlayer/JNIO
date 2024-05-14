#include "signatures.hpp"

namespace jnio {

    pure_signature::pure_signature(const char* signature) {
        size_t len = strlen(signature);
        this->signature = new char[len+1];
        this->signature[len] = '\0';

        for (size_t i = 0; i < len; i++) {
            this->signature[i] = signature[i];
        }
    }
    pure_signature::pure_signature(const pure_signature& s) : pure_signature(s.get_signature()) {
    }

    pure_signature::~pure_signature() {
        delete[] this->signature;
    }

    pure_signature& pure_signature::operator = (const pure_signature& ps2) noexcept {
        const char* sign = ps2.get_signature();
        size_t len = strlen(sign);
        this->signature = new char[len+1]; this->signature[len] = '\0';

        for (size_t i = 0; i < len; i++) {
            this->signature[i] = sign[i];
        }

        return *this;
    }
    bool pure_signature::operator == (const pure_signature& ps2) const noexcept {
        return (strcmp(this->signature, ps2.signature) == 0);
    }

    pure_signature::operator const char*() const noexcept {
        return this->signature;
    }
    const char* pure_signature::get_signature() const noexcept {
        return this->signature;
    }

    composed_signature::composed_signature(const pure_signature& ps) : pure_signature(ps) {
    }
    composed_signature::composed_signature(const char* signature) : pure_signature(signature) {
    }

    composed_signature& composed_signature::concat(const pure_signature& ps) {
        if (ps == signature::VOID) {
            throw jnio_exception("A Void Signature cannot be part of a ComposedSignature.");
        }

        size_t thislen = strlen(this->signature), len = strlen(ps.get_signature());
        char* newSign = new char[thislen+len+1]; newSign[thislen+len] = '\0';
        for (size_t i = 0; i < thislen; i++) {
            newSign[i] = this->signature[i];
        }
        for (size_t i = thislen; i < thislen+len; i++) {
            newSign[i] = ps.get_signature()[i-thislen];
        }
        delete[] this->signature;
        this->signature = newSign;

        return *this;
    }
    composed_signature& composed_signature::operator + (const pure_signature& ps) {
        return this->concat(ps);
    }
    composed_signature& composed_signature::operator += (const pure_signature& ps) {
        return this->concat(ps);
    }

    signature::signature(const char* signature) : pure_signature(signature) {
    }
    signature::signature(const signature& s) : pure_signature(s) {
    }

    const signature signature::BOOLEAN = signature("Z");
    const signature signature::BYTE = signature("B");
    const signature signature::CHAR = signature("C");
    const signature signature::SHORT = signature("S");
    const signature signature::INT = signature("I");
    const signature signature::LONG = signature("J");
    const signature signature::FLOAT = signature("F");
    const signature signature::DOUBLE = signature("D");

    const signature signature::VOID = signature("V");

    object_signature::object_signature(const char* obj) {
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
    object_signature::object_signature(const object_signature& os) : pure_signature(os) {
    }

    const object_signature object_signature::STRING = object_signature("java.lang.String");
    const object_signature object_signature::OBJECT = object_signature("java.lang.Object");

    array_signature::array_signature(const char* obj, unsigned int order) {
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
    array_signature::array_signature(const pure_signature& base, unsigned int order) {
        if (order == 0) {
            throw jnio_exception("Unable to create a Signature referring to a 0-dimensions array.");
        }
        if (base == signature::VOID) {
            throw jnio_exception("Cannot create an array_signature of a void array.");
        }

        const char* sign = base.get_signature();
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

    const array_signature array_signature::BOOLEAN_ARRAY = array_signature(signature::BOOLEAN);
    const array_signature array_signature::BYTE_ARRAY = array_signature(signature::BYTE);
    const array_signature array_signature::CHAR_ARRAY = array_signature(signature::CHAR);
    const array_signature array_signature::SHORT_ARRAY = array_signature(signature::SHORT);
    const array_signature array_signature::INT_ARRAY = array_signature(signature::INT);
    const array_signature array_signature::LONG_ARRAY = array_signature(signature::LONG);
    const array_signature array_signature::FLOAT_ARRAY = array_signature(signature::FLOAT);
    const array_signature array_signature::DOUBLE_ARRAY = array_signature(signature::DOUBLE);

    const array_signature array_signature::STRING_ARRAY = array_signature(object_signature::STRING);
    const array_signature array_signature::OBJECT_ARRAY = array_signature(object_signature::OBJECT);

    pure_signature array_signature::getBaseSignature() const noexcept {
        size_t i = 0, len = strlen(this->signature);
        for (const char* ch = this->signature; *ch == '['; ch++) { i++; }
        char sign[len-i+1];
        for (size_t e = 0; e < len-i+1; e++) {
            sign[e] = this->signature[e+i];
        }
        sign[len-i+1] = '\0';

        return pure_signature(sign);
    }

    method_signature::method_signature(const char* signature) {
        size_t len = strlen(signature);
        this->signature = new char[len+1]; this->signature[len] = '\0';
        for (size_t i = 0; i < len; i++) {
            this->signature[i] = signature[i];
        }
    }
    method_signature::method_signature(const pure_signature& returntype) {
        const char* sign = returntype.get_signature();
        size_t len = strlen(sign);
        char* fullname = new char[len+3];
        fullname[0] = '('; fullname[1] = ')';
        fullname[len+2] = '\0';

        for (size_t i = 2; i < len+2; i++) {
            fullname[i] = sign[i-2];
        }

        this->signature = fullname;
    }
    method_signature::method_signature(const pure_signature& returntype, const composed_signature& args) {
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
    method_signature::method_signature(const method_signature& ms) {
        const char* sign = ms.get_signature();
        size_t len = strlen(sign);
        this->signature = new char[len+1]; this->signature[len] = '\0';

        for (size_t i = 0; i < len; i++) {
            this->signature[i] = sign[i];
        }
    }

    method_signature::~method_signature() {
        delete[] this->signature;
    }

    const method_signature method_signature::BOOLEAN_METHOD = method_signature(signature::BOOLEAN);
    const method_signature method_signature::BYTE_METHOD = method_signature(signature::BYTE);
    const method_signature method_signature::SHORT_METHOD = method_signature(signature::SHORT);
    const method_signature method_signature::CHAR_METHOD = method_signature(signature::CHAR);
    const method_signature method_signature::INT_METHOD = method_signature(signature::INT);
    const method_signature method_signature::LONG_METHOD = method_signature(signature::LONG);
    const method_signature method_signature::FLOAT_METHOD = method_signature(signature::FLOAT);
    const method_signature method_signature::DOUBLE_METHOD = method_signature(signature::DOUBLE);

    const method_signature method_signature::VOID_METHOD = method_signature(signature::VOID);
    
    const method_signature method_signature::STRING_METHOD = method_signature(object_signature::STRING);

    const method_signature method_signature::MAIN = method_signature(signature::VOID, composed_signature(array_signature(object_signature::STRING)));
    
    const method_signature method_signature::TO_STRING = method_signature(object_signature::STRING);
    const method_signature method_signature::EQUALS = method_signature(signature::BOOLEAN, composed_signature(object_signature::OBJECT));
    const method_signature method_signature::HASH_CODE = method_signature(signature::INT);
    const method_signature method_signature::WAIT = method_signature(signature::VOID);
    const method_signature method_signature::NOTIFY = method_signature(signature::VOID);

    method_signature& method_signature::operator = (const method_signature& ms) noexcept {
        const char* sign = ms.get_signature();
        size_t len = strlen(sign);
        this->signature = new char[len+1]; this->signature[len] = '\0';

        for (size_t i = 0; i < len; i++) {
            this->signature[i] = sign[i];
        }

        return *this;
    }
    bool method_signature::operator == (const method_signature& ms) const noexcept {
        return (strcmp(this->signature, ms.signature) == 0);
    }

    method_signature::operator const char*() const noexcept {
        return this->signature;
    }
    const char* method_signature::get_signature() const noexcept {
        return this->signature;
    }

    const pure_signature method_signature::returnType() const noexcept {
        size_t len = strlen(this->signature); char* begin = this->signature;
        for (int i = 0; *begin != ')'; i++) { begin++; }
        if (*(begin+1) == '[' || *(begin+1) == 'L') {
            return object_signature("");
        }
        else {
            switch (*(begin+1)) {
                case 'Z' : return signature::BOOLEAN;
                case 'B' : return signature::BYTE;
                case 'S' : return signature::SHORT;
                case 'C' : return signature::BYTE;
                case 'I' : return signature::INT;
                case 'J' : return signature::LONG;
                case 'F' : return signature::FLOAT;
                case 'D' : return signature::DOUBLE;
                case 'V' : return signature::VOID;
            }
        }
        return signature::VOID;
    }

    constructor_signature::constructor_signature() : method_signature(signature::VOID) {
    }
    constructor_signature::constructor_signature(const char* signature) : method_signature(signature) {
        if (signature[strlen(signature)-1] != 'V') {
            throw jnio_exception("ConstructorSignatures must not state any return type other than void: \"(...)V\"");
        }  
    }
    constructor_signature::constructor_signature(const composed_signature& args) : method_signature(signature::VOID, args) {
    }
    constructor_signature::constructor_signature(const constructor_signature& cs) : method_signature(cs) {
    }

    const constructor_signature constructor_signature::DEFAULT = constructor_signature();

    field_signature::field_signature(const char* signature) {
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
    field_signature::field_signature(const pure_signature& type) {
        const char* typeStr = type.get_signature();
        size_t len = strlen(type);
        this->signature = new char[len+1]; this->signature[len] = '\0';

        for (size_t i = 0; i < len; i++) {
            this->signature[i] = typeStr[i];
        }
    }
    field_signature::field_signature(const field_signature& fs) {
        this->signature = fs.signature;
    }

    field_signature::~field_signature() {
        delete[] this->signature;
    }

    const field_signature field_signature::BOOLEAN_FIELD = field_signature(signature::BOOLEAN);
    const field_signature field_signature::BYTE_FIELD = field_signature(signature::BYTE);
    const field_signature field_signature::SHORT_FIELD = field_signature(signature::SHORT);
    const field_signature field_signature::CHAR_FIELD = field_signature(signature::CHAR);
    const field_signature field_signature::INT_FIELD = field_signature(signature::INT);
    const field_signature field_signature::LONG_FIELD = field_signature(signature::LONG);
    const field_signature field_signature::FLOAT_FIELD = field_signature(signature::FLOAT);
    const field_signature field_signature::DOUBLE_FIELD = field_signature(signature::DOUBLE);

    const field_signature field_signature::STRING_FIELD = field_signature(object_signature::STRING);

    field_signature& field_signature::operator = (const field_signature& ms) noexcept {
        const char* sign = ms.get_signature();
        size_t len = strlen(sign);
        this->signature = new char[len+1]; this->signature[len] = '\0';

        for (size_t i = 0; i < len; i++) {
            this->signature[i] = sign[i];
        }

        return *this;
    }
    bool field_signature::operator == (const field_signature& ms) const noexcept {
        return (strcmp(this->signature, ms.signature) == 0);
    }

    field_signature::operator const char*() const noexcept {
        return this->signature;
    }
    const char* field_signature::get_signature() const noexcept {
        return this->signature;
    }
}
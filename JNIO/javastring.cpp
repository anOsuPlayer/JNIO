#include "javastring.hpp"

namespace jnio {

    java_string::java_string(const std::string& str, size_t init, size_t end) {
		this->text = str.substr(init, end);
    }

    java_string::java_string(java_char_array& charr, size_t init, size_t end) {
		this->text = std::string((const char*) charr.get_elements()).substr(init, end);
    }

    java_string::java_string(const jstring& str, size_t init, size_t end) {
		const char* ch = JNIOEnv->GetStringUTFChars(str, &FALSE);
		this->text = std::string(ch).substr(init, end);
		JNIOEnv->ReleaseStringUTFChars(str, ch);
    }

    java_string::java_string(const java_string& str, size_t init, size_t end) {
		this->text = str.text.substr(init, end);
    }

    java_string& java_string::operator = (const jstring& str) {
        this->text.clear();

		const char* ch = JNIOEnv->GetStringUTFChars(str, &FALSE);
		this->text = std::string(ch);
		JNIOEnv->ReleaseStringUTFChars(str, ch);

        return *this;
    }

    char& java_string::operator [] (size_t index) {
        if (index >= this->length()) {
            throw std::out_of_range("The given index goes out of bounds for this java_string.");
        }
        return this->text[index];
    }

    size_t java_string::length() const noexcept {
        return this->text.length();
    }

	java_object java_string::as_object() const noexcept {
        return java_object(*this);
    }

    java_char_array java_string::to_char_array() const noexcept {
        return java_char_array(this->length(), std::wstring(this->text.begin(), this->text.end()).c_str());
    }

	java_string::operator jstring() const noexcept {
        return JNIOEnv->NewStringUTF(this->text.c_str());
    }

    const std::string& java_string::string() const noexcept {
        return this->text;
    }

	const char* java_string::c_str() const noexcept {
        return this->text.c_str();
    }

	bool java_string::operator == (const java_string& str) const noexcept {
        return this->text == str.text;
    }

    bool java_string::operator == (jstring str) const noexcept {
        const char* ch = JNIOEnv->GetStringUTFChars(str, &FALSE);
		bool res = this->text == ch;
		JNIOEnv->ReleaseStringUTFChars(str, ch);

		return res;
    }
}
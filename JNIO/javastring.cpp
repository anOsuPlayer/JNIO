#include "javastring.hpp"

namespace jnio {

    java_string::java_string(JNIEnv* env) {
        this->env = env;
    }

    java_string::java_string(JNIEnv* env, const std::string& str, size_t init, size_t end) {
        this->env = env;
		this->text = str.substr(init, end);
    }

    java_string::java_string(JNIEnv* env, java_char_array& charr, size_t init, size_t end) {
		this->env = env;
		this->text = std::string((const char*) charr.get_elements()).substr(init, end);
    }

    java_string::java_string(JNIEnv* env, const jstring& str, size_t init, size_t end) {
        this->env = env;
		const char* ch = env->GetStringUTFChars(str, &FALSE);
		this->text = std::string(ch).substr(init, end);
		env->ReleaseStringUTFChars(str, ch);
    }

    java_string::java_string(const java_string& str, size_t init, size_t end) {
        this->env = str.env;
		this->text = str.text.substr(init, end);
    }

    java_string& java_string::operator = (const jstring& str) {
        this->text.clear();

		const char* ch = env->GetStringUTFChars(str, &FALSE);
		this->text = std::string(ch);
		env->ReleaseStringUTFChars(str, ch);

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
        return java_object(this->env, *this);
    }

    java_char_array java_string::to_char_array() const noexcept {
        return java_char_array(this->env, this->length(), std::wstring(this->text.begin(), this->text.end()).c_str());
    }

	java_string::operator jstring() const noexcept {
        return env->NewStringUTF(this->text.c_str());
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
        const char* ch = env->GetStringUTFChars(str, &FALSE);
		bool res = this->text == ch;
		env->ReleaseStringUTFChars(str, ch);

		return res;
    }
}
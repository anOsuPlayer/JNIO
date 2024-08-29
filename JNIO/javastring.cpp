#include "javastring.hpp"

namespace jnio {

    JavaString::JavaString(JNIEnv* env) {
        this->env = env;
    }

    JavaString::JavaString(JNIEnv* env, const std::string& str, size_t init, size_t end) {
        this->env = env;
		this->text = str.substr(init, end);
    }

    JavaString::JavaString(JNIEnv* env, JavaCharArray& charr, size_t init, size_t end) {
		this->env = env;
		this->text = std::string((const char*) charr.get_elements()).substr(init, end);
    }

    JavaString::JavaString(JNIEnv* env, const jstring& str, size_t init, size_t end) {
        this->env = env;
		const char* ch = env->GetStringUTFChars(str, &FALSE);
		this->text = std::string(ch).substr(init, end);
		env->ReleaseStringUTFChars(str, ch);
    }

    JavaString::JavaString(const JavaString& str, size_t init, size_t end) {
        this->env = str.env;
		this->text = str.text.substr(init, end);
    }

    JavaString& JavaString::operator = (const jstring& str) {
        this->text.clear();

		const char* ch = env->GetStringUTFChars(str, &FALSE);
		this->text = std::string(ch);
		env->ReleaseStringUTFChars(str, ch);

        return *this;
    }

    char& JavaString::operator [] (size_t index) {
        if (index >= this->length()) {
            throw std::out_of_range("The given index goes out of bounds for this JavaString.");
        }
        return this->text[index];
    }

    size_t JavaString::length() const noexcept {
        return this->text.length();
    }

	JavaObject JavaString::asObject() const noexcept {
        return JavaObject(this->env, *this);
    }

    JavaCharArray JavaString::toCharArray() const noexcept {
        return JavaCharArray(this->env, this->length(), this->text.c_str());
    }

	JavaString::operator jstring() const noexcept {
        return env->NewStringUTF(this->text.c_str());
    }

    const std::string& JavaString::string() const noexcept {
        return this->text;
    }

	const char* JavaString::c_str() const noexcept {
        return this->text.c_str();
    }

	bool JavaString::operator == (const JavaString& str) const noexcept {
        return this->text == str.text;
    }

    bool JavaString::operator == (jstring str) const noexcept {
        const char* ch = env->GetStringUTFChars(str, &FALSE);
		bool res = this->text == ch;
		env->ReleaseStringUTFChars(str, ch);

		return res;
    }
}
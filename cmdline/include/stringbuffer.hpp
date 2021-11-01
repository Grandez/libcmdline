#pragma once
#include <sstream>

namespace jggtools {
	class stringbuffer {
		std::stringstream ss;
	public:
		stringbuffer() {};
		template <typename T> stringbuffer(T data) { ss << data; }
		template <typename T> stringbuffer& operator+(T data) {
			ss << data;
			return *this;
		}
		template <typename T> stringbuffer& operator<<(T data) {
			ss << data;
			return *this;
		}
		template <typename T> stringbuffer& operator<=(T data) {
			ss.str(data);
			return *this;
		}
		inline std::string toString() { return ss.str(); }
		inline const char * str()     { return ss.str().c_str(); }
		inline const char * value()   { return ss.str().c_str(); }
	};
}
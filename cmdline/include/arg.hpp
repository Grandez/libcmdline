#pragma once
#include <set>
#include "cmdline.hpp"

using namespace std;
using namespace cmdline;

namespace _cmdline {
	class Argument {
	public:
		string name;
		Source source   = Source::DEFAULT;
		Type   type     = Type::STRING;
		bool   multiple = false;
		string defValue;
		set<string> values; // avoid duplicates
		Argument() = delete;
		~Argument();
		Argument(Argument *arg);
		Argument(Parm *parm);
		Argument(const char *name, const char* value);
		Argument(const char *name, const char* value, Source source);
		Argument(const char* name, const char* value, Type type);
		Argument& setFromEnv(const char* value);
		Argument& setValue(bool value);
		Argument& setValue(const char* value);
		Argument& setValue(std::string value);
		Argument& addValue(std::string value);
		const char* getValue();
		vector<string>  getValues();
		bool            getBoolean();
		Argument&       initValues(vector<string> values);
		Argument&       makeUpper();
	protected:
		Argument&      addValues(vector<string> values);
	private:
		string first;
	};
}

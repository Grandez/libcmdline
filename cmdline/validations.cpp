#define _VALIDATIONS_CODE_

#include <iostream>
#include <vector>
#include <locale>
#include <iomanip>
#include <sstream>
#include <iterator>
#include <regex>
#include <time.h>
#include <filesystem>

#include "sal.h"
#include "tools.h"
#include "validations.h"
#include "cmdline_exceptions.hpp"


namespace cmdline {
	void        validateEntry(char* parm, char* prev) {
		if (strlen(parm) == 1) throw CmdLineException("Invalid Option", parm);
		//if (prev != nullptr) throw CmdLineException("Missing value", prev);
	}
	void  validateNumber(char* value) {
		try {
			std::stoll(std::string(value), nullptr, 0);
		}
		catch (std::exception ex) {
			throw CmdLineValueException(value, "expected number");
		}
	}
	inline void validateDecimal(char* value) {
		try {
			size_t pos;
			long double ld;
			long double *pld = &ld;
			std::stold(std::string(value), &pos);
		}
		catch (std::exception ex) {
			throw CmdLineValueException(value, "expected decimal");
		}
	}
	std::vector<int> validateTime(char* value) {
		std::regex pat{ "^[0-9]{1,2}:[0-9]{1,2}:[0-9]{1,2}$" };
		std::tm t;
		memset(&t, 0, sizeof(tm));
		bool match = std::regex_search(value, pat);
		if (!match) throw CmdLineValueException(value, "invalid time");
		std::vector<int> res = tokenizeNumber(value, (char*)":");
		if (res[0] < 0 || res[0] > 23) throw CmdLineValueException(value, "invalid time");
		for (int i = 1; i < 3; i++) 
			if (res[i] < 0 || res[i] > 59) throw CmdLineValueException(value, "invalid time");
		return res;
	}

	int isLeap(int year) {
		if (year < 100) year += 2000;
		if (year % 4) return 28;
		if ((year % 100) == 0) return ((year % 400) == 0 ? 29 : 28);
		return 29;
	}
	void validateDateValue(char *value, std::vector<int> dt) {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int day;

		if (dt[0] < 1 || dt[0] > 31) throw CmdLineValueException(value, "invalid date");
		if (dt[1] < 1 || dt[1] > 12) throw CmdLineValueException(value, "invalid date");
		day = (dt[1] == 2) ? isLeap(dt[2]) : days[dt[1] - 1];
		if (dt[0] > day) throw CmdLineValueException(value, "invalid date");
	}
	std::vector<int> validateDate(char* value) {
		std::vector<int> dt(3);
		std::regex pat1{ "^[0-9]{1,2}[/-]{1}[0-9]{1,2}[/-]{1}[0-9]{2,4}$" };
		std::regex pat2{ "^[0-9]{2,4}[/-]{1}[0-9]{1,2}[/-]{1}[0-9]{1,2}$" };
		std::regex pat;
		std::time_base::dateorder d = std::use_facet<std::time_get<char>>(
			std::locale()
			).date_order();
		switch (d) {
        		case std::time_base::no_order: 
		        case std::time_base::dmy: 
				case std::time_base::mdy: pat = pat1; break;
				default:                  pat = pat2;
		}
		bool match = std::regex_search(value, pat);
		if (!match) throw CmdLineValueException(value, "invalid date");
		std::vector<int> res = tokenizeNumber(value, (char*)"/-");
		switch (d) {
		       case std::time_base::dmy: dt = { res[0], res[1], res[2] }; break;
		       case std::time_base::mdy: dt = { res[1], res[0], res[2] }; break;
		       case std::time_base::ymd: dt = { res[2], res[1], res[0] }; break;
		       case std::time_base::ydm: dt = { res[2], res[0], res[1] }; break;
		       default:                  dt = { res[0], res[1], res[2] };
		}
		validateDateValue(value, dt);
		return dt;
	}
	inline void validateDir(char* value) {
		std::string start = "^";
		std::string drive = "(? <drive>[a - z] : ) ?";
		std::string path  = "(? <path>(? : [\\] ? (? : [\\w !#() - ] + | [.]{ 1,2 }) + ) * [\\]) ?";
		std::string end   = "$";
		std::regex pat{ start + drive + path + end};
		bool match = std::regex_search(value, pat);
		if (!match) throw CmdLineValueException(value, "expected path");
	}
	inline void  validateFile(char* value) {
		struct stat info;
		std::filesystem::path p = std::filesystem::path(value);
		if (stat((const char*)p.c_str(), &info) != 0) throw CmdLineValueException(value, "dir not found");
		if ((info.st_mode & S_IFREG) == 0)  throw CmdLineValueException(value, "is not a file");
	}
	inline void validateDirExist(char* value) {
		struct stat info;
		validateDir(value);
		std::filesystem::path p = std::filesystem::path(value);
		
		if (stat((const char *) p.c_str(), &info) != 0) throw CmdLineValueException(value, "dir not found");
		if ((info.st_mode & S_IFDIR) == 0)  throw CmdLineValueException(value, "is not a directory");
	}
	inline void  validateFileExist(char* value) {
		struct stat info;
		if (stat(value, &info) != 0) throw CmdLineValueException(value, "file not found");
		if (info.st_mode & S_IFDIR)  throw CmdLineValueException(value, "file is directory");
	}

	void          validateValue(char* value, cmdline::Type type) {
		/*
		void* obj = value;
		switch (type) {
		        case cmdline::NUMBER:      validateNumber(value); break;
		        case cmdline::DECIMAL:     validateDecimal(value); break;
		        case cmdline::DATE:        validateDate(value); break;
		        case cmdline::TIME:        validateTime(value); break;
		        case cmdline::DIR:         validateDir(value); break;
		        case cmdline::FILE:        validateFile(value); break;
		        case cmdline::DIR_EXISTS:  validateDirExist(value); break;
		        case cmdline::FILE_EXISTS: validateFileExist(value); break;
		}
		// return obj;
		*/
	}

}
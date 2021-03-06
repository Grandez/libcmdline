#pragma once

#include <filesystem>
#include <locale>
#include <filesystem>

#include "types.hpp"

using namespace std;

namespace NS2 {
    void        validateEntry      (const char* parm, const char* prev);
    void        validateValue      (const char* value, NS1::Type type);
    long        validateNumber     (const char* value);
    double      validateDecimal    (const char* value);
    long long   validateLongNumber (const char* value);
    long double validateLongDecimal(const char* value);
    filesystem::path        validateDir       (const char* value);
    filesystem::path        validateDirExist  (const char* value);
    filesystem::path        validateFile      (const char* value);
    filesystem::path        validateFileExist (const char* value);
    struct tm *validateTime      (const char* value);
    struct tm* validateDate      (const char* value, int fmt = -1);
    struct tm* validateDateTime  (const char* value);
    char *     validateTimestamp (const char* value);
    int         makeInteger      (const char* value);
    float       makeFloat        (const char* value);
    struct tm   makeTm           (const char* value);
    // Bridge
	bool  valMakeBoolean(const char *value);
 	bool  valMakeBoolean(std::string value);

/*
    template <typename T>
    T        getValue(const char* value, cmdline::Type type);
    template <typename T> T castValue(auto value, Type type);
    template <typename T> T castValue2(auto value);
*/
}

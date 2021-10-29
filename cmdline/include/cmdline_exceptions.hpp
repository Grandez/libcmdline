#pragma once

#include <stdexcept>
#include "msg_locale.h"

namespace cmdline {
	/**
	 * Base class for cmdline exceptions
	 *
	 * As library process argument from command line it inherits from invalid_argument
	 *
	 * @param msg Text to show
	 *
	 */

	class CmdLineNotFoundException : public std::runtime_error {
	public:
		CmdLineNotFoundException() = delete;
		CmdLineNotFoundException(const std::string& msg) : runtime_error(msg) {}
		CmdLineNotFoundException(const char* msg) : runtime_error(msg) {}
	};
	class CmdLineInvalidTypeException : public std::runtime_error {
	public:
		CmdLineInvalidTypeException() = delete;
		CmdLineInvalidTypeException(const std::string& msg) : runtime_error(msg) {}
		CmdLineInvalidTypeException(const char* msg)        : runtime_error(msg) {}
	};

	class CmdLineException : public std::invalid_argument {
	public:
		CmdLineException() = delete;
		CmdLineException(const std::string& msg) : invalid_argument(msg) { message = (char*)msg.c_str(); }
		CmdLineException(const char* msg) : invalid_argument(msg) { message = (char*)msg; }
		CmdLineException(const char* msg, const char* input) : invalid_argument(msg) {
			message = (char*)msg;
			parm = (char*)input;
		}
		CmdLineException(const char* msg, const char* input, const char* alt) : invalid_argument(msg) {
			message = (char*)msg;
			parm = (char*)input;
			this->alt = (char*)alt;
		}

	protected:
		char* message = (char*)"exceptions en library";
		char* parm = nullptr;
		char* alt =  nullptr;
	};
	class CmdLineParameterException : public CmdLineException {
	public:
		CmdLineParameterException() = delete;
		CmdLineParameterException(const char* value) : CmdLineException(TXT_ARG_INVALID) { parm = (char*) value; }
		CmdLineParameterException(const char* value, const char* desired) : CmdLineException(TXT_ARG_INVALID) {
			parm = (char*)value;
			alt = (char*)desired;
		}
	};
	class CmdLineValueException : public CmdLineException {
	public:
		CmdLineValueException() = delete;
		CmdLineValueException(const char* value, const char* desired) : CmdLineException(TXT_VAL_INVALID) {
			parm = (char*)value;
			alt = (char*)desired;
		}
	};
	
	class CmdLineDuplicateArgumentException : public CmdLineException {
	public:
		CmdLineDuplicateArgumentException() = delete;
		CmdLineDuplicateArgumentException(const char* value) : CmdLineException(TXT_ARG_SET) {
		};
	};
		
	/**
	 * Exception indicating HELP has been requested
	 */
	class HelpRequested : public CmdLineException {
	public:
		HelpRequested() : CmdLineException(TXT_HELP) {};
	};
	class HelpDetailedRequested : public CmdLineException {
	public:
		HelpDetailedRequested() : CmdLineException(TXT_HELP_DETAIL) {};
	};

}
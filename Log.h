#pragma once

#include "Common.h"

class Log
{
public:
	static std::mutex OutputMutex;

	enum class Severity
	{
		Notice,
		Warning,
		Critical
	};

	static void Write(const char* module, const char* text, Severity severity = Severity::Notice);

	static void WriteThreadSafe(const char* module, const char* text, Severity severity = Severity::Notice);
};

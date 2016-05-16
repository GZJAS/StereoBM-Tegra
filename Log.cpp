#include "Log.h"

Mutex Log::OutputMutex;

#define LOG_SEVERITY_TO_TEXT(X) ( (X) == Severity::Notice ? "[Notice]" : ( (X) == Severity::Warning ? "[Warning]" : "[Critical]" ) )

void Log::Write(const char* module, const char* text, Severity severity /*= Severity::Notice*/)
{
	std::cout << LOG_SEVERITY_TO_TEXT(severity) << " " << module << ": " << text << std::endl;

#if IS_DEBUG && _WIN32
	// NOTE: This buffer will crash for really long messages
	char buffer[255];
	char* _severity = LOG_SEVERITY_TO_TEXT(severity);

	sprintf_s(buffer, "%s %s: %s\n", _severity, module, text);
	OutputDebugStringA(buffer);
#endif
}

void Log::WriteThreadSafe(const char* module, const char* text, Severity severity /*= Severity::Notice*/)
{
	Log::OutputMutex.lock();

	Log::Write(module, text, severity);

	Log::OutputMutex.unlock();
}

#undef LOG_SEVERITY_TO_TEXT
#pragma once
#include <string>

class Logger
{
private:
	enum LogType
	{
		LogType_Error,
		LogType_Information,
		LogType_Verbose,
		LogType_Warning,
	};

public:
	static void Error(std::string message);
	static void Information(std::string message);
	static void Verbose(std::string message);
	static void Warning(std::string message);

private:
	static void Write(LogType logType, std::string message);
	static char ToString(LogType const &logType);
};


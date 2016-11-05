#include "Logger.h"

#include <iostream>

using namespace std;

void Logger::Error(std::string message)
{
	Write(LogType::LogType_Error, message);
}

void Logger::Information(std::string message)
{
	Write(LogType::LogType_Information, message);
}

void Logger::Verbose(std::string message)
{
	Write(LogType::LogType_Verbose, message);
}

void Logger::Warning(std::string message)
{
	Write(LogType::LogType_Warning, message);
}

void Logger::Write(LogType logType, std::string message)
{
	cerr << "[" << ToString(logType) << "] "
		<< message
		<< endl;
}

char Logger::ToString(LogType const & logType)
{
	switch (logType)
	{
	case LogType::LogType_Error:
		return 'E';
	case LogType::LogType_Information:
		return 'I';
	case LogType::LogType_Verbose:
		return 'V';
	case LogType::LogType_Warning:
		return 'W';
	default:
		throw exception("unknown type of LogType");
	}
}

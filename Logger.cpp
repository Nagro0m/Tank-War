#include "Logger.h"

Logger::Logger() {}

void Logger::PrintLog(const VerbosityType& _type, const string& _text, const string& _debug)
{
	if (WRITE_IN_LOG(_type))
	{
		const VerbosityData& _verbosity = VerbosityData(_type, _text, _debug);

		const string& _logText = _verbosity.GetFullText(false, true);
		WriteInLogs(_logText);
		if (WRITE_IN_CONSOLE(_type))
		{
			const string& _consoleText = _verbosity.GetFullText(true, true);
			WriteInConsole(_consoleText);
		}
	}
}

void Logger::WriteInLogs(const string& _text)
{
	ofstream _file("Logs/Log.txt", ios::app);
	if (_file.is_open())
	{
		_file << _text << endl;
		_file.close();
	}
}

void Logger::WriteInConsole(const string& _text)
{
	cout << _text << endl;
}
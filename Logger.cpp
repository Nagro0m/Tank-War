#include "Logger.h"
#include "TimerManager.h"

string Logger::logsPath = "Logs/log.txt";
ofstream Logger::stream = ofstream(logsPath, ios_base::app);

string VerbosityData::RetrieveFullText(const bool _useColor, const bool _useTime) const
{
	const string& _time = _useTime ? "<" + TimerManager<Seconds>::GetInstance().GetCurrentRealTime() + ">" : "";
	string _fullText = _time + GetPrefix(_useColor) + (_useColor ? color.GradientString(text) : text);
	if (USE_DEBUG || useDebug)
	{
		_fullText += (_useColor ? RESET WHITE"  " : "  ") + debug;
	}
	return _fullText + (_useColor ? RESET : "");

}

void Logger::PrintLog(const VerbosityType& _type,const string& _text, const string& _debug)
{
	if (WRITE_IN_LOG(_type))
	{
		const VerbosityData& _verbosity = VerbosityData(_type, _text, _debug);
		
		WriteInLogs(_verbosity.RetrieveFullText(false, true));
		if (WRITE_IN_CONSOLE(_type))
		{
			WriteInConsole(_verbosity.RetrieveFullText(true, true));
		}
	}
}

void Logger::WriteInLogs(const string& _text)
{
	stream << _text << endl;
}

void Logger::WriteInConsole(const string& _text)
{
	cout << _text << endl;
}


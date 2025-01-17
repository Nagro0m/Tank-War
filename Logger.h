#pragma once
#include "Colors.h"
#include "CustomException.h"

//#define DEBUG_FILE

#ifdef DEBUG_FILE
#define PATH __FILE__
#else
#define PATH __FUNCTION__
#endif

#ifdef DEBUG
#define USE_DEBUG 1
#else
#define USE_DEBUG 0
#endif

#define WRITE_IN_LOG(_verbosity) _type >= Log
#define WRITE_IN_CONSOLE(_verbosity) _type > Log

#define DEBUG_INFO "(" + string(PATH)  +  " | " + to_string(__LINE__) + ")"
#define LOG(_verbosity, _msg) Logger::PrintLog(_verbosity, _msg, DEBUG_INFO)


using namespace std;

enum VerbosityType
{
    VeryVerbose,
    Verbose,
    Log,
    Display,
    Warning,
    Error,
    Fatal,

    VT_COUNT
};


class VerbosityData
{
    Gradient color;
    string prefix;
    string text;
    string debug;
    bool useDebug;

private:
    __forceinline string GetPrefix(const bool _useColor) const
    {
        string _prefix = prefix;
        if (_useColor)
        {
            _prefix = RESET + color.GradientString(prefix) + RESET;
        }
        return "[" + _prefix + "]";
    }
public:
    __forceinline string RetrieveFullText(const bool _useColor = true, const bool _useTime = false) const;
public:
    VerbosityData(const VerbosityType& _type, const string& _text,
        const string& _debug)
    {
        ComputeUseDebug(_type);
        ComputePrefix(_type);
        ComputeColor(_type);
        text = _text;
        debug = _debug;
    }

private:
    void ComputePrefix(const VerbosityType& _type)
    {
        if (_type == VT_COUNT)
        {
            throw exception("Exception => Invalid VerbosityType");
        }

        const vector<string>& _verbosityTexts =
        {
            "VeryVerbose",
            "Verbose",
            "Log",
            "Display",
            "Warning",
            "Error",
            "Fatal",
        };

        prefix = _verbosityTexts[_type];
    }
    void ComputeColor(const VerbosityType& _type)
    {
        if (_type == VT_COUNT)
        {
            throw CustomException("Exception => Invalid VerbosityType");
        }

        const vector<Gradient>& _verbosityColors =
        {
            Gradient(ColorData(27, 27, 33), ColorData(37, 37, 51)),            //VERY VERBOSE
            Gradient(ColorData(55, 55, 61), ColorData(69, 69, 93)),            //VERBOSE
            Gradient(ColorData(100, 100, 119), ColorData(143, 143, 194)),    //LOG
            Gradient(ColorData(221, 221, 246), ColorData(122, 122, 236)),    //DISPLAY
            Gradient(ColorData(255, 231, 0), ColorData(255, 76, 17)),        //WARNING
            Gradient(ColorData(193, 6, 11), ColorData(249, 56, 67)),        //ERROR
            Gradient(ColorData(255, 0, 95), ColorData(118, 37, 184)),        //FATAL
        };

        color = _verbosityColors[_type];
    }
    void ComputeUseDebug(const VerbosityType& _type)
    {
        const set<VerbosityType>& _debugableVerbosity =
        {
            Warning,
            Error,
            Fatal,
        };
        useDebug = _debugableVerbosity.find(_type) != _debugableVerbosity.end();
    }

};

class Logger
{
    static string logsPath;
    static ofstream stream;

public:
    static void PrintLog(const VerbosityType& _type, const string& _text, const string& _debug = "");
private:

    static void WriteInLogs(const string& _text);
    static void WriteInConsole(const string& _text);
};


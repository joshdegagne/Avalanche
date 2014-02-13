#pragma once

#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <sstream>
#include <vector>
/////////////////////////////////////////////////////////////////////////////
//Labeling functions automatically format output for labeling of values
//Format: [Label] [Value]
//Label = L"Number of players: "
//Value = 1
//Output: Number of players: 1
/////////////////////////////////////////////////////////////////////////////
//Integers
static void writeLabelToConsole(const wchar_t* label, int value)
{
	writeTextToConsole(label, false);
	writeNumToConsole(value, true);
}
//Floats
static void writeLabelToConsole(const wchar_t* label, float value)
{
	writeTextToConsole(label, false);
	writeNumToConsole(value, true);
}

/////////////////////////////////////////////////////////////////////////////
//These functions are more manual. You give a wchar_t*, int, or float and
//prints to the debug console. You can also choose to specify if you do not
//want the function to print a new line after your desired output
/////////////////////////////////////////////////////////////////////////////
//Integers
static void writeNumToConsole (int input, bool printNewLineAfter = true)
{
	std::wostringstream oss;
	std::wstring ws;
	const wchar_t* cwp;

	oss<<input;
	ws = oss.str();
	cwp = ws.c_str(); // const wchar_t*
	std::vector<wchar_t> buf( cwp , cwp + (ws.size() + 1) );
	wchar_t* result = &buf[0];  // wchar_t*
	std::wstring ourString(result);
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), ourString.c_str(), wcslen(ourString.c_str()), NULL, NULL);
	if (printNewLineAfter)
		writeNewLineToConsole();
}
//Floats
static void writeNumToConsole (float input, bool printNewLineAfter = true)
{
	std::wostringstream oss;
	std::wstring ws;
	const wchar_t* cwp;

	oss<<input;
	ws = oss.str();
	cwp = ws.c_str(); // const wchar_t*
	std::vector<wchar_t> buf( cwp , cwp + (ws.size() + 1) );
	wchar_t* result = &buf[0];  // wchar_t*
	std::wstring ourString(result);
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), ourString.c_str(), wcslen(ourString.c_str()), NULL, NULL);
	if (printNewLineAfter)
		writeNewLineToConsole();
}
//Text (in wchar_t format)
static void writeTextToConsole(const wchar_t* theString, bool printNewLineAfter = true)
{
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), theString, wcslen(theString), NULL, NULL);
	if (printNewLineAfter)
		writeNewLineToConsole();
}

///////////////////////////////////////////////////////////////////////////////////////
//writes new line to Console. Very straight forward, but shouldn't be necessary to use.
///////////////////////////////////////////////////////////////////////////////////////
static void writeNewLineToConsole()
{
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), L"\n", wcslen(L"\n"), NULL, NULL);
}
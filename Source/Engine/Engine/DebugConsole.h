#pragma once

#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <sstream>
#include <vector>

static void writeNumToConsole (int input)
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
}

static void writeNumToConsole (float input)
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
}

static void writeTextToConsole(const wchar_t* theString)
{
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), theString, wcslen(theString), NULL, NULL);
}
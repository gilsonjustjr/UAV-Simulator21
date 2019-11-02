#ifndef __HELPERS_H__
#define __HELPERS_H__

#pragma once

#include <string.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <time.h>


#define CRLF "\r\n";

using namespace System;

String ^ _getTime()
{
	time_t tempo;
	struct tm * timeinfo;

	time(&tempo);
	timeinfo = localtime(&tempo);

	//char horario[10];
	//sprintf_s(horario, "%02d:%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	//return horario;

	return timeinfo->tm_hour + ":" + timeinfo->tm_min + ":" + timeinfo->tm_sec + " - ";
}

#endif
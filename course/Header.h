#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wincon.h>

#define CIN_FLUSH if (std::cin.fail()) {std::cin.clear(); std::cin.ignore();}

HANDLE hCon;
CONSOLE_SCREEN_BUFFER_INFO csbiScreenInfo;
COORD coordStart = { 0, 0 };  // Screen coordinate for upper left
DWORD dwNumWritten = 0;       // Holds # of cells written to 
							  // by FillConsoleOutputAttribute
DWORD dwScrSize;
WORD  wAttributes = BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
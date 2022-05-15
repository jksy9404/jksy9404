#pragma once
#include "Process.h"
extern HWND g_hWnd;

namespace Client
{
	enum LEVEL { LEVEL_STATIC, LEVEL_LOGO, LEVEL_GAMEPLAY, LEVEL_LOADING, LEVEL_END };
	const unsigned int g_iWinSizeX = 1280;
	const unsigned int g_iWinSizeY = 720;
}

using namespace Client;

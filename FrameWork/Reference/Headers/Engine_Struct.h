#pragma once

namespace Engine
{
	typedef struct tagGraphicDesc
	{
		HWND hWnd;
		unsigned int iWinCX;
		unsigned int iWinCY;
		bool isWindowed;
	}GRAPHICDESC;

}
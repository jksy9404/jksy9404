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
	// D3DDECLUSAGE 구조체 순서
	typedef struct tagVertex_Texture {
		D3DXVECTOR3 vPosition;
		D3DXVECTOR2	vTexUV;
	}VTXTEX;

}
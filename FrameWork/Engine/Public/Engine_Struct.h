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
	// D3DDECLUSAGE ����ü ����
	typedef struct tagVertex_Texture {
		D3DXVECTOR3 vPosition;
		D3DXVECTOR2	vTexUV;
	}VTXTEX;

}
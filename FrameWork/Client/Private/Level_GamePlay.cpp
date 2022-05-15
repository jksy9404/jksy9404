#include "stdafx.h"
#include "Level_GamePlay.h"



CLevel_GamePlay::CLevel_GamePlay(LPDIRECT3DDEVICE9 pGraphic)
	:CLevel(pGraphic)
{
}

HRESULT CLevel_GamePlay::NativeConstruct()
{
	if (FAILED(__super::NativeConstruct()))
		return E_FAIL;
	return S_OK;
}

void CLevel_GamePlay::Tick(_float fTmDelta)
{
	__super::Tick(fTmDelta);
}

void CLevel_GamePlay::LateTick(_float fTmDelta)
{
	__super::LateTick(fTmDelta);

	SetWindowText(g_hWnd, TEXT("게임플레이레벨임"));
}

HRESULT CLevel_GamePlay::Render()
{
	return S_OK;
}

CLevel_GamePlay * CLevel_GamePlay::Create(LPDIRECT3DDEVICE9 pGraphic)
{
	CLevel_GamePlay*		pInstance = new CLevel_GamePlay(pGraphic);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSX_BOX("Failed to Created : CLevel_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLevel_GamePlay::Free()
{
	__super::Free();
}

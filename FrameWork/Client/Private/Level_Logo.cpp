#include "stdafx.h"
#include "..\Public\Level_Logo.h"
#include "GameInstance.h"
#include "Level_Loading.h"

CLevel_Logo::CLevel_Logo(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CLevel(pGraphic_Device)
{
}

HRESULT CLevel_Logo::NativeConstruct()
{
	if (FAILED(__super::NativeConstruct()))
		return E_FAIL;

	if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
		return E_FAIL;

	return S_OK;
}

void CLevel_Logo::Tick(_float fTmDelta)
{
	__super::Tick(fTmDelta);
}

void CLevel_Logo::LateTick(_float fTmDelta)
{
	__super::LateTick(fTmDelta);

	if (GetKeyState(VK_RETURN) < 0)
	{
		CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
		Safe_AddRef(pGameInstance);


		if (FAILED(pGameInstance->Open_Level(CLevel_Loading::Create(m_pGraphic_Device, LEVEL_GAMEPLAY))))
			return;


		Safe_Release(pGameInstance);

	}

	SetWindowText(g_hWnd, TEXT("로고레벨임"));
}

HRESULT CLevel_Logo::Render()
{
	return S_OK;
}

HRESULT CLevel_Logo::Ready_Layer_BackGround(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);
	if (FAILED(pGameInstance->Clone_GameObject(LEVEL_LOGO, pLayerTag, TEXT("Prototype_GameObject_BackGround"))))
		return E_FAIL;

	Safe_Release(pGameInstance);

	return S_OK;
}

CLevel_Logo * CLevel_Logo::Create(LPDIRECT3DDEVICE9 pGraphic)
{
	CLevel_Logo* pInstance = new CLevel_Logo(pGraphic);
	if (FAILED(pInstance->NativeConstruct())) {
		MSX_BOX("Failed to Create : CLevel_Logo");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLevel_Logo::Free()
{
	__super::Free();
}

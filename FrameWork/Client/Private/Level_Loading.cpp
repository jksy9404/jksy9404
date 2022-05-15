#include "stdafx.h"
#include "..\Public\Level_Loading.h"
#include "GameInstance.h"
#include "Level_GamePlay.h"
#include "Level_Logo.h"
#include "Loader.h"
CLevel_Loading::CLevel_Loading(LPDIRECT3DDEVICE9 pGraphic)
	:CLevel(pGraphic)
{
}

HRESULT CLevel_Loading::NativeConstruct(LEVEL eLevel)
{
	if (FAILED(__super::NativeConstruct()))
		return E_FAIL;
	
	m_eNextLevel = eLevel;

	m_pLoader = CLoader::Create(m_pGraphic_Device, m_eNextLevel);
	if (nullptr == m_pLoader)
		return E_FAIL;

	return S_OK;
}

void CLevel_Loading::Tick(_float fTmDelta)
{
	__super::Tick(fTmDelta);


}

void CLevel_Loading::LateTick(_float fTmDelta)
{
	__super::LateTick(fTmDelta);

	if (false == m_pLoader->Get_Finished())
		OutputDebugString(m_pLoader->Get_LoadingText());

	/* 로더에게 로딩(다음레벨을 위한 자원로딩) 이 끝났다면이라는 정보를받아와서 진행  */
	if (m_pLoader->Get_Finished()) {
		if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
			CGameInstance* pGameInstance = CGameInstance::Get_Instance();
			Safe_AddRef(pGameInstance);

			CLevel* pLevel = nullptr;
			switch (m_eNextLevel)
			{
			case Client::LEVEL_LOGO:
				pLevel = CLevel_Logo::Create(m_pGraphic_Device);
				break;
			case Client::LEVEL_GAMEPLAY:
				pLevel = CLevel_GamePlay::Create(m_pGraphic_Device);
				break;
			}

			if (nullptr == pLevel)
				return;

			if (FAILED(pGameInstance->Open_Level(pLevel)))
				return;

			Safe_Release(pGameInstance);
		}
	}
}

HRESULT CLevel_Loading::Render()
{
	return S_OK;
}

CLevel_Loading * CLevel_Loading::Create(LPDIRECT3DDEVICE9 pGraphic, LEVEL eNextLevel)
{
	CLevel_Loading* pInstance = new CLevel_Loading(pGraphic);
	if (FAILED(pInstance->NativeConstruct(eNextLevel))) {
		MSX_BOX("Failed to Created : CLevel_Loading");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_Loading::Free()
{
	__super::Free();
	Safe_Release(m_pLoader);

}

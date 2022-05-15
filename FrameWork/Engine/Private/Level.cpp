#include "..\Public\Level.h"

CLevel::CLevel(LPDIRECT3DDEVICE9 pGraphic_Device)
	:m_pGraphic_Device(pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
}


HRESULT CLevel::NativeConstruct()
{
	return S_OK;
}

void CLevel::Tick(float fTmDelta)
{
}

void CLevel::LateTick(float fTmDelta)
{
}

HRESULT CLevel::Render()
{
	return S_OK;
}

void CLevel::Free()
{
	Safe_Release(m_pGraphic_Device);
}



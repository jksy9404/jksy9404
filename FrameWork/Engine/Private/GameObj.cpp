#include "..\Public\GameObj.h"


CGameObj::CGameObj(LPDIRECT3DDEVICE9 pGraphicDevice)
	:m_pGraphic_Device(pGraphicDevice)
{
	Safe_AddRef(m_pGraphic_Device);
}

CGameObj::CGameObj(const CGameObj & Prototype)
	:m_pGraphic_Device(Prototype.m_pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
}

HRESULT CGameObj::NativeConstruct_Prototype()
{
	return S_OK;
}

HRESULT CGameObj::NativeConstruct(void* pArg)
{

	return S_OK;
}

void CGameObj::Tick(_float fTimeDelta)
{
}

void CGameObj::LateTick(_float fTimeDelta)
{
}

HRESULT CGameObj::Render()
{
	return S_OK;
}

void CGameObj::Free()
{
	Safe_Release(m_pGraphic_Device);
}

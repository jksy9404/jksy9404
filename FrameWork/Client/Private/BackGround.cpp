#include "stdafx.h"
#include "..\Public\BackGround.h"


CBackGround::CBackGround(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObj(pGraphic_Device)
{
}

CBackGround::CBackGround(const CBackGround & Prototype)
	:CGameObj(Prototype)
{
}

HRESULT CBackGround::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;


	return S_OK;
}

HRESULT CBackGround::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;
	return S_OK;
}

void CBackGround::Tick(_float fTmDelta)
{
	__super::Tick(fTmDelta);
}

void CBackGround::LateTick(_float fTmDelta)
{
	__super::LateTick(fTmDelta);
}

HRESULT CBackGround::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

CBackGround * CBackGround::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CBackGround* pInstacne = new CBackGround(pGraphic_Device);
	if (FAILED(pInstacne->NativeConstruct_Prototype())) {
		MSX_BOX("Failed to Create : CBackGround");
		Safe_Release(pInstacne);
	}
	return pInstacne;
}

CGameObj * CBackGround::Clone(void * pArg)
{
	CBackGround* pInstance = new CBackGround(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSX_BOX("Failed to Created : CBackGround");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBackGround::Free()
{
	__super::Free();
}

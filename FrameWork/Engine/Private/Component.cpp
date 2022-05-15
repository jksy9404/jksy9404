#include "..\Public\Component.h"

CComponent::CComponent(LPDIRECT3DDEVICE9 pGraphicDevice)
	:m_pGraphic_Device(pGraphicDevice)
{
	Safe_Release(m_pGraphic_Device);
}

CComponent::CComponent(const CComponent & Prototype)
{
}

HRESULT CComponent::NativeConstruct_Prototype()
{
	return S_OK;
}

HRESULT CComponent::NativeConstruct(void * pArg)
{
	return S_OK;
}

void CComponent::Free()
{
	Safe_Release(m_pGraphic_Device);
}

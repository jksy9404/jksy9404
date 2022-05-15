#include "..\Public\VIBuffer_Rect.h"


CVIBuffer_Rect::CVIBuffer_Rect(LPDIRECT3DDEVICE9 pGraphicDevice)
	:CVIBuffer(pGraphicDevice)
{
}

CVIBuffer_Rect::CVIBuffer_Rect(const CVIBuffer_Rect & Prototype)
	:CVIBuffer(Prototype)
{
}

HRESULT CVIBuffer_Rect::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	m_iNumVertices = 6;
	m_iStride = sizeof(VTXTEX);
	m_dwFVF = D3DFVF_XYZ | D3DFVF_TEX1;

	if (FAILED(__super::Create_VertexBuffer())) // ���� ������ ���� ������ ���ؽ� ���� ȣ��
		return E_FAIL;

	//�Ҵ�� ������ ����� �װ��� ���� ä��, ������ �����ϱ� ���� �����ּҸ� ��� ���� �ڵ�
	VTXTEX*	pVertices = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertices, 0);
	// void**�� ����ȯ�� �ȵǰ� ���� void*�� �ּҰ����� ���� �� �����Ƿ� ��ó�� ����
	pVertices[0].vPosition = _float3();
	pVertices[0].vTexUV = _float2();

	pVertices[0].vPosition = _float3();
	pVertices[0].vTexUV = _float2();

	pVertices[0].vPosition = _float3();
	pVertices[0].vTexUV = _float2();

	pVertices[0].vPosition = _float3();
	pVertices[0].vTexUV = _float2();

	pVertices[0].vPosition = _float3();
	pVertices[0].vTexUV = _float2();

	pVertices[0].vPosition = _float3();
	pVertices[0].vTexUV = _float2();

	m_pVB->Unlock();

	return S_OK;
}

HRESULT CVIBuffer_Rect::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	return S_OK;
}

CVIBuffer_Rect * CVIBuffer_Rect::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CVIBuffer_Rect*		pInstance = new CVIBuffer_Rect(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSX_BOX("Failed to Created : CVIBuffer_Rect");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent * CVIBuffer_Rect::Clone(void * pArg)
{
	CVIBuffer_Rect*		pInstance = new CVIBuffer_Rect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSX_BOX("Failed to Make Clone : CVIBuffer_Rect");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CVIBuffer_Rect::Free()
{
	__super::Free();
}

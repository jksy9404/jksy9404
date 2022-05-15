#pragma once
#include "Component.h"
BEGIN(Engine)
class ENGINE_DLL CVIBuffer abstract : public CComponent
{
protected:
	CVIBuffer(LPDIRECT3DDEVICE9 pGraphicDevice);
	CVIBuffer(const CVIBuffer& Prototype);
	virtual ~CVIBuffer() = default;

public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);

protected:
	LPDIRECT3DVERTEXBUFFER9	m_pVB = nullptr;
	_uint	m_iNumVertices = 0; // ������ ����
	_uint	m_iStride = 0; // �� ������ �޸� ũ��
	_ulong	m_dwFVF = 0;


protected:
	HRESULT Create_VertexBuffer();

public:
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free();
};

END
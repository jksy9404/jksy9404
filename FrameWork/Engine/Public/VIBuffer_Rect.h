#pragma once
#include "VIBuffer.h"
BEGIN(Engine)
class ENGINE_DLL CVIBuffer_Rect final : public CVIBuffer
{
protected:
	explicit CVIBuffer_Rect(LPDIRECT3DDEVICE9 pGraphicDevice);
	explicit CVIBuffer_Rect(const CVIBuffer_Rect& Prototype);
	virtual	~CVIBuffer_Rect() = default;

public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);

public:
	static CVIBuffer_Rect* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg);
	virtual void Free();
};


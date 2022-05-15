#pragma once
#include "Base.h"
BEGIN(Engine)
class ENGINE_DLL CComponent abstract : public CBase
{
protected:
	explicit CComponent(LPDIRECT3DDEVICE9 pGraphicDevice);
	explicit CComponent(const CComponent& Prototype);
	virtual ~CComponent() = default;

public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);

protected:
	LPDIRECT3DDEVICE9 m_pGraphic_Device = nullptr;

public:
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free();
};

END
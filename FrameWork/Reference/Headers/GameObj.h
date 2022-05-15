#pragma once
#include "Base.h"
BEGIN(Engine)
class ENGINE_DLL CGameObj abstract : public CBase
{
protected:
	explicit CGameObj(LPDIRECT3DDEVICE9 pGraphicDevice);
	explicit CGameObj(const CGameObj& Prototype);
	virtual ~CGameObj() = default;

public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT  Render();

protected:
	LPDIRECT3DDEVICE9		m_pGraphic_Device = nullptr;

public:
	virtual CGameObj* Clone(void* pArg) = 0;
	virtual void Free() override;
};
END

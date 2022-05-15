#pragma once
#include "Base.h"

BEGIN(Engine)
class ENGINE_DLL CLevel abstract :	public CBase
{
protected:
	CLevel(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLevel() = default;

public:
	virtual HRESULT NativeConstruct();
	virtual void Tick(float fTmDelta);
	virtual void LateTick(float fTmDelta);
	virtual HRESULT Render();

protected:
	LPDIRECT3DDEVICE9 m_pGraphic_Device = nullptr;


public:
	virtual void Free() override;
};
END


#pragma once

#include "Client_Define.h"
#include "Level.h"

BEGIN(Client)
class CLevel_Logo final : public CLevel
{
public:
	CLevel_Logo(LPDIRECT3DDEVICE9 pGraphic);
	virtual ~CLevel_Logo() = default;

public:
	virtual HRESULT NativeConstruct();
	virtual void Tick(_float fTmDelta);
	virtual void LateTick(_float fTmDelta);
	virtual HRESULT Render();

private:
	HRESULT Ready_Layer_BackGround(const _tchar* pLayerTag);
	
public:
	static CLevel_Logo* Create(LPDIRECT3DDEVICE9 pGraphic);
	virtual void Free() override;
};
END

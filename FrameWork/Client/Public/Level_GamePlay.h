#pragma once

#include "Client_Define.h"
#include "Level.h"

BEGIN(Client)
class CLevel_GamePlay final : public CLevel
{
public:
	CLevel_GamePlay(LPDIRECT3DDEVICE9 pGraphic);
	virtual ~CLevel_GamePlay() = default;

public:
	virtual HRESULT NativeConstruct();
	virtual void Tick(_float fTmDelta);
	virtual void LateTick(_float fTmDelta);
	virtual HRESULT Render();

public:
	static CLevel_GamePlay* Create(LPDIRECT3DDEVICE9 pGraphic);
	virtual void Free() override;
};
END
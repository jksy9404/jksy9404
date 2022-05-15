#pragma once

#include "Client_Define.h"
#include "Level.h"

BEGIN(Client)
class CLevel_Loading final : public CLevel
{
public:
	CLevel_Loading(LPDIRECT3DDEVICE9 pGraphic);
	virtual ~CLevel_Loading() = default;

public:
	virtual HRESULT NativeConstruct(LEVEL eLevel);
	virtual void Tick(_float fTmDelta);
	virtual void LateTick(_float fTmDelta);
	virtual HRESULT Render();

private:
	LEVEL m_eNextLevel = LEVEL_END;
	class CLoader*	m_pLoader = nullptr;

public:
	static CLevel_Loading* Create(LPDIRECT3DDEVICE9 pGraphic, LEVEL eNextLevel);
	virtual void Free() override;
};
END
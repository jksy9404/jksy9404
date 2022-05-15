#pragma once
#include "Base.h"
BEGIN(Engine)

class CLayer final : public CBase
{
public:
	CLayer();
	virtual ~CLayer() = default;

public:
	HRESULT Add_GameObject(class CGameObj* pGameObject);

public:
	HRESULT NativeConstruct();
	void Tick(_float fTimeDelta);
	void LateTick(_float fTimeDelta);


private:
	list<class CGameObj*>			m_ObjectList;
	typedef list<class CGameObj*>	OBJECTS;

public:
	static CLayer* Create();
	virtual void Free() override;
};

END
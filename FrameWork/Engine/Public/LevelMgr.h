#pragma once
#include "Base.h"

BEGIN(Engine)
class CLevelMgr final: public CBase
{
	DECLARE_SINGLETON(CLevelMgr)
public:
	CLevelMgr();
	virtual ~CLevelMgr() = default;

public:
	HRESULT Change_Level(class CLevel* pNextLevel);
	HRESULT Tick(float fTmDelta);
	HRESULT LateTick(float fTmDelta);

private:
	class CLevel* m_pCurrentLevel = nullptr;
public:
	virtual void Free() override;

};
END

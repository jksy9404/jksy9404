#pragma once
#include "Base.h"

BEGIN(Engine)
class CTimeMgr final : public CBase
{
	DECLARE_SINGLETON(CTimeMgr)

private:
	CTimeMgr();
	virtual ~CTimeMgr() = default;

public:
	_float Get_TimeDelta(const _tchar* pTimerTag);

public:
	HRESULT Add_Timer(const _tchar* pTimerTag);
	void Update(const _tchar* pTimerTag);

private:
	map<const _tchar*, class CTimer*> m_Timers;
	typedef map<const _tchar*, class CTimer*> TIMERS;

private:
	class CTimer* Find_Timer(const _tchar* pTimerTag);
public:
	virtual void Free() override;
};

END
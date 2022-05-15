#include "..\Public\TimeMgr.h"
#include "Timer.h"

IMPLEMENT_SINGLETON(CTimeMgr)

CTimeMgr::CTimeMgr()
{
}


_float CTimeMgr::Get_TimeDelta(const _tchar * pTimerTag)
{
	CTimer* pTimer = Find_Timer(pTimerTag);

	if (pTimer == nullptr)
		return 0.0f;
	return pTimer->Get_TimeDelta();
}

HRESULT CTimeMgr::Add_Timer(const _tchar * pTimerTag)
{
	if (nullptr != Find_Timer(pTimerTag))
		return E_FAIL;

	m_Timers.emplace(pTimerTag, CTimer::Create());

	return S_OK;
}

void CTimeMgr::Update(const _tchar * pTimerTag)
{
	CTimer* pTimer = Find_Timer(pTimerTag);
	if (pTimer == nullptr)
		return;

	return pTimer->Update();
}

CTimer * CTimeMgr::Find_Timer(const _tchar * pTimerTag)
{
	auto	iter = find_if(m_Timers.begin(), m_Timers.end(), CTag_Finder(pTimerTag));
	if (iter == m_Timers.end()) {
		MSX_BOX("No TimerTag");
		return nullptr;
	}

	return iter->second;
}

void CTimeMgr::Free()
{
	for (auto& Pair : m_Timers)
		Safe_Release(Pair.second);

	m_Timers.clear();
}

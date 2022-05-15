#include "LevelMgr.h"
#include "Level.h"
IMPLEMENT_SINGLETON(CLevelMgr)

CLevelMgr::CLevelMgr()
{
}

HRESULT CLevelMgr::Change_Level(CLevel * pNextLevel)
{
	if (nullptr == pNextLevel)
		return E_FAIL;

	Safe_Release(m_pCurrentLevel);

	m_pCurrentLevel = pNextLevel;

	return S_OK;
}

HRESULT CLevelMgr::Tick(float fTmDelta)
{
	if (nullptr == m_pCurrentLevel)
		return E_FAIL;

	m_pCurrentLevel->Tick(fTmDelta);
	return S_OK;
}

HRESULT CLevelMgr::LateTick(float fTmDelta)
{
	if (nullptr == m_pCurrentLevel)
		return E_FAIL;

	m_pCurrentLevel->LateTick(fTmDelta);
	return S_OK;
}

void CLevelMgr::Free()
{
	Safe_Release(m_pCurrentLevel);
}

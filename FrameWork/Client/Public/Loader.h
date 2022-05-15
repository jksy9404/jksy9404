#pragma once
#include "Base.h"
#include "Client_Define.h"

BEGIN(Client)
class CLoader final : public CBase
{
private:
	CLoader(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLoader() = default;

public:
	LEVEL Get_NextLevel()					{ return m_eNextLevel; }
	CRITICAL_SECTION* Get_CriticalSection() { return &m_Critical_Section; }
	_bool Get_Finished()					{ return m_isFinished; }
	const _tchar* Get_LoadingText()			{ return m_szLoading;}
public:
	HRESULT NativeConstruct(LEVEL eNextLevel);

public:
	HRESULT Loading_ForLogoLevel();
	HRESULT Loading_ForGamePlayLevel();

private:
	LEVEL m_eNextLevel = LEVEL_END;
	LPDIRECT3DDEVICE9 m_pGraphic_Device = nullptr;

	// ½º·¹µå
private:
	HANDLE				m_hThread = 0;
	CRITICAL_SECTION	m_Critical_Section;
	_tchar				m_szLoading[MAX_PATH] = TEXT("");
	_bool				m_isFinished = false;
public:
	static CLoader* Create(LPDIRECT3DDEVICE9 pGraphicDevice, LEVEL eNextLevel);
	virtual void Free() override;
};
END

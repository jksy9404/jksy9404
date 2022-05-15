#pragma once
#include "Base.h"
#include "Client_Define.h"
BEGIN(Engine)
class CGameInstance;
END
class CMainApp final : public CBase
{
private:
	CMainApp();
	virtual ~CMainApp() = default;

public:
	HRESULT NativeConstruct();
	void Tick(float fTmDelta);
	HRESULT Render();

private:
	CGameInstance*				m_pGameInstance = nullptr;
	LPDIRECT3DDEVICE9			m_pGraphic_Device = nullptr;

private:
	HRESULT Open_Level(LEVEL eLevel);

#ifdef _DEBUG
private:
	_tchar					m_szFPS[MAX_PATH];
	_uint					m_iNumRender = 0;
	_float					m_fTimeAcc = 0.f;
#endif // _DEBUG

public:
	static CMainApp* Create();
	virtual void Free() override;
};



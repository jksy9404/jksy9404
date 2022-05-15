#pragma once
#include "Graphic_Device.h"
#include "LevelMgr.h"
#include  "TimeMgr.h"
#include "ObjMgr.h"

BEGIN(Engine)
class ENGINE_DLL CGameInstance final : public CBase
{
	DECLARE_SINGLETON(CGameInstance)
private:
	CGameInstance();
	virtual	~CGameInstance() = default;

public: /* For.GameInstance */
	HRESULT Initialize_Engine(_uint iNumLevels, const GRAPHICDESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut); /* 엔진의 기능을 사용하기위해 초기화가 필요한 녀석들을 초기화한다. */
	void Tick_Engine(_float fTimeDelta); /* 매프레임마다 갱신이 필요한 매니져들의 동작. */

public: /* For.Graphic_Device */
	void Render_Begin();
	void Render_End();

public: /* For.Level_Manager*/
	HRESULT Open_Level(class CLevel* pNextLevel);

public: /* For.Timer_Manager */
	_float Get_TimeDelta(const _tchar* pTimerTag);
	HRESULT Add_Timer(const _tchar* pTimerTag);
	void Update_Timer(const _tchar* pTimerTag);

public: /*For.Object_Manager */
	HRESULT Add_Prototype(const _tchar* pPrototypeTag, class CGameObj* pGameObject);
	HRESULT Clone_GameObject(_uint iLevelIndex, const _tchar* pLayerTag, const _tchar* pPrototypeTag, void* pArg = nullptr);


private:
	CGraphic_Device*				m_pGraphic_Device = nullptr;
	CLevelMgr*						m_pLevelMgr = nullptr;
	CObjMgr*						m_pObjMgr = nullptr;
	CTimeMgr*						m_pTimeMgr = nullptr;

public:
	static void Release_Engine(); /* 엔진에서 사용된 각종 매니져의 메모리 정리. */

public:
	virtual void Free() override;

};
END

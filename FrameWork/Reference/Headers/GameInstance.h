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
	HRESULT Initialize_Engine(_uint iNumLevels, const GRAPHICDESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut); /* ������ ����� ����ϱ����� �ʱ�ȭ�� �ʿ��� �༮���� �ʱ�ȭ�Ѵ�. */
	void Tick_Engine(_float fTimeDelta); /* �������Ӹ��� ������ �ʿ��� �Ŵ������� ����. */

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
	static void Release_Engine(); /* �������� ���� ���� �Ŵ����� �޸� ����. */

public:
	virtual void Free() override;

};
END

#include "..\Public\GameInstance.h"

IMPLEMENT_SINGLETON(CGameInstance)

CGameInstance::CGameInstance()
	: m_pGraphic_Device(CGraphic_Device::Get_Instance())
	, m_pLevelMgr(CLevelMgr::Get_Instance())
	, m_pObjMgr(CObjMgr::Get_Instance())
	, m_pTimeMgr(CTimeMgr::Get_Instance())
{
	Safe_AddRef(m_pGraphic_Device);
	Safe_AddRef(m_pLevelMgr);
	Safe_AddRef(m_pObjMgr);
	Safe_AddRef(m_pTimeMgr);
}

HRESULT CGameInstance::Initialize_Engine(_uint iNumLevels, const GRAPHICDESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut)
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	// 그래픽 디바이스 초기화
	if (FAILED(m_pGraphic_Device->InitDevice(GraphicDesc, ppOut)))
		return E_FAIL;

	// 입력 디바이스 초기화
	
	// 사운드 디바이스 초기화
	
	// 오브젝트 매니저 준비
	if (FAILED(m_pObjMgr->Reserve_Container(iNumLevels)))
		return E_FAIL;
	// 컴포넌트 매니저 준비
	
	return S_OK;
}

void CGameInstance::Tick_Engine(_float fTimeDelta)
{
	/* 입력장치의 상태 조사. */
	/* 오브젝트들의 업데이트를 수행한다. */
	if (nullptr == m_pLevelMgr || nullptr == m_pObjMgr)
		return;

	/* 입력장치의 상태 조사. */
	/* 오브젝트들의 업데이트를 수행한다. */

	m_pObjMgr->Tick(fTimeDelta); // objmgr -> obj -> layer
	m_pLevelMgr->Tick(fTimeDelta);

	m_pObjMgr->LateTick(fTimeDelta);
	m_pLevelMgr->LateTick(fTimeDelta);

}

void CGameInstance::Render_Begin()
{
	if (nullptr == m_pGraphic_Device)
		return;

	m_pGraphic_Device->Render_Begin();
}

void CGameInstance::Render_End()
{
	if (nullptr == m_pGraphic_Device)
		return;

	m_pGraphic_Device->Render_End();
}

HRESULT CGameInstance::Open_Level(CLevel * pNextLevel)
{
	if (nullptr == m_pLevelMgr)
		return E_FAIL;

	return m_pLevelMgr->Change_Level(pNextLevel);
}

_float CGameInstance::Get_TimeDelta(const _tchar * pTimerTag)
{
	if (nullptr == m_pTimeMgr)
		return 0.0f;

	return m_pTimeMgr->Get_TimeDelta(pTimerTag);
}

HRESULT CGameInstance::Add_Timer(const _tchar * pTimerTag)
{
	if (nullptr == m_pTimeMgr)
		return E_FAIL;

	return m_pTimeMgr->Add_Timer(pTimerTag);
}

void CGameInstance::Update_Timer(const _tchar * pTimerTag)
{
	if (nullptr == m_pTimeMgr)
		return;

	m_pTimeMgr->Update(pTimerTag);
}

HRESULT CGameInstance::Add_Prototype(const _tchar * pPrototypeTag, CGameObj * pGameObject)
{
	if (nullptr == m_pObjMgr)
		return E_FAIL;

	return m_pObjMgr->Add_Prototype(pPrototypeTag, pGameObject);
}

HRESULT CGameInstance::Clone_GameObject(_uint iLevelIndex, const _tchar * pLayerTag, const _tchar * pPrototypeTag, void * pArg)
{
	if (nullptr == m_pObjMgr)
		return E_FAIL;

	return m_pObjMgr->Clone_GameObj(iLevelIndex, pLayerTag, pPrototypeTag, pArg);
}

void CGameInstance::Release_Engine()
{
	CGameInstance::Get_Instance()->Destroy_Instance();

	CObjMgr::Get_Instance()->Destroy_Instance();

	CLevelMgr::Get_Instance()->Destroy_Instance();

	CTimeMgr::Get_Instance()->Destroy_Instance();

	CGraphic_Device::Get_Instance()->Destroy_Instance();

}

void CGameInstance::Free()
{
	Safe_Release(m_pObjMgr);
	Safe_Release(m_pTimeMgr);
	Safe_Release(m_pGraphic_Device);
	Safe_Release(m_pLevelMgr);

}

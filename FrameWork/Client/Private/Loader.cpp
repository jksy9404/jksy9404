#include "stdafx.h"
#include "..\Public\Loader.h"
#include "GameInstance.h"
#include"BackGround.h"
CLoader::CLoader(LPDIRECT3DDEVICE9 pGraphic_Device)
	:m_pGraphic_Device(pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
}

unsigned APIENTRY ThreadEntyFunc(void* pArg) {
	
	CLoader* pLoader = (CLoader*)pArg;
	EnterCriticalSection(pLoader->Get_CriticalSection());

	// 스레드를 시작했고 다음 해당 스레드에서 해야할 코드 ( 로딩스레드이므로 다음 레벨(신)에 필요한 자원들을 로드
	switch (pLoader->Get_NextLevel())
	{
	case LEVEL_LOGO:
		pLoader->Loading_ForLogoLevel();
		break;
	case LEVEL_GAMEPLAY:
		pLoader->Loading_ForGamePlayLevel();
		break;
	}
	LeaveCriticalSection(pLoader->Get_CriticalSection());
	return 0;
}


HRESULT CLoader::NativeConstruct(LEVEL eNextLevel)
{
	m_eNextLevel = eNextLevel;
	InitializeCriticalSection(&m_Critical_Section);

	m_hThread = (HANDLE)_beginthreadex(nullptr, // 보안속성(핸들 상속여부)
										0,		// 스택사이즈, 스레드는 고유의 스택을 가지고있고 보통 null, default mb1크기
										ThreadEntyFunc, // 스레드가 작동할 함수
										this, // 함수의 인자
										0, //suspend count 1로 설정
										nullptr); // 생성시 이 변수로 스레드 전달, 필요없으면 null
	
	if (m_hThread == 0)
		return E_FAIL;

	return S_OK;
}

HRESULT CLoader::Loading_ForLogoLevel()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	if (nullptr == pGameInstance)
		return E_FAIL;

	Safe_AddRef(pGameInstance);


	wsprintf(m_szLoading, TEXT("로고용 텍스쳐를 로딩 중입니다."));
	

	wsprintf(m_szLoading, TEXT("로고용 모델를 로딩 중입니다."));
	

	wsprintf(m_szLoading, TEXT("로고용 객체들을 생성 중입니다."));
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_BackGround"), CBackGround::Create(m_pGraphic_Device))))
		return E_FAIL;

	wsprintf(m_szLoading, TEXT("로딩이 완료되었습니다. "));
	
	Safe_Release(pGameInstance);

	m_isFinished = true;

	return S_OK;
}

HRESULT CLoader::Loading_ForGamePlayLevel()
{
	wsprintf(m_szLoading, TEXT("게임플레이용 텍스쳐를 로딩 중입니다."));
	for (_uint i = 0; i < 999999999; ++i)
	{
		int a = 10;
	}

	wsprintf(m_szLoading, TEXT("게임플레이용 모델를 로딩 중입니다."));
	for (_uint i = 0; i < 999999999; ++i)
	{
		int a = 10;
	}

	wsprintf(m_szLoading, TEXT("게임플레이용 객체들을 생성 중입니다."));
	for (_uint i = 0; i < 999999999; ++i)
	{
		int a = 10;
	}

	wsprintf(m_szLoading, TEXT("게임플레이용 완료되었습니다. "));
	for (_uint i = 0; i < 999999999; ++i)
	{
		int a = 10;
	}

	m_isFinished = true;

	return S_OK;
}

CLoader * CLoader::Create(LPDIRECT3DDEVICE9 pGraphicDevice, LEVEL eNextLevel)
{
	CLoader* pInstance = new CLoader(pGraphicDevice);
	if (FAILED(pInstance->NativeConstruct(eNextLevel))) {
		MSX_BOX("Failed to Created : CLoader");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLoader::Free()
{
	Safe_Release(m_pGraphic_Device);
	WaitForSingleObject(m_hThread, INFINITE);
	DeleteCriticalSection(&m_Critical_Section);
	CloseHandle(m_hThread);
}

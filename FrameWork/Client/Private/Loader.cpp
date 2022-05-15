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

	// �����带 �����߰� ���� �ش� �����忡�� �ؾ��� �ڵ� ( �ε��������̹Ƿ� ���� ����(��)�� �ʿ��� �ڿ����� �ε�
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

	m_hThread = (HANDLE)_beginthreadex(nullptr, // ���ȼӼ�(�ڵ� ��ӿ���)
										0,		// ���û�����, ������� ������ ������ �������ְ� ���� null, default mb1ũ��
										ThreadEntyFunc, // �����尡 �۵��� �Լ�
										this, // �Լ��� ����
										0, //suspend count 1�� ����
										nullptr); // ������ �� ������ ������ ����, �ʿ������ null
	
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


	wsprintf(m_szLoading, TEXT("�ΰ�� �ؽ��ĸ� �ε� ���Դϴ�."));
	

	wsprintf(m_szLoading, TEXT("�ΰ�� �𵨸� �ε� ���Դϴ�."));
	

	wsprintf(m_szLoading, TEXT("�ΰ�� ��ü���� ���� ���Դϴ�."));
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_BackGround"), CBackGround::Create(m_pGraphic_Device))))
		return E_FAIL;

	wsprintf(m_szLoading, TEXT("�ε��� �Ϸ�Ǿ����ϴ�. "));
	
	Safe_Release(pGameInstance);

	m_isFinished = true;

	return S_OK;
}

HRESULT CLoader::Loading_ForGamePlayLevel()
{
	wsprintf(m_szLoading, TEXT("�����÷��̿� �ؽ��ĸ� �ε� ���Դϴ�."));
	for (_uint i = 0; i < 999999999; ++i)
	{
		int a = 10;
	}

	wsprintf(m_szLoading, TEXT("�����÷��̿� �𵨸� �ε� ���Դϴ�."));
	for (_uint i = 0; i < 999999999; ++i)
	{
		int a = 10;
	}

	wsprintf(m_szLoading, TEXT("�����÷��̿� ��ü���� ���� ���Դϴ�."));
	for (_uint i = 0; i < 999999999; ++i)
	{
		int a = 10;
	}

	wsprintf(m_szLoading, TEXT("�����÷��̿� �Ϸ�Ǿ����ϴ�. "));
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

#include "..\Public\Layer.h"
#include "GameObj.h"


CLayer::CLayer()
{
}

HRESULT CLayer::Add_GameObject(CGameObj * pGameObject) // ���̾ ȣ��Ǹ鼭 ������� ������Ʈ�� �־���
{
	m_ObjectList.push_back(pGameObject);
	return S_OK;
}

HRESULT CLayer::NativeConstruct()
{

	return S_OK;
}

void CLayer::Tick(_float fTimeDelta) // ����Ʈ�ȿ� �����ϴ� ������Ʈ�� ƽ ����
{
	for (auto& pGameObject : m_ObjectList) {
		if (nullptr != pGameObject)
			pGameObject->Tick(fTimeDelta);
	}
}

void CLayer::LateTick(_float fTimeDelta)
{
	for (auto& pGameObject : m_ObjectList) {
		if (nullptr != pGameObject)
			pGameObject->LateTick(fTimeDelta);
	}
}

CLayer * CLayer::Create()
{
	CLayer* pInstance = new CLayer();
	if (FAILED(pInstance->NativeConstruct())) {
		MSX_BOX("Failed to Created : CLayer");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLayer::Free()
{
	for (auto& pGameObj : m_ObjectList)
		Safe_Release(pGameObj);

	m_ObjectList.clear();
}



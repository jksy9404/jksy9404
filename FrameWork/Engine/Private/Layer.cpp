#include "..\Public\Layer.h"
#include "GameObj.h"


CLayer::CLayer()
{
}

HRESULT CLayer::Add_GameObject(CGameObj * pGameObject) // 레이어가 호출되면서 만들어진 오브젝트를 넣어줌
{
	m_ObjectList.push_back(pGameObject);
	return S_OK;
}

HRESULT CLayer::NativeConstruct()
{

	return S_OK;
}

void CLayer::Tick(_float fTimeDelta) // 리스트안에 존재하는 오브젝트들 틱 진행
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



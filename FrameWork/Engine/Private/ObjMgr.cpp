#include "..\Public\ObjMgr.h"
#include "Layer.h"
#include "GameObj.h"
IMPLEMENT_SINGLETON(CObjMgr)

CObjMgr::CObjMgr()
{
}

HRESULT CObjMgr::Reserve_Container(_uint iNumLevels)
{
	if (nullptr != m_pLayer) // 이미 레이어(오브젝트 리스트)가 존재한다면 중복이 되므로 예외처리
		return E_FAIL;

	m_pLayer = new LAYERS[iNumLevels]; // 레벨에 따른 동적할당으로 각 레벨(신) 마다 오브젝트를 저장관리

	m_iNumLevels = iNumLevels;

	
	return S_OK;
}

HRESULT CObjMgr::Add_Prototype(const _tchar * pPrototypeTag, CGameObj * pGameObj)
{
	if (nullptr != Find_Prototype(pPrototypeTag)) // 원본 만들기, 프로토타입 맵의 second값, 이미 만들어진 값이라면 리턴
		return E_FAIL;

	m_ProtoType.emplace(pPrototypeTag, pGameObj); // 원본 추가

	return S_OK;
}

HRESULT CObjMgr::Clone_GameObj(_uint iLevelIdx, const _tchar * pLayerTag, const _tchar * pPrototypeTag, void* pArg) // 원본을 바탕으로 클론 얕은복사
{
	if (iLevelIdx > m_iNumLevels || nullptr == m_pLayer)
		return E_FAIL;

	// 기존 원본가져오기
	CGameObj* pPrototype = Find_Prototype(pPrototypeTag);
	if (pPrototype == nullptr) // 원본이 없다면 사본은 만들수 없으므로 예외처리
		return E_FAIL;

	// 원본의 사본생성
	CGameObj* pGameObj = pPrototype->Clone(pArg); // 클라의 백그라운드로 상속된 클론에서 만들어짐(얕은복사), 부모클래스 게임오브젝트에서 레퍼런스카운트 올려줌
	if (pGameObj == nullptr)// 사본이 안만들어졌다면 예외처리
		return E_FAIL;

	CLayer* pLayer = Find_Layer(iLevelIdx, pLayerTag); // 만들어진 클론을 레어이에 보관하기 위해 신인덱스와 태그로 먼저 레이어가 존재하는지 찾고 있으면 추가, 없으면 만들고 추가
	if (pLayer == nullptr) {
		pLayer = CLayer::Create();
		if (nullptr == pLayer)
			return E_FAIL;

		if (FAILED(pLayer->Add_GameObject(pGameObj)))
			return E_FAIL;

		m_pLayer[iLevelIdx].emplace(pLayerTag, pLayer);
	}
	else
		pLayer->Add_GameObject(pGameObj);
	
	return S_OK;
}

void CObjMgr::Tick(_float fTimeDelta) // 리스트마다 틱진행
{
	for (_uint i = 0; i < m_iNumLevels; i++){
		for (auto& Pair : m_pLayer[i]) {
			if (Pair.second != nullptr)
				Pair.second->Tick(fTimeDelta);
		}
	}
}

void CObjMgr::LateTick(_float fTimeDelta)
{
	for (_uint i = 0; i < m_iNumLevels; i++) {
		for (auto& Pair : m_pLayer[i]) {
			if (Pair.second != nullptr)
				Pair.second->LateTick(fTimeDelta);
		}
	}
}

CGameObj * CObjMgr::Find_Prototype(const _tchar * pPrototypeTag) //  해당 태그로 맵에서 먼저 찾고 없으면 널, 있으면 second 값 반환
{
	auto iter = find_if(m_ProtoType.begin(), m_ProtoType.end(), CTag_Finder(pPrototypeTag));
	
	if(iter == m_ProtoType.end())
		return nullptr;

	return iter->second;
}

CLayer * CObjMgr::Find_Layer(_uint iLevelIdx, const _tchar * pLayerTag) // 리스트 반환
{
	auto iter = find_if(m_pLayer[iLevelIdx].begin(), m_pLayer[iLevelIdx].end(), CTag_Finder(pLayerTag));
	
	if(iter == m_pLayer[iLevelIdx].end())
		return nullptr;

	return iter->second;
}

void CObjMgr::Free()
{
	for (_uint i = 0; i < m_iNumLevels; i++){
		for (auto& Pair : m_pLayer[i])
			Safe_Release(Pair.second);

		m_pLayer[i].clear();
	}

	Safe_Delete_Array(m_pLayer);

	for (auto& Pair : m_ProtoType)
		Safe_Release(Pair.second);

	m_ProtoType.clear();
}


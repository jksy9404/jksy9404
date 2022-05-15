#include "..\Public\ObjMgr.h"
#include "Layer.h"
#include "GameObj.h"
IMPLEMENT_SINGLETON(CObjMgr)

CObjMgr::CObjMgr()
{
}

HRESULT CObjMgr::Reserve_Container(_uint iNumLevels)
{
	if (nullptr != m_pLayer) // �̹� ���̾�(������Ʈ ����Ʈ)�� �����Ѵٸ� �ߺ��� �ǹǷ� ����ó��
		return E_FAIL;

	m_pLayer = new LAYERS[iNumLevels]; // ������ ���� �����Ҵ����� �� ����(��) ���� ������Ʈ�� �������

	m_iNumLevels = iNumLevels;

	
	return S_OK;
}

HRESULT CObjMgr::Add_Prototype(const _tchar * pPrototypeTag, CGameObj * pGameObj)
{
	if (nullptr != Find_Prototype(pPrototypeTag)) // ���� �����, ������Ÿ�� ���� second��, �̹� ������� ���̶�� ����
		return E_FAIL;

	m_ProtoType.emplace(pPrototypeTag, pGameObj); // ���� �߰�

	return S_OK;
}

HRESULT CObjMgr::Clone_GameObj(_uint iLevelIdx, const _tchar * pLayerTag, const _tchar * pPrototypeTag, void* pArg) // ������ �������� Ŭ�� ��������
{
	if (iLevelIdx > m_iNumLevels || nullptr == m_pLayer)
		return E_FAIL;

	// ���� ������������
	CGameObj* pPrototype = Find_Prototype(pPrototypeTag);
	if (pPrototype == nullptr) // ������ ���ٸ� �纻�� ����� �����Ƿ� ����ó��
		return E_FAIL;

	// ������ �纻����
	CGameObj* pGameObj = pPrototype->Clone(pArg); // Ŭ���� ��׶���� ��ӵ� Ŭ�п��� �������(��������), �θ�Ŭ���� ���ӿ�����Ʈ���� ���۷���ī��Ʈ �÷���
	if (pGameObj == nullptr)// �纻�� �ȸ�������ٸ� ����ó��
		return E_FAIL;

	CLayer* pLayer = Find_Layer(iLevelIdx, pLayerTag); // ������� Ŭ���� �����̿� �����ϱ� ���� ���ε����� �±׷� ���� ���̾ �����ϴ��� ã�� ������ �߰�, ������ ����� �߰�
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

void CObjMgr::Tick(_float fTimeDelta) // ����Ʈ���� ƽ����
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

CGameObj * CObjMgr::Find_Prototype(const _tchar * pPrototypeTag) //  �ش� �±׷� �ʿ��� ���� ã�� ������ ��, ������ second �� ��ȯ
{
	auto iter = find_if(m_ProtoType.begin(), m_ProtoType.end(), CTag_Finder(pPrototypeTag));
	
	if(iter == m_ProtoType.end())
		return nullptr;

	return iter->second;
}

CLayer * CObjMgr::Find_Layer(_uint iLevelIdx, const _tchar * pLayerTag) // ����Ʈ ��ȯ
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


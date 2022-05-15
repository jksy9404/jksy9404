#pragma once
#include "Base.h"

BEGIN(Engine)
class CObjMgr final : public CBase
{
	DECLARE_SINGLETON(CObjMgr);
private:
	CObjMgr();
	virtual ~CObjMgr() = default;

public:
	HRESULT Reserve_Container(_uint iNumLevels);

	// ��ü�� ������ �߰��ϴ� �Լ�
	HRESULT Add_Prototype(const _tchar* pPrototypeTag, class CGameObj* pGameObj);

	// ��ü�� �纻�� �����ϰ� �纻�� m_pLayer�� �߰�
	HRESULT Clone_GameObj(_uint iLevelIdx, const _tchar* pLayerTag, const _tchar* pPrototypeTag, void* pArg);
	// void* �� ������ ������ �����ؼ� �������� ����

public:
	void Tick(_float fTimeDelta);
	void LateTick(_float fTimeDelta);

private:
	map<const _tchar*, class CGameObj*> m_ProtoType;
	typedef map<const _tchar*, class CLayer*> PROTOTYPES;

private:
	/* ���� ������ ���պ��� ��ü���� �����ϳ�. */
	/* ex: �𵥽����ͷ��̾�. ��水ü���̾�. �����̷��̾�. */
	map<const _tchar*, class CLayer*>*		m_pLayer = nullptr;
	typedef map<const _tchar*, class CLayer*> LAYERS;

	_uint										m_iNumLevels = 0;

private:
	class CGameObj* Find_Prototype(const _tchar* pPrototypeTag);
	class CLayer* Find_Layer(_uint iLevelIdx, const _tchar* pLayerTag);


public:
	virtual void Free() override;
};

END
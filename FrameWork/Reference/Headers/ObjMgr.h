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

	// 객체의 원형을 추가하는 함수
	HRESULT Add_Prototype(const _tchar* pPrototypeTag, class CGameObj* pGameObj);

	// 객체의 사본을 생성하고 사본을 m_pLayer에 추가
	HRESULT Clone_GameObj(_uint iLevelIdx, const _tchar* pLayerTag, const _tchar* pPrototypeTag, void* pArg);
	// void* 는 원본의 변수를 선택해서 가져오기 위함

public:
	void Tick(_float fTimeDelta);
	void LateTick(_float fTimeDelta);

private:
	map<const _tchar*, class CGameObj*> m_ProtoType;
	typedef map<const _tchar*, class CLayer*> PROTOTYPES;

private:
	/* 내가 지정한 집합별로 객체들을 보관하낟. */
	/* ex: 언데스몬스터레이어. 배경객체레이어. 유아이레이어. */
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
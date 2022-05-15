#pragma once
#include "Client_Define.h"
#include "GameObj.h"

BEGIN(Client)
class CBackGround final : public CGameObj
{
private:
	explicit CBackGround(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CBackGround(const CBackGround& Prototype);
	virtual ~CBackGround() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg) override;
	virtual void Tick(_float fTmDelta) override;
	virtual void LateTick(_float fTmDelta) override;
	virtual HRESULT Render() override;

public:
	// 원형객체 만들기
	static CBackGround* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObj* Clone(void* pArg) override;
	virtual void Free() override;
};

END
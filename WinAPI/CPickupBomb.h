#pragma once
#include "CPickupItem.h"

class CPlayer;

class CPickupBomb : public CPickupItem
{
public:
	CPickupBomb();
	virtual ~CPickupBomb();

	void Activate(CPlayer* pPlayer) override;

private:
	CImage* m_pPickBombImage;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
};

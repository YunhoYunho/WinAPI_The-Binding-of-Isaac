#pragma once
#include "CMonster.h"

class CImage;
class CAnimator;

enum class BoomflyState
{
	Move,
	Dead,

	Size
};

class CBoomfly : public CMonster
{
public:
	CBoomfly();
	virtual ~CBoomfly();

private:
	CAnimator* m_pAnimator;
	CImage* m_pBoomflyImage;
	CImage* m_pBoomflyDeadImage;

	BoomflyState m_stateBoomfly;
	BoomflyState m_BoomflyState;
	wstring stateBoomfly;

	CSound* pExplosion = RESOURCE->LoadSound(L"Boom", L"Sound\\Monster\\explosions.wav");

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void AnimatorUpdate();

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;
};

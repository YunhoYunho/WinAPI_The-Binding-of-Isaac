#include "framework.h"
#include "CBaby.h"

CBaby::CBaby()
{
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Monster;
	m_strName = L"Baby";

	m_pBabyImage = nullptr;
	m_pBabyDeadImage = nullptr;

	m_vecMoveDir = Vector(0, 0);
	m_vecLookDir = Vector(0, 0);

	m_bIsMove = false;
	m_bIsShot = false;
	m_bIsDead = false;

	m_fSpeed = 30.0f;
	m_iHP = 10;
}

CBaby::~CBaby()
{
}

void CBaby::Init()
{
	m_pBabyImage = RESOURCE->LoadImg(L"Baby", L"Image\\Unit\\Mon_baby.png");
	m_pBabyDeadImage = RESOURCE->LoadImg(L"BabyDead", L"Image\\Effect\\Effect_DEAD.png");

	m_pAnimator = new CAnimator;

	m_pAnimator->CreateAnimation(L"Move", m_pBabyImage, Vector(0.f, 0.f), Vector(120.f, 60.f), Vector(120.f, 0.f), 0, 1);

	m_pAnimator->CreateAnimation(L"Shot", m_pBabyImage, Vector(0.f, 60.f), Vector(120.f, 60.f), Vector(120.f, 0.f), 0, 1, false);

	m_pAnimator->CreateAnimation(L"Dead", m_pBabyDeadImage, Vector(0.f, 0.f), Vector(75.f, 75.f), Vector(75.f, 0.f), 0.1f, 10, false);

	m_pAnimator->Play(L"Move");

	AddComponent(m_pAnimator);

	m_BabyState = BabyState::Move;

	AddCollider(ColliderType::Rect, Vector(50, 50), Vector(0, 0));
}

void CBaby::Update()
{
	if (m_iHP < 1)
	{
		stateBaby = L"Dead";
		RemoveCollider();
	}

	else
	{
		switch (m_BabyState)
		{
			m_vecPlayerPosition = PLAYERPOS;

		case BabyState::Move:
			stateBaby = L"Move";

			if (PLAYERPOS.x < m_vecPos.x)
			{
				left = true;
				right = false;
			}

			if (PLAYERPOS.x > m_vecPos.x)
			{
				left = false;
				right = true;
			}

			if (PLAYERPOS.y < m_vecPos.y)
			{
				up = true;
				down = false;
			}

			if (PLAYERPOS.y > m_vecPos.y)
			{
				up = false;
				down = true;
			}

			if (up) m_vecPos.y -= m_fSpeed * DT;
			if (down) m_vecPos.y += m_fSpeed * DT;
			if (left) m_vecPos.x -= m_fSpeed * DT;
			if (right) m_vecPos.x += m_fSpeed * DT;

		case BabyState::Shot:
			stateBaby = L"Shot";
			CreateMissile();

		case BabyState::Dead:

			if (m_iHP < 1)
			{
				stateBaby = L"Dead";
			}
			else
			{
				m_BabyState = BabyState::Move;
			}
			break;
		}
	}
	AnimatorUpdate();
}

void CBaby::Render()
{
}

void CBaby::Release()
{
}

void CBaby::AnimatorUpdate()
{
	m_pAnimator->Play(stateBaby, false);
}

void CBaby::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"PlayerMissile")
	{
		m_iHP--;
	}

	if (m_iHP < 1)
	{
		m_BabyState = BabyState::Dead;
	}
}

void CBaby::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CBaby::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"�÷��̾�")
	{
		Logger::Debug(L"���Ͱ� �÷��̾�� �浹����");
	}
	else if (pOtherCollider->GetObjName() == L"�̻���")
	{
		Logger::Debug(L"���Ͱ� �̻��ϰ� �浹����");
	}
}
#include "GamePCH.h"
#include "Enemy.h"

Enemy::Enemy(Mesh * amesh, vec2 aposition, ObjectType aType) :
	GameObject(amesh, aposition, aType)
{
	m_Type = aType;

	if (m_Type == ObjectType_MovingEnemy)
	{
		m_MoveType = rand() % 5 + 1; //1-5
	}
	else
	{
		m_MoveType = 0; //not moving
	}
}

Enemy::~Enemy()
{

}

void Enemy::Update(float adelta)
{
	if (m_Type == ObjectType_MovingEnemy)
	{
		Move(adelta);
	}
}

void Enemy::Move(float adelta)
{
	m_Time += adelta;
	m_X = 0.5f * 1.0f * m_Time;
	m_Y = sinf(m_X / (0.5f / (1.0f * PI))) * 5.0f;

	switch (m_MoveType)
	{
	case 1:
		m_Rotation += adelta * 5.0f;
		break;
	case 2:
		m_Position.x += m_Y;
		break;
	case 3:
		m_Position.y += m_Y;
		break;
	case 4:
		m_Position.x += m_Y;
		m_Position.y += m_Y;
		break;
	case 5:
		m_Rotation += adelta * 5.0f;
		m_Position.x += m_Y;
		m_Position.y += m_Y;
		break;
	default:
		break;
	}
}

ObjectType Enemy::GetObjectType()
{
	return m_Type;
}

void Enemy::SetObjectType(ObjectType atype)
{
	m_Type = atype;
}

int Enemy::GetMovementType()
{
	return m_MoveType;
}

void Enemy::SetMovementType(int atype)
{
	m_MoveType = atype;
}

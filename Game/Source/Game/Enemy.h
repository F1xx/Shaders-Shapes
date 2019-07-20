#pragma once

class Enemy : public GameObject
{

public:
	Enemy(Mesh* amesh, vec2 aposition, ObjectType aType);
	~Enemy();

	virtual void Update(float adelta) override;
	virtual void Move(float adelta) override;

	ObjectType GetObjectType();
	void SetObjectType(ObjectType atype);

	int GetMovementType();
	void SetMovementType(int atype);

private:
	ObjectType m_Type;

	float m_X, m_Y, m_Time;

	int m_MoveType;

};
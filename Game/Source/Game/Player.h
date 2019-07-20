#pragma once

class Framework;
class PlayerController;
class Mesh;

class Player : public GameObject
{

public:
	Player(PlayerController* controller, Framework* aframework, Mesh* amesh, vec2 aposition, ObjectType aType);
	~Player();

	virtual void Update(float adelta) override;
	virtual void Move(float adelta) override;

private:
	PlayerController* m_pController;
	Framework* m_pFramework;

	bool LeftWorldBounds();
};
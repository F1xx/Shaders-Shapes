#pragma once

class HUDObject : public GameObject
{
public:
	HUDObject(Mesh* amesh, vec2 aposition, ObjectType aType);
	~HUDObject();

	virtual void Update(float adelta) override;
	virtual void Move(float adelta) override;

};
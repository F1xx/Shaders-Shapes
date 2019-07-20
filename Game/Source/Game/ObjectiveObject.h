#pragma once

class ObjectiveObject : public GameObject
{
public:
	ObjectiveObject(Mesh* amesh, vec2 aposition, ObjectType aType);
	~ObjectiveObject();

	virtual void Update(float adelta) override;
	virtual void Move(float adelta) override;

};
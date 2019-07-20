#pragma once
#include "GameConstants.h"

class Mesh;
class Camera;

class GameObject
{
public:
	GameObject(Mesh* amesh, vec2 aposition, ObjectType aType);
    ~GameObject();

	virtual void Update(float adelta) = 0;
    virtual void Draw();

    virtual void Move(float adelta) = 0;

	vec2 GetPosition();
	void SetPosition(vec2 aposition);

	vec2 GetDirection();
	void SetDirection(vec2 adirection);

	Camera* GetActiveCamera();
	void SetActiveCamera(Camera* acam);

	void SetRadians(float arotation);
	float GetRadians();
	void SetDegrees(float arotation);
	float GetDegrees();

	float GetRadius();
	void SetRadius(float aradius);

	void SetScale(float ascale);
	float GetScale();

	ObjectType GetObjectType();

protected:
	ObjectType m_Type;
	vec2 m_Direction;
    vec2 m_Position;
	Camera* m_ActiveCam;
	float m_Rotation;
	float m_Radius;
    Mesh* m_pMesh;
	float m_Scale;
};
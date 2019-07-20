#include "GamePCH.h"
#include "GameObject.h"

//A standard GameObject. Requires a mesh and position to draw
GameObject::GameObject(Mesh* amesh, vec2 aposition, ObjectType aType)
{
    m_pMesh = amesh;
    m_Position = aposition;
	m_Type = aType;
	m_Radius = STANDARD_RADIUS;
	m_Scale = 1.0f;
	m_Rotation = 0.0f;
	m_Direction = vec2(0.0f, 0.0f);
}

GameObject::~GameObject()
{
	
}

void GameObject::Draw()
{
	m_pMesh->Draw(m_Position, m_ActiveCam, m_Scale, m_Rotation);
}

vec2 GameObject::GetPosition()
{
    return m_Position;
}

void GameObject::SetPosition(vec2 aposition)
{
    m_Position = aposition;
}

vec2 GameObject::GetDirection()
{
	return m_Direction;
}

void GameObject::SetDirection(vec2 adirection)
{
	m_Direction = adirection;
}

Camera* GameObject::GetActiveCamera()
{
	return m_ActiveCam;
}

void GameObject::SetActiveCamera(Camera* acam)
{
	m_ActiveCam = acam;
}

void GameObject::SetRadians(float arotation)
{
	m_Rotation = arotation;
}

float GameObject::GetRadians()
{
	return m_Rotation;
}

void GameObject::SetDegrees(float arotation)
{
	SetRadians((arotation / 180) * PI);
}

float GameObject::GetDegrees()
{
	return (GetRadians() / PI) * 180;
}

//returns a smaller radius for the player for a smaller hitbox
float GameObject::GetRadius()
{
    if (m_Type == ObjectType_Player)
        return m_Radius * 0.5f;
    else
        return m_Radius;
}

void GameObject::SetRadius(float aradius)
{
	m_Radius = aradius;
	SetScale(m_Radius / STANDARD_RADIUS); //Scales the object to the new radius
}

void GameObject::SetScale(float ascale)
{
	m_Scale = ascale;
}

float GameObject::GetScale()
{
	return m_Scale;
}

ObjectType GameObject::GetObjectType()
{
	return m_Type;
}

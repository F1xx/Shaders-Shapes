#include "GamePCH.h"
#include "Camera.h"

Camera::Camera(GameObject * following, float ascale)
{
	m_Target = following;
	m_Position = m_Target->GetPosition();
	m_Scale = ascale;
}

Camera::Camera(vec2 position, float ascale)
{
    m_Position = position;
	m_Scale = ascale;
}

vec2 Camera::Getposition()
{
	return m_Position;
}

void Camera::SetFollowing(GameObject* following)
{
    m_Target = following;
}

void Camera::Update(float adelta)
{
    if(m_Target)
	m_Position = m_Target->GetPosition();
}

void Camera::SetScale(float ascale)
{
	m_Scale = ascale;
}

float Camera::GetScale()
{
	return m_Scale;
}

#pragma once
class GameObject;

class Camera
{
public:
	Camera(GameObject* following, float ascale);
    Camera(vec2 position, float ascale);

	vec2 Getposition();
	void SetFollowing(GameObject* following);
	void Update(float adelta);

	void SetScale(float ascale);
	float GetScale();

protected:
	GameObject* m_Target;
	vec2 m_Position;
	float m_Scale;
};
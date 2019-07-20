#include "GamePCH.h"

Player::Player(PlayerController* controller, Framework* aframework, Mesh* amesh, vec2 aposition, ObjectType aType) :
	GameObject(amesh, aposition, aType)
{
	m_pController = controller;
	m_pFramework = aframework;
}

Player::~Player()
{

}

void Player::Update(float adelta)
{
	float speed = 1.0f;
	int aKeys = m_pController->GetPressedKeys();

	//sprint
	if ((aKeys & KeyValue_Sprint) > 0)
	{
		speed = 2.0f;
	}
	//walk
	if ((aKeys & KeyValue_Walk) > 0)
	{
		speed = 0.5f;
	}

	//movement
	if ((aKeys & KeyValue_Up) > 0)
	{
		m_Direction.y = speed;
	}
	if ((aKeys & KeyValue_Down) > 0)
	{
		m_Direction.y = -speed;
	}
	if ((aKeys & KeyValue_Left) > 0)
	{
		m_Direction.x = -speed;
	}
	if ((aKeys & KeyValue_Right) > 0)
	{
		m_Direction.x = speed;
	}

	//rotation
	if ((aKeys & KeyValue_RotLeft) > 0)
	{
		m_Rotation -= ROTATION_SPEED;
	}
	if ((aKeys & KeyValue_RotRight) > 0)
	{
		m_Rotation += ROTATION_SPEED;
	}

	//Grow while pressed
	if ((aKeys & KeyValue_Grow) > 0)
	{
		m_Scale += adelta;
	}
	//Shrink to normal if unpressed
 	if ((aKeys & KeyValue_Grow) == 0 && m_Scale > 1.0f)
 	{
 		m_Scale -= adelta;
 
 		if (m_Scale < 1.0f)
 		{
 			m_Scale = 1.0f;
 		}
 	}

	//if nothing is pressed slowly return speed to 0, 0
	if (abs(m_Direction.x) > 0 || abs(m_Direction.y) > 0)
	{
		//Set to 0 if it gets close enough
		if (abs(m_Direction.x) < 0.1f)
		{
			m_Direction.x = 0.0f;
		}
		if (abs(m_Direction.y) < 0.1f)
		{
			m_Direction.y = 0.0f;
		}


		if ((aKeys & KeyValue_Up) == 0 && (aKeys & KeyValue_Down) == 0)
		{
			if (m_Direction.y > 0)
			{
				m_Direction.y -= DECAY_RATE;
			}
			else if (m_Direction.y < 0)
			{
				m_Direction.y += DECAY_RATE;
			}
		}
		if ((aKeys & KeyValue_Left) == 0 && (aKeys & KeyValue_Right) == 0)
		{
			if (m_Direction.x > 0)
			{
				m_Direction.x -= DECAY_RATE;
			}
			else if (m_Direction.x < 0)
			{
				m_Direction.x += DECAY_RATE;
			}
		}
	}
	Move(adelta);
}

void Player::Move(float adelta)
{
	vec2 originalpos = m_Position;
	vec2 velocity = m_Direction * SPEED;

	m_Position += velocity * adelta;

	//if the player is trying to leave the map revert their movement
	if (LeftWorldBounds())
	{
		m_Position = originalpos;
	}
}

//Checks if the player has exited the world
bool Player::LeftWorldBounds()
{
	//(world size is a 4*4 of the screen, player starts dead center)
	int width = m_pFramework->GetWindowWidth();
	int height = m_pFramework->GetWindowHeight();

	if (m_Position.x < (0 - width) || m_Position.x > width) //if they are off the screen to the left or right
	{
		return true;
	}
	if (m_Position.y < (0 - height) || m_Position.y > height) //if they are off the screen to the top or bottom
	{
		return true;
	}

	return false;
}

#pragma once

const enum ObjectType
{
	ObjectType_StaticEnemy = 0,
	ObjectType_MovingEnemy,
	ObjectType_Player,
	ObjectType_Goal,
    ObjectType_HUD,
};

const enum GameStates
{
	GameState_Play,
	GameState_Win,
	GameState_Die,
	GameState_Reset,
	GameState_Load,

	GameState_StateCount
};

const float SPEED = 250.0f; //Player's Speed per second in pixels
//const float MAX_SPEED = 300.0f;
const float DECAY_RATE = 0.2f; //per second away from 1 or -1
const float ROTATION_SPEED = 0.05f; //angle of rotation per frame in radians
const float STANDARD_RADIUS = 30.0f; // Standard radius for triangle fan
const float DEFAULT_SCALE = 1.0f;
const int MAP_SIZE = 100;
const float DEFAULT_LINE_SIZE = 10.0f;

const int LEVEL_DIFFICULTY_INCREMENT = 5;

//enemy numbers
const int MAX_ENEMY_COUNT = 100;
const int MAX_MOVING_ENEMIES = 30;
const int START_ENEMY_COUNT = 40;
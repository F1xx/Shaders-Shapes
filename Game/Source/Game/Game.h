#ifndef __Game_H__
#define __Game_H__

class ShaderProgram;
class Mesh;
class PlayerController;
class Camera;
class Timer;

//objects:
class GameObject;
class Player;
class Enemy;
class HUDObject;
class ObjectiveObject;

class Game : public GameCore
{
protected:
    ShaderProgram* m_pShader;

    Mesh* m_pPlayerMesh;
    Mesh* m_pEnemyMesh;
	Mesh* m_pGoalMesh;
    Mesh* m_pMapBackgroundMesh;
	Mesh* m_pLevelBackgroundMesh;

	Player* m_pPlayerObject;
	ObjectiveObject* m_pGoalObject;
	HUDObject* m_pMapBackgroundObject;
	HUDObject* m_pLevelBackgroundObject;
    std::vector<Enemy*> m_pEnemies;
	std::vector<Enemy*> m_pMovingEnemies;

    PlayerController* m_pPlayerController;

	Camera* m_pPlayerCamera;
    Camera* m_pMapCam;

	Timer* m_Timer;

	unsigned char m_GameState;
    vec2 m_MapPos;

	//draws all objects and sets their camera
	void DrawAllObjects(Camera* acam);

public:
    Game(Framework* pFramework);
    virtual ~Game();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height);
    virtual void LoadContent();

    virtual void Update(float deltatime);
    virtual void Draw() override;

    virtual void OnEvent(Event *aevent) override;

    bool IsColliding(GameObject* obj1, GameObject* obj2);

    vec2 RandomPos();
	void Reset();

    float CalculateDistanceSquared(float a, float b);

	int m_LevelDifficulty;
	int m_LevelNum;
};

#endif //__Game_H__

#include "GamePCH.h"
#include "Game.h"

Game::Game(Framework* pFramework)
: GameCore(pFramework)
{
    m_pShader = 0;
    m_pPlayerMesh = 0;
	m_pGoalMesh = 0;
    m_pPlayerController = 0;
	m_pPlayerObject = 0;
	m_pGoalObject = 0;
	m_pEnemyMesh = 0;
	m_GameState = GameState_Load;
	m_pPlayerCamera = 0;
    m_pMapCam = 0;
    m_pMapBackgroundMesh = 0;
    m_pMapBackgroundObject = 0;
	m_pLevelBackgroundObject = 0;
	m_pLevelBackgroundMesh = 0;
	m_Timer = 0;

	m_LevelDifficulty = 0;
	m_LevelNum = 1;
}

Game::~Game()
{
    SafeDelete(m_pShader);
    SafeDelete(m_pPlayerMesh);
    SafeDelete(m_pPlayerObject);
    SafeDelete(m_pPlayerController);
    SafeDelete(m_pEnemyMesh);
	SafeDelete(m_pGoalMesh);
	SafeDelete(m_pGoalObject);
	SafeDelete(m_pPlayerCamera);
    SafeDelete(m_pMapCam);
    SafeDelete(m_pMapBackgroundObject);
    SafeDelete(m_pMapBackgroundMesh);
	SafeDelete(m_pLevelBackgroundObject);
    SafeDelete(m_pLevelBackgroundMesh);
	SafeDelete(m_Timer);

    for (int i = 0; i < MAX_ENEMY_COUNT; i++)
    {
        SafeDelete(m_pEnemies.at(i));
    }
	for (int i = 0; i < MAX_MOVING_ENEMIES; i++)
	{
		SafeDelete(m_pMovingEnemies.at(i));
	}
}

void Game::OnSurfaceChanged(unsigned int width, unsigned int height)
{
    glViewport( 0, 0, width, height );
}

void Game::LoadContent()
{
    wglSwapInterval(1);
    // Seed random.
    srand( (unsigned int)GetSystemTime() );
    
    CheckForGLErrors();

    // Turn on depth buffer testing.
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );

    // Turn on alpha blending.
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	//Make a timer, used for both death and win animations
	m_Timer = new Timer(1.0f);

	//Controllers
	m_pPlayerController = new PlayerController(m_pFramework); //Registers input events to control the player

    // Create our shaders.
    m_pShader = new ShaderProgram("Data/Shaders/Color.vert", "Data/Shaders/Color.frag");

	//Meshes
    m_pPlayerMesh = new Mesh(m_pShader);
	m_pGoalMesh = new Mesh(m_pShader);
    m_pEnemyMesh = new Mesh(m_pShader);
    m_pMapBackgroundMesh = new Mesh(m_pShader); //Black Backing to the Minimap viewport
	m_pLevelBackgroundMesh = new Mesh(m_pShader); //White lines on the border of the map

	//Objects
	m_pPlayerObject = new Player(m_pPlayerController, m_pFramework, m_pPlayerMesh, vec2(0.0f, 0.0f), ObjectType_Player);
	m_pGoalObject = new ObjectiveObject(m_pGoalMesh, vec2(0.0f, 0.0f), ObjectType_Goal); //spawn the goal in the top right (player is bottom left)
    m_pMapBackgroundObject = new HUDObject(m_pMapBackgroundMesh, vec2(0.0f, 0.0f), ObjectType_HUD);
	m_pLevelBackgroundObject = new HUDObject(m_pLevelBackgroundMesh, vec2(0.0f, 0.0f), ObjectType_HUD);
	for (int i = 0; i < MAX_ENEMY_COUNT; i++)
	{
		m_pEnemies.push_back(new Enemy(m_pEnemyMesh, RandomPos(), ObjectType_StaticEnemy));
	}
	for (int i = 0; i < MAX_MOVING_ENEMIES; i++)
	{
		m_pMovingEnemies.push_back(new Enemy(m_pEnemyMesh, RandomPos(), ObjectType_MovingEnemy));
	}

	//cameras
	m_pPlayerCamera = new Camera(m_pPlayerObject, 1.0f);
    m_pMapCam = new Camera(vec2(0.0f, 0.0f), 2.4f);

    //Enemy Triangle Mesh
    VertexAttributes vertexAttributes[] = {
        VertexAttributes(0.0f, 0.0f, COLOR::Red),
        VertexAttributes(STANDARD_RADIUS, 0.0f, COLOR::Red),
        VertexAttributes(STANDARD_RADIUS * 0.5f, STANDARD_RADIUS, COLOR::Black)
    };

	//Map Border
	VertexAttributes levelBack[4] = {
		VertexAttributes((0.0f - m_pFramework->GetWindowWidth() - STANDARD_RADIUS), (m_pFramework->GetWindowHeight() + STANDARD_RADIUS), COLOR::White),
		VertexAttributes((0.0f - m_pFramework->GetWindowWidth() - STANDARD_RADIUS), (0.0f - m_pFramework->GetWindowHeight() - STANDARD_RADIUS), COLOR::White),
		VertexAttributes((m_pFramework->GetWindowWidth() + STANDARD_RADIUS), (0.0f - m_pFramework->GetWindowHeight() - STANDARD_RADIUS), COLOR::White),
		VertexAttributes((m_pFramework->GetWindowWidth() + STANDARD_RADIUS), (m_pFramework->GetWindowHeight() + STANDARD_RADIUS), COLOR::White),
	};

	//Set Meshes
	m_pEnemyMesh->GenerateMesh(3, vertexAttributes, GL_TRIANGLES);
	m_pLevelBackgroundMesh->GenerateMesh(4, levelBack, GL_LINE_LOOP);
	m_pGoalMesh->GenerateTriangleFan(0.0f, 0.0f, 5, STANDARD_RADIUS, COLOR::Green);
    m_pPlayerMesh->GenerateTriangleFan(m_pPlayerObject->GetPosition().x, m_pPlayerObject->GetPosition().y, 8, STANDARD_RADIUS, COLOR::Magenta);
    m_pMapBackgroundMesh->GenerateTriangleFan(m_pPlayerObject->GetPosition().x, m_pPlayerObject->GetPosition().y, 8, 400.0f, COLOR::Black);


    CheckForGLErrors();
	//done loading start playing and reposition objects
	Reset();
}

void Game::Update(float deltatime)
{
#if WIN32
	//always do events FIRST
    while (!m_pFramework->GetEventManager()->IsEmpty())
    {
        OnEvent(m_pFramework->GetEventManager()->GetNextEvent());
    }


    //only do this if this game state is true
    if (m_GameState == GameState_Play)
    {
		if (m_pFramework->IsKeyDown('1'))
		{
			m_pFramework->SetWindowSize(600, 600);
		}
		if (m_pFramework->IsKeyDown('2'))
		{
			m_pFramework->SetWindowSize(960, 540);
		}
		if (m_pFramework->IsKeyDown('3'))
		{
			m_pFramework->SetWindowSize(360, 640);
		}
		//Check if the player is resetting
		if ((m_pPlayerController->GetPressedKeys() & KeyValue_Reset) > 0)
		{
			m_GameState = GameState_Reset;
			Reset();
		}

		//update the player
		m_pPlayerObject->Update(deltatime);

		//update the enemies
		//These guys don't do anything with their update rn. Just a waste of cycles
		/*for (int i = 0; i < START_ENEMY_COUNT + m_LevelDifficulty; i++)
		{
			m_pEnemies.at(i)->Update(deltatime);
		}*/

		if (m_LevelNum > 1)
		{
			for (int i = 0; i < MAX_MOVING_ENEMIES; i++)
			{
				if (m_pMovingEnemies.at(i)->GetMovementType() <= m_LevelNum - 1)
				{
					m_pMovingEnemies.at(i)->Update(deltatime);
				}
			}
		}

		//update the goal
		m_pGoalObject->Update(deltatime);
        m_pMapBackgroundObject->Update(deltatime);

		//check collision
		for (int i = 0; i < START_ENEMY_COUNT + m_LevelDifficulty; i++)
		{
			if (IsColliding(m_pPlayerObject, m_pEnemies.at(i)))
			{
				m_GameState = GameState_Die;

				DeathEvent* event = new DeathEvent(EventType_Death);
				m_pFramework->GetEventManager()->AddEvent(event);
			}
		}
		//only check collision of active moving enemies
		if (m_LevelNum > 1)
		{
			for (int i = 0; i < MAX_MOVING_ENEMIES; i++)
			{
				if (m_pMovingEnemies.at(i)->GetMovementType() <= m_LevelNum - 1)
				{
					if (IsColliding(m_pPlayerObject, m_pMovingEnemies.at(i)))
					{
						m_GameState = GameState_Die;

						DeathEvent* event = new DeathEvent(EventType_Death);
						m_pFramework->GetEventManager()->AddEvent(event);
					}
				}
			}
		}
		//did we win?
		if (IsColliding(m_pPlayerObject, m_pGoalObject))
		{
			TimedEvent* event = new TimedEvent(EventType_Win);
			m_pFramework->GetEventManager()->AddEvent(event);
		}
	}
	if (m_GameState == GameState_Win)
	{
		m_Timer->Update(deltatime);

		//keep updating the Victory object so we can animate it
		m_pPlayerCamera->SetFollowing(m_pGoalObject);
		m_pGoalObject->Update(deltatime);
		m_pGoalObject->SetRadians(m_pGoalObject->GetRadians() + (deltatime * 5));
		m_pGoalObject->SetScale(m_pGoalObject->GetScale() + deltatime + 0.25f);

		if (m_Timer->IsComplete())
		{
			TimedEvent* event = new TimedEvent(EventType_TimeEnd);
			m_pFramework->GetEventManager()->AddEvent(event);
		}
	}
	if (m_GameState == GameState_Die)
	{
		m_Timer->Update(deltatime);

		m_pPlayerObject->SetScale(m_pPlayerObject->GetScale() - deltatime);

		if (m_Timer->IsComplete())
		{
			TimedEvent* event = new TimedEvent(EventType_TimeEnd);
			m_pFramework->GetEventManager()->AddEvent(event);
		}
	}
    //always update camera
    m_pPlayerCamera->Update(deltatime);

    m_pMapBackgroundObject->SetPosition(m_pPlayerObject->GetPosition());
#endif
}

void Game::Draw()
{
    // Setup the values we will clear to, then actually clear the color and depth buffers.
    glClearColor( 0.0f, 0.0f, 0.4f, 0.0f ); // (Red, Green, Blue, Alpha) - Dark blue
#if WIN32
    glClearDepth( 1 ); // 1 is maximum depth
#endif
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


    for (int i = 0; i < 2; i++)
    {
        if (i == 0) // gamescreen
        {
            glUseProgram(m_pShader->GetProgram());
            glViewport(0, 0, m_pFramework->GetWindowWidth(), m_pFramework->GetWindowHeight());
			DrawAllObjects(m_pPlayerCamera);
		}
        else if(i == 1) // minimap
        {
            glUseProgram(m_pShader->GetProgram());
            glViewport((GLint)(m_pFramework->GetWindowWidth() - (MAP_SIZE + 10)), 10, MAP_SIZE, MAP_SIZE);
			m_pMapBackgroundObject->SetActiveCamera(m_pPlayerCamera);
			m_pMapBackgroundObject->Draw();
			DrawAllObjects(m_pMapCam);
        }
    }
    // Check for errors.
    CheckForGLErrors();
}

//This is what actually Draws everything on the screen
//@para 'acam' is a camera pointer which sets the active camera of the objects so they draw appropriately
void Game::DrawAllObjects(Camera* acam)
{
	m_pLevelBackgroundObject->SetActiveCamera(acam);
	m_pLevelBackgroundObject->Draw();

	for (int i = 0; i < START_ENEMY_COUNT + m_LevelDifficulty; i++)
	{
		m_pEnemies.at(i)->SetActiveCamera(acam);
		m_pEnemies.at(i)->Draw();
	}

	//only draw moving enemies after level 1.
	if (m_LevelNum > 1)
	{
		for (int i = 0; i < MAX_MOVING_ENEMIES; i++)
		{
			if (m_pMovingEnemies.at(i)->GetMovementType() <= m_LevelNum - 1)
			{
				m_pMovingEnemies.at(i)->SetActiveCamera(acam);
				m_pMovingEnemies.at(i)->Draw();
			}
		}
	}

	m_pPlayerObject->SetActiveCamera(acam);
	m_pPlayerObject->Draw();

	m_pGoalObject->SetActiveCamera(acam);
	m_pGoalObject->Draw();
}

//Handles the events or delegates them to things that handle them
void Game::OnEvent(Event *aevent)
{
    if (aevent->GetEventType() == EventType_Input)
    {
        //send the event to the player controller
        m_pPlayerController->SetFlag(aevent);
    }
	else if (aevent->GetEventType() == EventType_Win)
	{
		m_pFramework->GetEventManager()->PopEvent();

		TimedEvent* event = new TimedEvent(EventType_TimeStart);
		m_pFramework->GetEventManager()->AddEvent(event);

		m_GameState = GameState_Win;

		m_LevelDifficulty += LEVEL_DIFFICULTY_INCREMENT;
		if (m_LevelDifficulty + START_ENEMY_COUNT > MAX_ENEMY_COUNT)
			m_LevelDifficulty = MAX_ENEMY_COUNT - START_ENEMY_COUNT;

		m_LevelNum++;
	}
	else if (aevent->GetEventType() == EventType_TimeStart)
	{
		m_pFramework->GetEventManager()->PopEvent();

		m_Timer->Start();
	}
	else if (aevent->GetEventType() == EventType_TimeEnd)
	{
		m_pFramework->GetEventManager()->PopEvent();
		m_Timer->Stop();
		Reset();
	}
	else if (aevent->GetEventType() == EventType_Death)
	{
		m_GameState = GameState_Die;
		m_pFramework->GetEventManager()->PopEvent();

		TimedEvent* event = new TimedEvent(EventType_TimeStart);
		m_pFramework->GetEventManager()->AddEvent(event);
	}
}

//checks if 2 game objects are colliding with circle collision
bool Game::IsColliding(GameObject* obj1, GameObject* obj2)
{
    vec2 pos1 = obj1->GetPosition();
    vec2 pos2 = obj2->GetPosition();

    float distancesqre = (((pos1.x - pos2.x) * (pos1.x - pos2.x)) + ((pos1.y - pos2.y) * (pos1.y - pos2.y)));
    float radii = obj1->GetRadius() + obj2->GetRadius();

    if (distancesqre <= radii * radii)
    {
        return true;
    }
    return false;
}

//Used for enemies. Generates a random position for them and ensures it is not where the player spawns.
vec2 Game::RandomPos()
{    
    float x = (float)(rand() % (m_pFramework->GetWindowWidth() * 2) - m_pFramework->GetWindowWidth());
    float y = (float)(rand() % (m_pFramework->GetWindowHeight() * 2) - m_pFramework->GetWindowHeight());


	//if the pos is inside of the starting area remake it until it isn't
	bool cont = true;
	while (cont)
	{
		for (int i = 0; i < 2; i++)
		{
			if (x < STANDARD_RADIUS * 2.0f && x > STANDARD_RADIUS * -2.0f)
			{
				i--;
				x = (float)(rand() % (m_pFramework->GetWindowWidth() * 2) - m_pFramework->GetWindowWidth());
			}
			if (y < STANDARD_RADIUS * 2.0f && y > STANDARD_RADIUS * -2.0f)
			{
				i--;
				y = (float)(rand() % (m_pFramework->GetWindowWidth() * 2) - m_pFramework->GetWindowWidth());
			}
		}
		cont = false;
	}    
    return vec2(x, y);
}

//Resets positions, scales, etc
void Game::Reset()
{
	for (int i = 0; i < MAX_ENEMY_COUNT; i++)
	{
		m_pEnemies.at(i)->SetPosition(RandomPos());
	}
	for (int i = 0; i < MAX_MOVING_ENEMIES; i++)
	{
		m_pMovingEnemies.at(i)->SetPosition(RandomPos());
	}

	m_pPlayerObject->SetPosition(vec2(0.0f, 0.0f));
	m_pPlayerObject->SetDegrees(0.0f);
	m_pPlayerObject->SetScale(DEFAULT_SCALE);

	m_Timer->Reset();

	//set the goal to one of the 4 corners
	char pos = rand() % 4 + 1;
	vec2 Goalpos;
	switch (pos)
	{
	case 1:
		Goalpos = vec2(m_pFramework->GetWindowWidth() - 20.0f, m_pFramework->GetWindowHeight() - 20.0f);
		break;
	case 2:
		Goalpos = vec2(0.0f - m_pFramework->GetWindowWidth() + 20.0f, m_pFramework->GetWindowHeight() - 20.0f);
		break;
	case 3:
		Goalpos = vec2(0.0f - m_pFramework->GetWindowWidth() + 20.0f, 0.0f - m_pFramework->GetWindowHeight() + 20.0f);
		break;
	case 4:
		Goalpos = vec2(m_pFramework->GetWindowWidth() - 20.0f, 0.0f - m_pFramework->GetWindowHeight() + 20.0f);
		break;
	default:
		break;
	}

	m_pGoalObject->SetScale(DEFAULT_SCALE);
	m_pGoalObject->SetRadians(0.0f);
	m_pGoalObject->SetPosition(Goalpos);
	m_pPlayerCamera->SetFollowing(m_pPlayerObject);

	m_GameState = GameState_Play;
}

//returns the squared distance of 2 floats passed in. 
//Avoids rooting them due to the amount of work rooting uses
float Game::CalculateDistanceSquared(float a, float b)
{
    return ((a * a) * (a * a)) - ((b * b) * (b * b));
}

#include "GamePCH.h"

#if _DEBUG
//#pragma comment( lib, "../Output/Framework-Win32/Win32/Debug/Framework-Win32.lib" )
#else
#pragma comment( lib, "../Output/Framework-Win32/Win32/Release/Framework-Win32.lib" )
#endif
#pragma comment( lib, "opengl32.lib" )

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Framework* pFramework = new Framework();

    GameCore* pGame = new Game( pFramework );

    pFramework->Init( SCREEN_WIDTH, SCREEN_HEIGHT );
    pFramework->Run( pGame );
    pFramework->Shutdown();

    delete( pGame );
    delete( pFramework );

	PrintLeaks();
}

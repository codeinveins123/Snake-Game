#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <windows.h>

#ifdef _WIN32
    #pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#endif

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    HWND hWnd = GetConsoleWindow();
    ShowWindow( hWnd, SW_HIDE );
    Game game;
    game.Run();

    return 0;
}
#pragma once


#include "windows.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <atlstr.h>


class PhiEngine
{
private:
	static bool IsOnlyInstance(LPCTSTR gameTitle);
	static bool CheckStorage(const DWORDLONG diskSpaceNeeded);
	static bool CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded);
	static DWORD ReadCPUSpeed();

	static bool IsExiting();
	static void GameLoop();

	enum GameState {
		Uninitialized,
		SplashScreen,
		Paused,
		Menu,
		Playing,
		Exiting
	};

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;


public:
	static bool Initialize();
	static void Start();

};


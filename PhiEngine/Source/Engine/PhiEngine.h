#pragma once


#include "windows.h"
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Text.hpp>
#include "SplashScreen.h"
#include "PhiEngineAudio.h"
#include "GameObjectManager.h"
#include <iostream>
#include <iomanip>
#include <sstream>
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
		LoadAssets,
		Playing,
		Exiting
	};

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
	static PhiEngineAudio _audioManager;
	static GameObjectManager* _gameObjectManager;
	static sf::Clock _gameTime;

	static sf::Font _font;
	static sf::Text _frameCount;
	static sf::Texture TEST_TEX;
	static sf::Sprite TEST_SPRITE;
	static float _timeLastFrame;


public:
	static bool Initialize();
	static void Start();

};


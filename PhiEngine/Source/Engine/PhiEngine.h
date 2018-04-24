#pragma once


#include "windows.h"
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Text.hpp>
#include "SplashScreen.h"
#include "PhiEngineAudio.h"
#include "GameObjectManager.h"
#include "PhysicsEngine.h"
#include "InputManager.h"
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
		GameOver,
		Win,
		LoadAssets,
		Playing,
		Exiting
	};
	enum Levels {
		Level1,
		Level2,
	};
	
	static GameState _gameState;
	static Levels  _level;
	static sf::RenderWindow _mainWindow;
	static PhiEngineAudio _audioManager;
	static GameObjectManager* _gameObjectManager;
	static PhysicsEngine* _physicsEngine;
	static InputManager* _inputManager;
	static sf::Clock _gameTime;
	static GameObject* _mainUser;
	static GameObject* _mainUser2;

	static sf::Font _font;
	static sf::Text _frameCount;
	static sf::Texture TEST_TEX;
	static sf::Sprite TEST_SPRITE;
	static float _timeLastFrame;


public:
	static bool Initialize();
	static void Start();

};


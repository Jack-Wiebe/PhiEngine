#include "PhiEngine.h"

using namespace std;
PhiEngine::GameState PhiEngine::_gameState;
PhiEngineAudio PhiEngine::_audioManager;
sf::RenderWindow PhiEngine::_mainWindow;
GameObjectManager* PhiEngine::_gameObjectManager;
PhysicsEngine* PhiEngine::_physicsEngine;
InputManager* PhiEngine::_inputManager;
sf::Clock PhiEngine::_gameTime;
sf::Text PhiEngine::_frameCount;
sf::Font PhiEngine::_font;
float PhiEngine::_timeLastFrame = 0.0f;
GameObject* PhiEngine::_mainUser;


sf::Texture PhiEngine::TEST_TEX;
sf::Sprite PhiEngine::TEST_SPRITE;

bool PhiEngine::IsOnlyInstance(LPCTSTR gameTitle)
{
	HANDLE handle = CreateMutex(NULL, TRUE, gameTitle);
	if (GetLastError() != ERROR_SUCCESS)
	{
		HWND hWnd = FindWindow(gameTitle, NULL);
		if (hWnd)
		{  // An instance of your game is already running.
			ShowWindow(hWnd, SW_SHOWNORMAL);
			SetFocus(hWnd);
			SetForegroundWindow(hWnd);
			SetActiveWindow(hWnd);
			cout << "Multiple instances detected" << endl;
			return false;
		}
	}

	cout << "Only one instance detected" << endl;
	return true;
}

bool PhiEngine::CheckStorage(const DWORDLONG diskSpaceNeeded)
{

	LPCTSTR lpDirectoryName = NULL;
	__int64 lpFreeBytesAvailable;
	__int64 lpTotalNumberOfBytes;
	__int64 lpTotalNumberOfFreeBytes;

	GetDiskFreeSpaceEx(lpDirectoryName, (PULARGE_INTEGER)&lpFreeBytesAvailable, (PULARGE_INTEGER)&lpTotalNumberOfBytes, (PULARGE_INTEGER)&lpTotalNumberOfFreeBytes);
	if ((DWORDLONG)lpTotalNumberOfBytes <= diskSpaceNeeded)
	{
		cout << "No Availible Drive Space" << endl;
		return false;
	}


	cout << "Drive Space Availible " << endl;
	cout << "Requested " << diskSpaceNeeded << " bytes needed of " << (DWORDLONG)lpTotalNumberOfBytes << " availible bytes" << endl;
	return true;

}

bool PhiEngine::CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded)
{
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	

	cout << status.ullTotalPhys << " bytes of Physical Memory availible for the " << physicalRAMNeeded << " bytes needed" << endl;

	if (status.ullTotalPhys <= physicalRAMNeeded)
	{  /* you don’t have enough physical memory. Tell the player to go get a real computer and give this one to his mother. */
	   //GCC_ERROR(“CheckMemory Failure: Not enough physical memory.”);

		cout << "CheckMemory Failure : Not enough physical memory." << endl;
		return false;
	}

	cout << status.ullAvailVirtual << " bytes of Virtual Memory availible for the " << virtualRAMNeeded << " bytes needed" << endl;

	// Check for enough free memory.
	if (status.ullAvailVirtual <= virtualRAMNeeded)
	{
		/* you don’t have enough virtual memory available. Tell the player to shut down the copy of Visual Studio running in the background. */
		//GCC_ERROR(“CheckMemory Failure: Not enough virtual memory.”);

		cout << "CheckMemory Failure: Not enough virtual memory." << endl;
		return false;
	}

	//char *buff = GCC_NEW char[virtualRAMNeeded];
	//if (buff) {
	//delete[] buff;
	//}else{
	// even though there is enough memory, it isn’t available in one block, which can be critical for games that manage their own memory
	//GCC_ERROR(“CheckMemory Failure: Not enough contiguous memory.”);
	//cout << " Not enough physical memory" << endl;
	//return false;
	//} 

	return true;
}

DWORD PhiEngine::ReadCPUSpeed()
{
	DWORD BufSize = sizeof(DWORD);
	DWORD dwMHz = 0;
	DWORD type = REG_DWORD;
	DWORD strType = REG_SZ;
	CString architecture;
	HKEY hKey;

	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey);
	if (lError == ERROR_SUCCESS)
	{
		// query the key:  
		if (RegQueryValueEx(hKey, "~MHz", NULL, &type, (LPBYTE)&dwMHz, &BufSize) != ERROR_SUCCESS)
		{
			cout << "Could not read CPU clock speed" << endl;
			return -1;
		}
		else
		{
			cout << dwMHz << "MHz cpu speed" << endl;
		}

		long aError = RegQueryValueEx(hKey, "ProcessorNameString", NULL, &strType, (LPBYTE)(architecture.GetBuffer(MAX_PATH)), &BufSize);

		if (aError != ERROR_SUCCESS)
		{
			while (aError == ERROR_MORE_DATA) {
				BufSize++;
				aError = RegQueryValueEx(hKey, "ProcessorNameString", NULL, &strType, (LPBYTE)(architecture.GetBuffer(MAX_PATH)), &BufSize);
			}
			//cout << "Error reading from register" << endl;
			//cout << "Error Code: " << aError << endl;
		}


		cout << architecture << endl;

		architecture.ReleaseBuffer();


	}

	return dwMHz;
}

bool PhiEngine::Initialize()
{
	_gameState = Uninitialized;

	LPCTSTR Title = "PhiEngine";
	if (!IsOnlyInstance(Title))
	{
		//error
		return false;
	}
	DWORDLONG SpaceNeeded = 300000000;
	if (!CheckStorage(SpaceNeeded))
	{
		//error
		return false;
	}
	DWORDLONG RAMNeeded = 300000000;
	DWORDLONG VRAMNeeded = 300000000;
	if (!CheckMemory(RAMNeeded, VRAMNeeded))
	{
		//error
		return false;
	}

	DWORD Success = ReadCPUSpeed();
	if (Success < 0)
		return false;



	if (_gameState != Uninitialized)
		return false;

	//inti Audio
	sf::SoundBuffer buffer = sf::SoundBuffer();
	std::vector<std::string> files = std::vector<std::string>();
	///
	///TODO: this is where you populate sound effects for the game
	///
	files.push_back("click.wav");

	std::string music = "splashmusic.ogg";
	_audioManager.Initialize(buffer, files, music);
	_audioManager.PlayMusic();


	//init Graphics
	_mainWindow.create({ 1024,620 }, "PhiEngine");
	if (!_mainWindow.isOpen())
		return false;
	_mainWindow.setFramerateLimit(60);


	//splashscreen
	SplashScreen::init(_mainWindow.getView().getSize());
	_gameState = SplashScreen;

	return true;
}

void PhiEngine::Start()
{

	while (!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.close();
}

bool PhiEngine::IsExiting()
{
	sf::Event m_event;
	//return false;
	while (_mainWindow.pollEvent(m_event)) {
		if (m_event.type == sf::Event::Closed)
		{
			return true;
		}
	}
	return false;
}

void PhiEngine::GameLoop()
{	
	///
	///Splash Screen Loop
	///
	while (_gameState == SplashScreen)
	{

		SplashScreen::draw(_mainWindow);

		sf::Event m_event;
		while (_mainWindow.pollEvent(m_event))
		{
			std::cout << "first poll" << std::endl;
			if (m_event.type == sf::Event::KeyPressed
				|| m_event.type == sf::Event::MouseButtonPressed)
			{
				_audioManager.StopMusic();
				_gameTime = sf::Clock();
				_frameCount = sf::Text();
				//_frameCount.setPosition(_mainWindow.getSize().x / 2, _mainWindow.getSize().y / 2);
				//_frameCount.setFont()
				/*if (_font.loadFromFile("../Assets/Fonts/d7.ttf") != true)
				{
					cout << "failed to load font" << endl;
					return;
				}

				_frameCount.setFont(_font);
				_frameCount.setPosition(0.0f,0.0f);
				_frameCount.setFillColor(sf::Color::Magenta);

				if (TEST_TEX.loadFromFile("../Assets/Images/phi.png") != true)
				{
					cout << "failed to load image" << endl;
					return;
				}

				cout << "Test image loaded..." << endl;
				TEST_SPRITE.setTexture(TEST_TEX);
				TEST_SPRITE.setOrigin(TEST_SPRITE.getLocalBounds().width / 2.0f, TEST_SPRITE.getLocalBounds().height / 2.0f);
				TEST_SPRITE.setScale(0.2f,0.2f);
				TEST_SPRITE.setPosition((_mainWindow.getSize().x / 2.0f), (_mainWindow.getSize().y / 2.0f));
				*/

				_gameState = LoadAssets;
				break;
			}
		}

		
	}

	///
	///Load Assets
	///
	while (_gameState == LoadAssets)
	{
		_gameObjectManager = new GameObjectManager();
		_physicsEngine = new PhysicsEngine(&_gameTime);
		_inputManager = new InputManager();
		

		GameObject * player = _gameObjectManager->Instantiate("player");
		player->SetTexture("phi.png");
		player->SetSprite();
		player->SetTransform(TransformComponent((_mainWindow.getSize().x / 2.0f), (_mainWindow.getSize().y / 2.0f)-150));
		player->SetScale(sf::Vector2f(.2f, .2f));
		player->AddComponent(new PhysicsComponent(_physicsEngine));
		player->GetComponent<PhysicsComponent>()->Awake();

		GameObject * child = _gameObjectManager->Instantiate("child");
		
		child->SetTexture("phi.png");
		child->SetSprite();
		
		//child->SetParent(player);
		child->SetTransform(TransformComponent((_mainWindow.getSize().x / 2.0f), (_mainWindow.getSize().y / 2.0f)+ 100));
		child->SetScale(sf::Vector2f(.2f, .2f));
		child->AddComponent(new PhysicsComponent(_physicsEngine, sf::Vector2f(0.0,9.8), false, 1.0));
		child->GetComponent<PhysicsComponent>()->Awake();
		//player->SetScale(sf::Vector2f(.10, .05f));

		_mainUser = child;
		_gameState = Playing;

	}
	
	float frameCount;
	stringstream stream;
	///
	///Game Logic Layer
	///
	while (true) {
		switch (_gameState)
		{


		case Menu:
		{
			//frame count
			frameCount = 1.0f / (_gameTime.getElapsedTime().asSeconds() - _timeLastFrame);
			_timeLastFrame = _gameTime.getElapsedTime().asSeconds();
			stream << fixed << setprecision(2) << frameCount;

			//text rendering
			_gameObjectManager->Update(_gameTime.getElapsedTime().asSeconds());
			_frameCount.setString(stream.str());

			//image positon
			//TEST_SPRITE.setPosition((_mainWindow.getSize().x / 2), (_mainWindow.getSize().y / 2));
			TEST_SPRITE.rotate(1.0f);

			//rendering
			_mainWindow.clear(sf::Color::White);

			_mainWindow.draw(TEST_SPRITE);
			_mainWindow.draw(_frameCount);

			_mainWindow.display();
		}
		break;
		case Paused:
		{

		}
		break;
		case Playing:
		{
			_mainWindow.clear(sf::Color::White);

			float lastRot = _gameObjectManager->FindObjectByName("player")->GetTransform()->GetRotation();
			//	std::cout << _gameObjectManager->FindObjectByName("player")->GetTransform()->GetRotation() << std::endl;
			//_gameObjectManager->FindObjectByName("player")->GetTransform()->SetRotation(++lastRot);
			//	std::cout << _gameObjectManager->FindObjectByName("player")->GetTransform()->GetRotation() << std::endl;

			_inputManager->Update(&_mainWindow, _mainUser);
			_physicsEngine->Update();
			_gameObjectManager->Update(_gameTime.getElapsedTime().asSeconds());
			_gameObjectManager->Draw(&_mainWindow);


			_mainWindow.display();
			break;
		}

		default:
		{

		}
		break;
		}
	}
}

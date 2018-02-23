#include "PhiEngine.h"

using namespace std;
PhiEngine::GameState PhiEngine::_gameState;
PhiEngineAudio PhiEngine::_audioManager;
sf::RenderWindow PhiEngine::_mainWindow;

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
	_mainWindow.create({ 1024,769 }, "PhiEngine");
	if (!_mainWindow.isOpen())
		return false;


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
			if (m_event.type == sf::Event::KeyPressed
				|| m_event.type == sf::Event::MouseButtonPressed)
			{
				_audioManager.StopMusic();
				_gameState = Menu;
				break;
			}
		}

		
	}

	///
	///Game Logic Layer
	///
	switch (_gameState)
	{
	case Menu:
		break;
	case Paused:
		break;
	case Playing:
		break;
	}

	_mainWindow.clear();
	_mainWindow.display();
}

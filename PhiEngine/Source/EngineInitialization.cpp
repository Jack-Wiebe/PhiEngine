#include "EngineInitialization.h"

using namespace std;

bool IsOnlyInstance(LPCTSTR gameTitle)
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

bool CheckStorage(const DWORDLONG diskSpaceNeeded)
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

bool CheckMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded)
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



DWORD ReadCPUSpeed()
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

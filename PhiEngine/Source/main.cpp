#include "EngineInitialization.h"

using namespace std;

void main(int argc, char **argv)
{
	LPCTSTR Title = "PhiEngine";
	if (!IsOnlyInstance(Title))
	{
		//error
	}
	DWORDLONG SpaceNeeded = 300;
	if (!CheckStorage(SpaceNeeded))
	{
		//error
	}
	DWORDLONG RAMNeeded = 300;
	DWORDLONG VRAMNeeded = 300;
	if (!CheckMemory(RAMNeeded, VRAMNeeded))
	{
		//error
	}

	DWORD Success = ReadCPUSpeed();
	system("pause");
}
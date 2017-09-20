#include "EngineInitialization.h"

using namespace std;

void main(int argc, char **argv)
{
	LPCTSTR Title = "PhiEngine";
	if (!IsOnlyInstance(Title))
	{
		//error
	}
	DWORDLONG SpaceNeeded = 3000000000;
	if (!CheckStorage(SpaceNeeded))
	{
		//error
	}
	DWORDLONG RAMNeeded = 3000000000;
	DWORDLONG VRAMNeeded = 3000000000;
	if (!CheckMemory(RAMNeeded, VRAMNeeded))
	{
		//error
	}

	DWORD Success = ReadCPUSpeed();
	system("pause");
}
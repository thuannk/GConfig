// DVC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <Windows.h>
#include "NvidiaWrapper.h"

using namespace std;

// Get actual vibrance level from input percentage
int GetVibranceLevel(int Percentage)
{
	// Level: 0 - 63
	// Percentage: 50 - 100
	float rate = ((float)64) / 51;
	return (Percentage - 50) * rate;
}

int main(int argc, TCHAR* argv[])
{
	// Hide console windows
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	// Get percentage from parameter 1
	int iPercentage = 0;
	if (argc == 2)
	{
		iPercentage = _ttoi(argv[1]);
	}
	if (iPercentage < 50 || iPercentage > 100)
	{
		ShowWindow(GetConsoleWindow(), SW_SHOW);
		_tprintf_s("Invalid parameter. Inputed: %s\n", argv[1]);
		getchar();
		return -1;
	}

	// Get actual vibrance level
	int VibranceLevel = GetVibranceLevel(iPercentage);

	// Init NVAPI.dll
	NvidiaWrapper _nvidia;
	bool bRet = _nvidia.InitializeLibrary();
	if (bRet == false)
	{
		ShowWindow(GetConsoleWindow(), SW_SHOW);
		_tprintf_s("Initialize nvidia library error.\n");
		_nvidia.UnloadLibrary();
		getchar();
		return -1;
	}

	// Get default display handle
	int DefaultHandle = _nvidia.EnumerateNvidiaDisplayHandle(0);
	if (DefaultHandle == -1)
	{
		ShowWindow(GetConsoleWindow(), SW_SHOW);
		_tprintf_s("Enumerate display handle error.\n");
		_nvidia.UnloadLibrary();
		getchar();
		return -1;
	}

	// Get current vibrance level, if diff from input, set vibrance to new value
	NV_DISPLAY_DVC_INFO info;
	if (_nvidia.GetDVCInfo(&info, DefaultHandle) == true)
	{
		if (info.currentLevel != VibranceLevel)
		{
			bRet = _nvidia.SetDVCLevel(DefaultHandle, VibranceLevel);
			// Inform when fail
			if (bRet == false)
			{
				ShowWindow(GetConsoleWindow(), SW_SHOW);
				_tprintf_s("Digital Vibrance was not set due to an error.\n");
				_nvidia.UnloadLibrary();
				getchar();
				return -1;
			}
		}
	}

	// Unload library when done
	_nvidia.UnloadLibrary();

    return 0;
}


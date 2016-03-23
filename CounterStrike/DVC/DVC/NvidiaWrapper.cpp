#include "stdafx.h"
#include "NvidiaWrapper.h"
#include <Windows.h>

NvidiaWrapper::NvidiaWrapper()
{
}


NvidiaWrapper::~NvidiaWrapper()
{
}

bool NvidiaWrapper::InitializeLibrary()
{
	HMODULE hmod = LoadLibrary("nvapi.dll");
	if (hmod == NULL)
	{
		return false;
	}

	NvAPI_QueryInterface = (NvAPI_QueryInterface_t)GetProcAddress(hmod, "nvapi_QueryInterface");
	NvAPI_Initialize = (NvAPI_Initialize_t)(*NvAPI_QueryInterface)(0x0150E828);
	NvAPI_Unload = (NvAPI_Unload_t)(*NvAPI_QueryInterface)(0x0D22BDD7E);
	NvAPI_GetDVCInfo = (NvAPI_GetDVCInfo_t)(*NvAPI_QueryInterface)(0x4085DE45);
	NvAPI_SetDVCLevel = (NvAPI_SetDVCLevel_t)(*NvAPI_QueryInterface)(0x172409B4);
	NvAPI_EnumNvidiaDisplayHandle = (NvAPI_EnumNvidiaDisplayHandle_t)(*NvAPI_QueryInterface)(0x9ABDD40D);

	if (NvAPI_Initialize == NULL	|| NvAPI_Unload == NULL
									|| NvAPI_GetDVCInfo == NULL
									|| NvAPI_SetDVCLevel == NULL
									|| NvAPI_EnumNvidiaDisplayHandle == NULL)
	{
		return false;
	}

	int ret = (*NvAPI_Initialize)();
	if (ret == 0)
	{
		return true;
	}
	return false;
}

bool NvidiaWrapper::UnloadLibrary()
{
	int ret = (*NvAPI_Unload)();
	if (ret == 0)
		return true;
	return false;
}

int NvidiaWrapper::EnumerateNvidiaDisplayHandle(int index)
{
	int defaultHandle = 0;
	_NvAPI_Status status = (_NvAPI_Status)(*NvAPI_EnumNvidiaDisplayHandle)(index, &defaultHandle);
	if (status != 0 && status == NVAPI_END_ENUMERATION)
	{
		return -1;
	}
	return defaultHandle;
}

bool NvidiaWrapper::GetDVCInfo(NV_DISPLAY_DVC_INFO * info, int defaultHandle)
{
	info->version = sizeof(NV_DISPLAY_DVC_INFO) | 0x10000;
	_NvAPI_Status status = (_NvAPI_Status)(*NvAPI_GetDVCInfo)(defaultHandle, 0, info);
	if (status != NVAPI_OK)
	{
		return false;
	}
	return true;
}

bool NvidiaWrapper::SetDVCLevel(int defaultHandle, int level)
{
	_NvAPI_Status status = (_NvAPI_Status)(*NvAPI_SetDVCLevel)(defaultHandle, 0, level);
	if (status != NVAPI_OK)
	{
		return false;
	}
	return true;
}

#include "pch.h"
#include "jsrt.h"
#include "ChakraDbg.h"

using namespace ChakraDemoApp;

_Check_return_ WINOLEAPI CoGetClassObject(	_In_ REFCLSID rclsid,
											_In_ DWORD dwClsContext,
											_In_opt_ LPVOID pvReserved,
											_In_ REFIID riid,
											_Outptr_ LPVOID FAR * ppv
											);

void ChakraDbg::EnableDebugging()
{
	HRESULT hr;

	IClassFactory *classFactory = nullptr;
	IProcessDebugManager *pdm = nullptr;
	IDebugApplication *debugApplication = nullptr;

	hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
	assert(SUCCEEDED(hr));

	hr = CoGetClassObject(__uuidof(ProcessDebugManager), CLSCTX_INPROC_SERVER, NULL, __uuidof(IClassFactory), (LPVOID *)&classFactory);
	assert(SUCCEEDED(hr)); 
	
	hr = classFactory->CreateInstance(0, _uuidof(IProcessDebugManager), (LPVOID *)&pdm);
	assert(SUCCEEDED(hr));

	hr = pdm->GetDefaultApplication(&debugApplication);
	assert(SUCCEEDED(hr));

	JsErrorCode err;
	err = JsStartDebugging(debugApplication);
	assert(JsNoError == err);

	debugApplication->Release();
	pdm->Release();
	classFactory->Release();
}
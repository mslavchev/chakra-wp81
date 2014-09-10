#include "pch.h"
#include "Chakra.h"
#include "ChakraDbg.h"
#include <fstream>
#include <iostream>

using namespace ChakraDemoApp;
using namespace Platform;

Chakra::Chakra()
{
	JsErrorCode err;

	err = JsCreateRuntime(JsRuntimeAttributeNone, JsRuntimeVersion11, nullptr, &m_runtime);
	assert(JsNoError == err);

	err = JsCreateContext(m_runtime, nullptr, &m_context);
	assert(JsNoError == err);

	err = JsSetCurrentContext(m_context);
	assert(JsNoError == err);

	ChakraDbg::EnableDebugging();
}


String^ Chakra::GetGreeting()
{
	JsErrorCode err;

	std::wifstream in(L"app.js");
	assert(in);

	std::wstring script((std::istreambuf_iterator<wchar_t>(in)), std::istreambuf_iterator<wchar_t>());
	JsValueRef result;
	JsSourceContext contextCookie = 0;

	err = JsRunScript(script.c_str(), contextCookie, L"app.js", &result);
	assert(JsNoError == err);

	const wchar_t *pStr;
	size_t len;
	
	err = JsStringToPointer(result, &pStr, &len);
	assert(JsNoError == err);

	return ref new String(pStr, len);
}


Chakra::~Chakra()
{
	JsErrorCode err;

	err = JsSetCurrentContext(JS_INVALID_REFERENCE);
	assert(JsNoError == err);

	err = JsDisposeRuntime(m_runtime);
	assert(JsNoError == err);
}

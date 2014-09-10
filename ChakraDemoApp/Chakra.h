
#include "jsrt.h"

namespace ChakraDemoApp
{
	class Chakra
	{
	public:
		Chakra();

		Platform::String^ GetGreeting();

		~Chakra();

	private:
		JsRuntimeHandle m_runtime;
		JsContextRef m_context;
	};
}
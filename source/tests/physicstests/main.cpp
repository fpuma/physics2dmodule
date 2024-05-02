#include <precompiledphysics.h>
#include <precompiledapplication.h>

#include <graphics/commondefinitions.h>
#include <graphics/iapplication.h>
#include <graphics/irenderer.h>

#include <chrono>
#include <thread>

#include "libtest.h"

//#define PROCESS_MULTI_PARAMS_STRING(FORMAT_VAR,STRING_NAME) 	va_list args;\
//	va_start(args, FORMAT_VAR); \
//	int length = _vscprintf(FORMAT_VAR, args) + 1; \
//	char* buffer = new char[length]; \
//	vsprintf_s(buffer, length, FORMAT_VAR, args); \
//	STRING_NAME = std::string(buffer); \
//	delete[] buffer; \
//	va_end(args);

int main( int argc, char* argv[] )
{
	auto graphicsPtr = puma::app::IApplication::create();
	
	puma::app::Extent wExtent = { 1000,1000, 100, 100 };
	graphicsPtr->init();
	graphicsPtr->createWindow( wExtent, "PhysicsTests" );

	//========================================================================

	std::unique_ptr<LibTest> libTest = std::make_unique<LibTest>();

	libTest->init( graphicsPtr.get() );

	while (!graphicsPtr->shouldQuit())
	{
        graphicsPtr->update();
		libTest->update();
        puma::app::IRenderer* renderer = graphicsPtr->getDefaultRenderer();
		
		renderer->beginRender();
		libTest->render();
        renderer->endRender();

        std::this_thread::sleep_for( std::chrono::milliseconds( 16 ) );
	}
	
	return 0;
}
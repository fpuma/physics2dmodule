#include <precompiledpt.h>
#include <graphics/graphicdefinitions.h>
#include <graphics/igraphics.h>
#include <graphics/irenderer.h>

#include <box2dtests.h>
#include <libtest.h>

#include <SDL2_gfxPrimitives.h>

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

	auto graphicsPtr = puma::gfx::IGraphics::create();
	
	
	puma::gfx::Extent wExtent = { 1000,1000, 100, 100 };
	graphicsPtr->init( wExtent, "PhysicsTests" );

	//========================================================================

	std::unique_ptr<LibTest> libTest = std::make_unique<LibTest>();
	std::unique_ptr <Test1>  box2dTest = std::make_unique<Test1>();;

	libTest->init( graphicsPtr.get() );
	box2dTest->init( graphicsPtr.get() );

	while (!graphicsPtr->shouldQuit())
	{
        graphicsPtr->update();
		libTest->update();
		box2dTest->update();
        puma::gfx::IRenderer* renderer = graphicsPtr->getRenderer();
		
		renderer->beginRender();
		libTest->render();
		box2dTest->render();
        renderer->endRender();

        std::this_thread::sleep_for( std::chrono::milliseconds( 16 ) );
	}
	
	return 0;
}
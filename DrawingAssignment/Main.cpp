#include <Windows.h>
#include <crtdbg.h>
#include "GraphicsTool.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	//_CrtSetBreakAlloc(204);
	_onexit(_CrtDumpMemoryLeaks);
#endif

	GraphicsTool gt(hInstance);

	return 0;
}
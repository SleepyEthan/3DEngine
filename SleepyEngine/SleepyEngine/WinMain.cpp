#include "Window.h"
#include "App.h"

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR	  lpCmdLine,
	int		  nCmdShow )
{
	try
	{
		return App{}.Go();
	}
	catch ( const SleepyException& e )
	{
		MessageBox( nullptr,e.what(),e.GetType(),MB_OK | MB_ICONEXCLAMATION );
	}
	catch ( std::exception& e )
	{
		MessageBox( nullptr,e.what(),"Standard Exception",MB_OK | MB_ICONEXCLAMATION );
	}
	catch ( ... )
	{
		MessageBox( nullptr,"No details available","Unknown Exception",MB_OK | MB_ICONEXCLAMATION );
	}
	return -1;
}

#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>

#include "Engine.h"

void InitGameplay() {

}

INT WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ PSTR, _In_ INT) {
	buki::Engine theEngine;
	if (theEngine.Init("Bart Attacks Buki", 800, 600)) {
		InitGameplay();
		theEngine.Start();
	}
	return 0;
}

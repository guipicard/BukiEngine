#include "SdlInput.h"
#include <SDL.h>

void SdlInput::Update()
{
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}

bool SdlInput::IsKeyDown(buki::EKey _keycode)
{
	return m_KeyStates[static_cast<int>(_keycode)] == 1;
}

bool SdlInput::IsButtonDown(int button)
{
	return false;
}

void SdlInput::GetMousePosition(int* x, int* y)
{
}

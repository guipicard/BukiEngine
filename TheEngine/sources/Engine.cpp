#include "Engine.h"
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include <windows.h>
#include <vld.h>

// Carrer is never used ... it's more of an emotional thing. I am attached to that class and one day it will do great things!
class Carrer {
	Carrer() {
		y = x = 0;
		h = w = 100;
	};
public:
	int x;
	int y;
	int w;
	int h;
};

bool buki::Engine::Init(const std::string& title, int w, int h)
{
	AllocConsole();
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log(SDL_GetError());
		return false;
	}

	int _x = SDL_WINDOWPOS_CENTERED;
	int _y = SDL_WINDOWPOS_CENTERED;

	// Inputs
	m_Input = new SdlInput();

	// Window can be minimize and reshaped
	Uint32 _flag = SDL_WINDOW_TOOLTIP | SDL_WINDOW_RESIZABLE;

	m_Window = SDL_CreateWindow(title.c_str(), _x, _y, w, h, _flag);
	if (!m_Window) {
		SDL_Log(SDL_GetError());
		return false;
	}

	// Gpu Handling
	_flag = SDL_RENDERER_ACCELERATED;
	m_Renderer = SDL_CreateRenderer(m_Window, -1, _flag);
	if (!m_Renderer) {
		SDL_Log(SDL_GetError());
		return false;
	}
	m_IsInit = true;
	return true;
}


void buki::Engine::Start() {
	if (!m_IsInit) {
		if (!Init("Unknown title", 800, 600)) {
			return;
		}
	}
	const float MS_PER_FRAME = 16.0f; // 16 to get 60 fps
	m_IsRunning = true;
	float _end = clock();
	float _lag = 0.0f;
	float _elapsed = 0.0f;
	while (m_IsRunning) {
		const double _start = clock();
		_elapsed = (_start - _end);
		float _dt = _elapsed * 0.001f;
		_end = _start;
		_lag += _elapsed;
		ProcessInput();

		while (_lag >= MS_PER_FRAME)
		{
			Update(_dt);
			_lag -= MS_PER_FRAME;
		}
		float sleepTime = _start + MS_PER_FRAME - clock();
		if (sleepTime >= 0)
		{
			Sleep(sleepTime);
		}
		Render();
	}
	Shutdown();
}

void buki::Engine::Exit()
{
	Shutdown();
}

void buki::Engine::ProcessInput()
{

	SDL_Event _event;
	while (SDL_PollEvent(&_event)) {
		if (_event.type == SDL_QUIT)
		{
			Shutdown();
			return;
		}
	}

	if (m_Input != nullptr) 
	{
		m_Input->Update();
	}



}

static float x = 0;
static float y = 0;
void buki::Engine::Update(float dt)
{

	if (m_Input == nullptr) return;

	const unsigned char* _keystates = SDL_GetKeyboardState(nullptr);
	if (m_Input->IsKeyDown(EKey::EKEY_UP)) {
		y -= 100 * dt;
	}
	if (m_Input->IsKeyDown(EKey::EKEY_LEFT)) {
		x -= 100 * dt;
	}
	if (m_Input->IsKeyDown(EKey::EKEY_DOWN)) {
		y += 100 * dt;
	}
	if (m_Input->IsKeyDown(EKey::EKEY_RIGHT)) {
		x += 100 * dt;
	}


}

void buki::Engine::Render()
{
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_Renderer);
	SDL_SetRenderDrawColor(m_Renderer, 255, 0, 0, 255);
	SDL_Rect get_rekt = { 0 };
	get_rekt.x = 100 + x;
	get_rekt.y = 100 + y;
	get_rekt.w = 100;
	get_rekt.h = 100;
	SDL_RenderFillRect(m_Renderer, &get_rekt);

	SDL_RenderPresent(m_Renderer);
}

void buki::Engine::Shutdown()
{
	if (m_Input != nullptr) {
		delete m_Input;
		m_Input = nullptr;
	}

	SDL_DestroyRenderer(m_Renderer);
	m_Renderer = nullptr;

	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;

	FreeConsole();

	SDL_Quit();
	m_IsInit = m_IsRunning = false;
}

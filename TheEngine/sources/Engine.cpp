#include "Engine.h"
#include <SDL.h>
#include <time.h>
#include <windows.h>

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
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log(SDL_GetError());
		return false;
	}

	int _x = SDL_WINDOWPOS_CENTERED;
	int _y = SDL_WINDOWPOS_CENTERED;

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
		switch (_event.type) {
		case SDL_QUIT: // exit ti desktop button or top right x to close window
			Exit();
			break;
		case SDL_MOUSEBUTTONDOWN:
			SDL_MouseButtonEvent _buttonDown = _event.button;
			SDL_Log("Button down : %d)", _buttonDown.button);
			SDL_Log("at (%d, %d)", _buttonDown.x, _buttonDown.y);
			break;
		case SDL_MOUSEBUTTONUP:
			SDL_MouseButtonEvent _buttonUp = _event.button;
			SDL_Log("Button up : %d", _buttonUp.button);
			SDL_Log("at (%d, %d)", _buttonUp.x, _buttonUp.y);
			break;
		case SDL_MOUSEMOTION:
			SDL_MouseMotionEvent _motion = _event.motion;
			SDL_Log("%d, %d", _motion.x, _motion.y);
			break;

		}
	}
}

static float x = 0;
static float y = 0;
void buki::Engine::Update(float dt)
{
	const unsigned char* _keyStates = SDL_GetKeyboardState(nullptr); // reset key events
	if (_keyStates[SDL_SCANCODE_W]) {
		y -= 100 * dt;
	}
	if (_keyStates[SDL_SCANCODE_A]) {
		x -= 100 * dt;
	}
	if (_keyStates[SDL_SCANCODE_S]) {
		y += 100 * dt;
	}
	if (_keyStates[SDL_SCANCODE_D]) {
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
	SDL_DestroyRenderer(m_Renderer);
	m_Renderer = nullptr;

	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;

	SDL_Quit();
	m_IsRunning = false;
}

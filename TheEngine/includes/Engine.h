#pragma once
#include "SdlInput.h"
#include <string>

struct SDL_Window;
struct SDL_Renderer;
namespace buki {
	class Engine final {
	public:
		bool Init(const std::string& title, int w, int d);
		void Start();
		void Exit();
	public:
		IInput& Input() const { return *m_Input; }
	private:

		void ProcessInput();
		void Update(float dt);
		void Render();
		void Shutdown();
	private:
		IInput* m_Input = nullptr;

		bool m_IsRunning = false;
		bool m_IsInit = false;
		SDL_Window* m_Window = nullptr;
		SDL_Renderer* m_Renderer = nullptr;
	};
}


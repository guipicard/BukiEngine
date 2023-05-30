#pragma once
#include <cstdlib>
#include <functional>
#include <string>

class IGraphics
{
public:
	IGraphics(int _x, int _y, int _w, int _h);
	virtual void LoadTexture(std::string _path) = 0;
	virtual void Draw() = 0;
private:
	const size_t _textureId;

	int m_X;
	int m_Y;
	int m_W;
	int m_H;
};


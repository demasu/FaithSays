#pragma once
#include "olcPixelGameEngine.h"
#include "FaithRenderer.h"

class InputHandler
{
public:
	InputHandler();

	FaithRenderer::FaithState HandleInput(olc::PixelGameEngine* pge);
};


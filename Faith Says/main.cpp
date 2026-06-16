#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "FaithRenderer.h"
#include "InputHandler.h"

// Override base class with your custom functionality
class FaithSays : public olc::PixelGameEngine
{
private:
	FaithRenderer renderer;
	InputHandler inputHandler;

public:
	FaithSays() : renderer(FaithRenderer::FaithState::NONE)
	{
		// Name your application
		sAppName = "Faith Says";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		renderer.LoadFaithSprites();
		renderer.LoadUISprites();
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLACK);
		// Update game state
		renderer.Update(fElapsedTime);

		// Get input
		FaithRenderer::FaithState newState = inputHandler.HandleInput(this);
		if (newState != FaithRenderer::FaithState::NONE) {
			renderer.TriggerAnimation(newState, 0.5f);
		}

		// Render
		renderer.DrawFaith(this);
		renderer.DrawUI(this);

		return true;
	}
};

int main()
{
	FaithSays game;
	if (game.Construct(512, 500, 1, 1))
		game.Start();
	return 0;
}
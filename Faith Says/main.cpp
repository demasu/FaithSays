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

	GameState currentGameState = GameState::MAIN_MENU;
	MenuItem highlightedMenuItem = MenuItem::START;

	float totalElapsedTime = 0.0f;
public:
	FaithSays() : renderer(FaithState::NONE)
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
		totalElapsedTime += fElapsedTime;
		FaithState newState = FaithState::NONE;
		// Clear stays out of the state selection because we always want to clear the screen
		Clear(olc::BLACK);
		switch (currentGameState) {
		case GameState::MAIN_MENU:
			inputHandler.Update(this, currentGameState, highlightedMenuItem);
			renderer.DrawMenu(this, highlightedMenuItem, totalElapsedTime);
			break;
		case GameState::PLAYING:
			// Check here if the player hits escape so it's easier to quit
			if (GetKey(olc::Key::ESCAPE).bPressed) {
				currentGameState = GameState::MAIN_MENU;
				return true;
			}
			// Update game state
			renderer.Update(fElapsedTime);

			// Get input
			newState = inputHandler.HandlePlayingInput(this);
			if (newState != FaithState::NONE) {
				renderer.TriggerAnimation(newState, 0.5f);
			}

			// Render
			renderer.DrawFaith(this);
			renderer.DrawUI(this);
			break;
		case GameState::PAUSED:

			break;
		case GameState::DISPLAY_CREDITS:
			break;
		case GameState::QUITTING:
			return false;
		}


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
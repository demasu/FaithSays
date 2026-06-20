#pragma once
#include "olcPixelGameEngine.h"
#include "InputHandler.h"
#include "Types.h"

class FaithRenderer {
public:
	//*********************************
	//* Functions for loading sprites *
	//*********************************
	void LoadFaithSprites();
	void LoadUISprites();
	
	//******************************************
	//* Functions for rendering the main Faith *
	//******************************************
	FaithRenderer(FaithState initialState = FaithState::NONE);

	void Update(float fElapsedTime);
	void TriggerAnimation(FaithState newState, float duration = 0.5f);
	void DrawFaith(olc::PixelGameEngine* pge);

	//**********************************
	//* Functions for rendering the UI *
	//**********************************
	void DrawUI(olc::PixelGameEngine* pge);
	void DrawMenu(olc::PixelGameEngine* pge, MainMenuItem highlightedMenuItem, int highScore, float totalElapsedTime);
	void DrawCreditsScreen(olc::PixelGameEngine* pge);
	void DrawGameOverScreen(olc::PixelGameEngine* pge);
	void DrawHighScore(olc::PixelGameEngine* pge, int highScore);
	void DrawHighScoreMainMenu(olc::PixelGameEngine* pge, int highScore);
	void DrawScore(olc::PixelGameEngine* pge, int currentScore);

	//*********************************
	//* Useful functions for everyone *
	//*********************************
	void DrawStringCentered(olc::PixelGameEngine* pge, int y, const std::string& text, olc::Pixel color = olc::WHITE, uint32_t scale = 1);
	void Reset();

private:
	//*********************************************
	//* Variables for Faith's state and animation *
	//*********************************************
	FaithState currentState = NONE;
	float animationTimer = 0.0f;                  // Time the current animation state has been active in seconds
	float animationDuration = 0.5f;               // Duration of each animation state in seconds
	
	//***********************************************
	//* Variables for Faith's sprites and rendering *
	//***********************************************
	int spriteWidth = 128;						  // Width of each sprite in pixels
	std::unique_ptr<olc::Sprite> faithNeutral;    // Sprite for Faith's face
	std::unique_ptr<olc::Sprite> faithMouthLeft;  // Sprite for Faith's mouth left
	std::unique_ptr<olc::Sprite> faithMouthRight; // Sprite for Faith's mouth right
	std::unique_ptr<olc::Sprite> faithPawLeft;    // Sprite for Faith's paw left
	std::unique_ptr<olc::Sprite> faithPawRight;   // Sprite for Faith's paw right

	//******************************
	//* Variables for UI rendering *
	//******************************
	std::unique_ptr<olc::Sprite> uiInputLeft;
	std::unique_ptr<olc::Sprite> uiInputRight;
	std::unique_ptr<olc::Sprite> uiInputUp;
	std::unique_ptr<olc::Sprite> uiInputDown;
	std::unique_ptr<olc::Sprite> uiInputLeftPressed;
	std::unique_ptr<olc::Sprite> uiInputRightPressed;
	std::unique_ptr<olc::Sprite> uiInputUpPressed;
	std::unique_ptr<olc::Sprite> uiInputDownPressed;
	std::unique_ptr<olc::Sprite> uiMenuCursor;
};


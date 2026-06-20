#pragma once
#include "olcPixelGameEngine.h"
#include "Types.h"

class InputHandler
{
public:
	InputHandler();

	void Update(olc::PixelGameEngine* pge, GameState& currentState, MainMenuItem& highlightedMenuItem);
	MenuAction GetMenuAction() const { return currentMenuAction; };
	FaithState GetFaithAction() const { return currentFaithAction; };
	FaithState HandlePlayingInput(olc::PixelGameEngine* pge);
	MenuAction HandleMenuInput(olc::PixelGameEngine* pge);
	void HandleGameOverInput(olc::PixelGameEngine* pge, GameState& currentGameState);
	void HandleCreditsInput(olc::PixelGameEngine* pge, GameState& currentGameState);

	bool LeftPressed(olc::PixelGameEngine* pge);
	bool UpPressed(olc::PixelGameEngine* pge);
	bool RightPressed(olc::PixelGameEngine* pge);
	bool DownPressed(olc::PixelGameEngine* pge);
	bool SelectPressed(olc::PixelGameEngine* pge);
	bool EscapePressed(olc::PixelGameEngine* pge);

private:
	MenuAction currentMenuAction = MenuAction::NONE;
	FaithState currentFaithAction = FaithState::NONE;

};


#include "InputHandler.h"

InputHandler::InputHandler() {}

FaithState InputHandler::HandlePlayingInput(olc::PixelGameEngine* pge)
{
	FaithState none       = FaithState::NONE;
	FaithState mouthLeft  = FaithState::MOUTH_LEFT;
	FaithState mouthRight = FaithState::MOUTH_RIGHT;
	FaithState pawLeft    = FaithState::PAW_LEFT;
	FaithState pawRight   = FaithState::PAW_RIGHT;

	bool LEFT_PRESSED   = LeftPressed(pge);
	bool RIGHT_PRESSED  = RightPressed(pge);
	bool DOWN_PRESSED   = DownPressed(pge);
	bool UP_PRESSED     = UpPressed(pge);
	bool SELECT_PRESSED = SelectPressed(pge);

	if (LEFT_PRESSED) {
		return mouthLeft;
	}

	if (RIGHT_PRESSED) {
		return mouthRight;
	}
	
	if (UP_PRESSED) {
		return pawLeft;
	}
	
	if (DOWN_PRESSED) {
		return pawRight;
	}

	// Default state
	return none;
}

MenuAction InputHandler::HandleMenuInput(olc::PixelGameEngine* pge) {
	bool UP_PRESSED     = UpPressed(pge);
	bool DOWN_PRESSED   = DownPressed(pge);
	bool SELECT_PRESSED = SelectPressed(pge);

	if (UP_PRESSED) {
		return MenuAction::UP;
	}

	if (DOWN_PRESSED) {
		return MenuAction::DOWN;
	}

	if (SELECT_PRESSED) {
		return MenuAction::SELECT;
	}

	return MenuAction::NONE;
}

void InputHandler::HandleCreditsInput(olc::PixelGameEngine* pge, GameState& currentGameState) {
	bool SELECT_PRESSED = SelectPressed(pge);
	bool ESCAPE_PRESSED = EscapePressed(pge);

	// Only end the credits when the user hits the select button
	if (SELECT_PRESSED || ESCAPE_PRESSED) {
		currentGameState = GameState::MAIN_MENU;
	}
}

void InputHandler::HandleGameOverInput(olc::PixelGameEngine* pge, GameState& currentGameState) {
	bool SELECT_PRESSED = SelectPressed(pge);
	bool ESCAPE_PRESSED = EscapePressed(pge);

	if (SELECT_PRESSED) {
		currentGameState = GameState::MAIN_MENU;
	}

	if (ESCAPE_PRESSED) {
		currentGameState = GameState::QUITTING;
	}
}

void InputHandler::Update(olc::PixelGameEngine* pge, GameState& currentState, MainMenuItem& highlightedMenuItem) {
	currentMenuAction = MenuAction::NONE;
	currentFaithAction = FaithState::NONE;
	MenuAction requestedMenuAction = MenuAction::NONE;

	switch (currentState) {
	case GameState::MAIN_MENU:
		requestedMenuAction = HandleMenuInput(pge);
		if (requestedMenuAction == MenuAction::UP) {
			int previousItem = static_cast<int>(highlightedMenuItem) - 1;
			if (previousItem < 0) {
				previousItem = static_cast<int>(MainMenuItem::COUNT) - 1;
			}
			highlightedMenuItem = static_cast<MainMenuItem>(previousItem);
		}

		if (requestedMenuAction == MenuAction::DOWN) {
			int nextItem = static_cast<int>(highlightedMenuItem) + 1;
			if (nextItem >= static_cast<int>(MainMenuItem::COUNT)) {
				nextItem = 0;
			}
			highlightedMenuItem = static_cast<MainMenuItem>(nextItem);
		}

		if (requestedMenuAction == MenuAction::SELECT) {
			switch (highlightedMenuItem) {
			case MainMenuItem::START:
				currentState = GameState::PLAYING;
				break;
			case MainMenuItem::CREDITS:
				currentState = GameState::DISPLAY_CREDITS;
				break;
			case MainMenuItem::QUIT:
				currentState = GameState::QUITTING;
				break;
			default:
				break;
			}
		}
		break;
	case GameState::PLAYING:
		HandlePlayingInput(pge);
		break;
	case GameState::DISPLAY_CREDITS:
		HandleCreditsInput(pge, currentState);
		break;
	case GameState::GAME_OVER:
		HandleGameOverInput(pge, currentState);
		break;
	}
}

bool InputHandler::LeftPressed(olc::PixelGameEngine* pge) {
	if (pge->GetKey(olc::Key::LEFT).bPressed) {
		return true;
	}
	else if (pge->GetKey(olc::Key::A).bPressed) {
		return true;
	}
	else if (pge->GetKey(olc::Key::NP4).bPressed) {
		return true;
	}

	return false;
}

bool InputHandler::RightPressed(olc::PixelGameEngine* pge) {
	if (pge->GetKey(olc::Key::RIGHT).bPressed) {
		return true;
	}
	else if (pge->GetKey(olc::Key::D).bPressed) {
		return true;
	}
	else if (pge->GetKey(olc::Key::NP6).bPressed) {
		return true;
	}

	return false;
}

bool InputHandler::UpPressed(olc::PixelGameEngine* pge) {
	if (pge->GetKey(olc::Key::UP).bPressed) {
		return true;
	}
	else if (pge->GetKey(olc::Key::W).bPressed) {
		return true;
	}
	else if (pge->GetKey(olc::Key::NP8).bPressed) {
		return true;
	}

	return false;
}

bool InputHandler::DownPressed(olc::PixelGameEngine* pge) {
	if (pge->GetKey(olc::Key::DOWN).bPressed) {
		return true;
	}
	else if (pge->GetKey(olc::Key::S).bPressed) {
		return true;
	}
	else if (pge->GetKey(olc::Key::NP2).bPressed) {
		return true;
	}

	return false;
}

bool InputHandler::SelectPressed(olc::PixelGameEngine* pge) {
	if (pge->GetKey(olc::Key::ENTER).bPressed) {
		return true;
	}

	return false;
}

bool InputHandler::EscapePressed(olc::PixelGameEngine* pge) {
	if (pge->GetKey(olc::Key::ESCAPE).bPressed) {
		return true;
	}

	return false;
}
#pragma once

//***************************************************************
//* A single header that contains the enums and other things we *
//* might want to know about in other classes/files             *
//***************************************************************

enum class GameState {
	MAIN_MENU,
	PLAYING,
	PAUSED,
	DISPLAY_CREDITS,
	GAME_OVER,
	QUITTING
};

enum FaithState {
	NONE,
	MOUTH_LEFT,
	MOUTH_RIGHT,
	PAW_LEFT,
	PAW_RIGHT
};

enum class MenuAction {
	NONE,
	UP,
	DOWN,
	SELECT
};

enum class MenuItem {
	START,
	CREDITS,
	QUIT,
	COUNT
};
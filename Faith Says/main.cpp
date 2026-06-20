#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "FaithRenderer.h"
#include "InputHandler.h"
#include "Types.h"
#include <vector>
#include <random>

#include <iostream>

// Override base class with your custom functionality
class FaithSays : public olc::PixelGameEngine
{
private:
	FaithRenderer renderer;
	InputHandler inputHandler;

	GameState currentGameState = GameState::MAIN_MENU;
	MainMenuItem highlightedMenuItem = MainMenuItem::START;

	float totalElapsedTime = 0.0f;

	RoundPhase currentPhase = RoundPhase::INIT_ROUND;
	std::vector<FaithState> gameSequence;
	size_t playbackIndex = 0;
	size_t playerIndex = 0;
	float playbackTimer = 0.0f;
	float timeBetweenMoves = 0.6f;
	float delayTimer = 0.0f;
	float delayDuration = 0.8f; // Delay before playback starts

	bool firstRound = true;

	int currentScore = 0;
	int highScore = 0;

	std::mt19937 prng;

public:
	FaithSays() : renderer(FaithState::NONE)
	{
		// Name your application
		sAppName = "Faith Says";
	}

public:
	bool OnUserCreate() override
	{
		// Get a better random number generator started
		std::random_device rd;
		prng.seed(rd());
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
			HandleMainMenuLoop();
			break;
		case GameState::PLAYING:
			if (inputHandler.EscapePressed(this)) {
				// Immediately go to the main menu if the user hits escape
				currentGameState = GameState::MAIN_MENU;
				resetState();
				return true;
			}
			HandleGameplayLoop(fElapsedTime, newState);
			break;
		case GameState::PAUSED:
			break;
		case GameState::DISPLAY_CREDITS:
			HandleCreditsLoop();
			break;
		case GameState::GAME_OVER:
			resetState();
			HandleGameOverLoop();
			break;
		case GameState::QUITTING:
			return false;
		}


		return true;
	}

private:
	//***********************************************************
	//* Internal functions to make reading the game loop easier *
	//***********************************************************

	void resetState() {
		highlightedMenuItem = MainMenuItem::START;
		currentPhase = RoundPhase::INIT_ROUND;
		playbackIndex = 0;
		playbackTimer = 0.0f;
		delayTimer = 0.0f;
		firstRound = true;
		currentScore = 0;
		gameSequence.erase(gameSequence.begin(), gameSequence.end());
		renderer.Reset();
	}

	void HandleMainMenuLoop() {
		inputHandler.Update(this, currentGameState, highlightedMenuItem);
		renderer.DrawMenu(this, highlightedMenuItem, highScore, totalElapsedTime);
	}

	void HandleCreditsLoop() {
		inputHandler.Update(this, currentGameState, highlightedMenuItem);
		renderer.DrawCreditsScreen(this);
	}

	void HandleGameOverLoop() {

		inputHandler.Update(this, currentGameState, highlightedMenuItem);
		renderer.DrawGameOverScreen(this);
	}

	void HandleGameplayLoop(float fElapsedTime, FaithState& newState) {
		// We need to update the state every frame regardless of the actual RoundPhase
		renderer.Update(fElapsedTime);

		// Check the current phase and call the right thing based on that
		switch (currentPhase) {
		case RoundPhase::INIT_ROUND:
			GenerateNextMove();
			break;
		case RoundPhase::ROUND_DELAY:
			DelayRound(fElapsedTime);
			break;
		case RoundPhase::PLAYBACK:
			PlaybackSequence(fElapsedTime);
			break;
		case RoundPhase::PLAYER_TURN:
			ProcessPlayerTurn(newState);
			break;
		}

		// Render what's happened
		renderer.DrawFaith(this);
		renderer.DrawUI(this);
		renderer.DrawScore(this, currentScore);
		renderer.DrawHighScore(this, highScore);
	}

	void GenerateNextMove() {
		// Pick a new move from 1-4 since there's only 4 moves and the
		// first in the enum is NONE, so we do want 1-4 and not 0-3
		std::uniform_int_distribution<int> dist(1, 4);
		FaithState newMove = static_cast<FaithState>(dist(prng));
		gameSequence.push_back(newMove);

		playbackIndex = 0;
		playbackTimer = 0.0f;
		delayTimer = 0.0f;

		currentPhase = RoundPhase::ROUND_DELAY;
	}

	void ProcessPlayerTurn(FaithState& newState) {
		newState = inputHandler.HandlePlayingInput(this);
		if (newState != FaithState::NONE) {
			renderer.TriggerAnimation(newState, 0.5f);

			// Check if the player selected the correct input
			if (newState == gameSequence[playerIndex]) {
				playerIndex++;

				// Check if the player has hit the end of the sequence
				if (playerIndex == gameSequence.size()) {
					currentScore++;
					if (currentScore > highScore) {
						highScore = currentScore;
					}
					currentPhase = RoundPhase::INIT_ROUND;
				}
			}
			else {
				// Player hit the wrong button
				currentGameState = GameState::GAME_OVER;
			}
		}
	}

	void PlaybackSequence(float fElapsedTime) {
		playbackTimer += fElapsedTime;

		renderer.DrawStringCentered(this, (ScreenHeight() / 2) - (8 * 5), "Faith's turn", olc::WHITE, 5);
		if (playbackTimer >= timeBetweenMoves) {
			// Reset the timer fully instead of subtracting so each new
			// animation always gets at least the full playback time
			playbackTimer = 0.0f;

			if (playbackIndex < gameSequence.size()) {
				renderer.TriggerAnimation(gameSequence[playbackIndex], 0.5f);
				playbackIndex++;
			}
			else {
				playbackIndex = 0;
				playerIndex = 0;
				currentPhase = RoundPhase::PLAYER_TURN;
			}
		}
	}

	void DelayRound(float fElapsedTime) {
		delayTimer += fElapsedTime;

		if (firstRound) {
			renderer.DrawStringCentered(this, (ScreenHeight() / 2) - (8 * 5), "GET READY!", olc::WHITE, 5);
		}

		if (delayTimer >= delayDuration) {
			currentPhase = RoundPhase::PLAYBACK;

			if (firstRound) {
				firstRound = false;
			}
		}
	}
};

int main() {
	FaithSays game;
	if (game.Construct(512, 500, 1, 1))
		game.Start();
	return 0;
}
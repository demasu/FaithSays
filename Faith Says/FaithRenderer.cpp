#include "FaithRenderer.h"
#include <array>

FaithRenderer::FaithRenderer(FaithState initialState) : currentState(initialState), animationTimer(0.0f), animationDuration(0.5f) {
}

void FaithRenderer::LoadFaithSprites() {
	// Load sprites for Faith's face and actions
	faithNeutral = std::make_unique<olc::Sprite>("sprites/faith_head.png");
	faithMouthLeft = std::make_unique<olc::Sprite>("sprites/faith_head_left.png");
	faithMouthRight = std::make_unique<olc::Sprite>("sprites/faith_head_right.png");
	faithPawLeft = std::make_unique<olc::Sprite>("sprites/faith_paw_left.png");
	faithPawRight = std::make_unique<olc::Sprite>("sprites/faith_paw_right.png");
}

void FaithRenderer::LoadUISprites() {
	uiInputLeft = std::make_unique<olc::Sprite>("sprites/button_mouth_left_new.png");
	uiInputRight = std::make_unique<olc::Sprite>("sprites/button_mouth_right_new.png");
	uiInputUp = std::make_unique<olc::Sprite>("sprites/button_paw_left_new.png");
	uiInputDown = std::make_unique<olc::Sprite>("sprites/button_paw_right_new.png");
	uiInputLeftPressed = std::make_unique<olc::Sprite>("sprites/button_mouth_left_new_pressed.png");
	uiInputRightPressed = std::make_unique<olc::Sprite>("sprites/button_mouth_right_new_pressed.png");
	uiInputUpPressed = std::make_unique<olc::Sprite>("sprites/button_paw_left_new_pressed.png");
	uiInputDownPressed = std::make_unique<olc::Sprite>("sprites/button_paw_right_new_pressed.png");
	uiMenuCursor = std::make_unique<olc::Sprite>("sprites/cursor.png");
}

void FaithRenderer::InitAudio() {
	audioEngine.InitialiseAudio();

	soundMouthLeft = std::make_unique<olc::sound::Wave>("sounds/meow_left.wav");
	soundMouthRight = std::make_unique<olc::sound::Wave>("sounds/meow_right.wav");
	soundPawLeft = std::make_unique<olc::sound::Wave>("sounds/paw_left.wav");
	soundPawRight = std::make_unique<olc::sound::Wave>("sounds/paw_right.wav");
}

void FaithRenderer::TriggerAnimation(FaithState actionState, float duration) {
	currentState = actionState;
	animationTimer = 0.0f;
	animationDuration = duration;

	// Audio time!
	switch (currentState) {
	case FaithState::MOUTH_LEFT:
		audioEngine.PlayWaveform(soundMouthLeft.get());
		break;
	case FaithState::MOUTH_RIGHT:
		audioEngine.PlayWaveform(soundMouthRight.get());
		break;
	case FaithState::PAW_LEFT:
		audioEngine.PlayWaveform(soundPawLeft.get());
		break;
	case FaithState::PAW_RIGHT:
		audioEngine.PlayWaveform(soundPawRight.get());
		break;
	}
}

void FaithRenderer::Update(float fElapsedTime) {
	if (currentState != FaithState::NONE) {
		animationTimer += fElapsedTime;
		if (animationTimer >= animationDuration) {
			currentState = FaithState::NONE; // Reset to default state after animation duration
			animationTimer = 0.0f;
		}
	}
}

void FaithRenderer::DrawFaith(olc::PixelGameEngine* pge)
{
	int screenWidth = pge->ScreenWidth();
	int screenHeight = pge->ScreenHeight();
	olc::vi2d center(screenWidth / 2, screenHeight / 2);
	int halfSprite = spriteWidth / 2;

	// Want Faith centerred horizontally and in the top half vertically
	olc::vi2d spritePos(center.x - halfSprite, center.y - (screenHeight /2));

	FaithState faithState = currentState;
	// Draw the cat based on the faith state
	switch (faithState)
	{
	case NONE:
		pge->SetPixelMode(olc::Pixel::MASK);
		pge->DrawSprite(spritePos, faithNeutral.get());
		pge->SetPixelMode(olc::Pixel::NORMAL);
		break;
	case MOUTH_LEFT:
		pge->SetPixelMode(olc::Pixel::MASK);
		pge->DrawSprite(spritePos, faithMouthLeft.get());
		pge->SetPixelMode(olc::Pixel::NORMAL);
		break;
	case MOUTH_RIGHT:
		pge->SetPixelMode(olc::Pixel::MASK);
		pge->DrawSprite(spritePos, faithMouthRight.get());
		pge->SetPixelMode(olc::Pixel::NORMAL);
		break;
	case PAW_LEFT:
		pge->SetPixelMode(olc::Pixel::MASK);
		pge->DrawSprite(spritePos, faithPawLeft.get());
		pge->SetPixelMode(olc::Pixel::NORMAL);
		break;
	case PAW_RIGHT:
		pge->SetPixelMode(olc::Pixel::MASK);
		pge->DrawSprite(spritePos, faithPawRight.get());
		pge->SetPixelMode(olc::Pixel::NORMAL);
		break;
	default:
		break;
	}
}

void FaithRenderer::DrawUI(olc::PixelGameEngine* pge)
{
	// Button position helper variables
	int uiSpriteSize = 64;
	int uiSpriteHalfSize = uiSpriteSize / 2;
	int buttonCenterHorizontal = pge->ScreenWidth() / 2;
	int buttonCenterVertical = pge->ScreenHeight() - uiSpriteSize - 50;
	olc::vi2d buttonCenter(buttonCenterHorizontal, buttonCenterVertical);
	olc::vi2d buttonInputUpPos(buttonCenterHorizontal - uiSpriteHalfSize, buttonCenterVertical - uiSpriteSize);
	olc::vi2d buttonInputDownPos(buttonCenterHorizontal - uiSpriteHalfSize, buttonCenterVertical + uiSpriteHalfSize);
	olc::vi2d buttonInputLeftPos(buttonCenterHorizontal - uiSpriteSize, buttonCenterVertical - uiSpriteHalfSize);
	olc::vi2d buttonInputRightPos(buttonCenterHorizontal + uiSpriteHalfSize, buttonCenterVertical - uiSpriteHalfSize);

	// Draw sprites
	pge->SetPixelMode(olc::Pixel::MASK);

	switch (currentState) {
	case NONE:
		pge->DrawSprite(buttonInputUpPos, uiInputUp.get());
		pge->DrawSprite(buttonInputDownPos, uiInputDown.get());
		pge->DrawSprite(buttonInputLeftPos, uiInputLeft.get());
		pge->DrawSprite(buttonInputRightPos, uiInputRight.get());
		break;
	case MOUTH_LEFT:
		pge->DrawSprite(buttonInputUpPos, uiInputUp.get());
		pge->DrawSprite(buttonInputDownPos, uiInputDown.get());
		pge->DrawSprite(buttonInputLeftPos, uiInputLeftPressed.get());
		pge->DrawSprite(buttonInputRightPos, uiInputRight.get());
		break;
	case MOUTH_RIGHT:
		pge->DrawSprite(buttonInputUpPos, uiInputUp.get());
		pge->DrawSprite(buttonInputDownPos, uiInputDown.get());
		pge->DrawSprite(buttonInputLeftPos, uiInputLeft.get());
		pge->DrawSprite(buttonInputRightPos, uiInputRightPressed.get());
		break;
	case PAW_LEFT:
		pge->DrawSprite(buttonInputUpPos, uiInputUpPressed.get());
		pge->DrawSprite(buttonInputDownPos, uiInputDown.get());
		pge->DrawSprite(buttonInputLeftPos, uiInputLeft.get());
		pge->DrawSprite(buttonInputRightPos, uiInputRight.get());
		break;
	case PAW_RIGHT:
		pge->DrawSprite(buttonInputUpPos, uiInputUp.get());
		pge->DrawSprite(buttonInputDownPos, uiInputDownPressed.get());
		pge->DrawSprite(buttonInputLeftPos, uiInputLeft.get());
		pge->DrawSprite(buttonInputRightPos, uiInputRight.get());
		break;
	default:
		break;
	}

	pge->SetPixelMode(olc::Pixel::NORMAL);

	// Draw labels
	DrawStringCentered(pge, buttonInputUpPos.y - 15, "Walk Left");
	DrawStringCentered(pge, buttonInputDownPos.y + uiSpriteHalfSize + 10, "Walk Right");

	// For left and right the string length * 8 will give the width in pixels
	// of the text
	pge->DrawString({ buttonInputLeftPos.x - 16 - 72, buttonInputLeftPos.y + uiSpriteHalfSize}, "Meow Left");
	pge->DrawString({ buttonInputRightPos.x + 16 + 32, buttonInputRightPos.y + uiSpriteHalfSize }, "Meow Right");
}

void FaithRenderer::DrawMenu(olc::PixelGameEngine* pge, MainMenuItem highlightedMenuItem, int highScore, float totalElapsedTime) {
	int screenWidth = pge->ScreenWidth();
	int screenHeight = pge->ScreenHeight();
	olc::vi2d screenCenter = { (screenWidth / 2), (screenHeight / 2) };

	//******************************************************************
	//* The menu is split up into two sections. Title in the top third *
	//* with the rest of the options set up in the bottom two thirds   *
	//* of the screen                                                  *
	//******************************************************************
	int titleLimit = screenHeight / 3;
	int menuTopLimit = titleLimit;
	unsigned int titleScale = 6;
	unsigned int  textScale = 4;
	int textHeight = 8 * textScale;
	int spacingGap = 30;
	int cursorSize = 32;
	int cursorGap = 8;

	DrawStringCentered(pge, (titleLimit / 2) - 8, "FAITH SAYS", olc::WHITE, titleScale);

	std::vector<std::string> menuItems = { "PLAY", "CREDITS", "QUIT" };
	int menuStart = menuTopLimit + (screenHeight - menuTopLimit - (spacingGap * 5) - (textHeight * menuItems.size()));

	for (int i = 0; i < menuItems.size(); i++) {
		int menuItemYPos = menuStart + (i * (textHeight + spacingGap));
		int menuItemXPos = (screenWidth - (menuItems[i].length() * 8 * textScale)) / 2;
		pge->DrawString(menuItemXPos, menuItemYPos, menuItems[i], olc::WHITE, textScale);

		// Check if we need to draw the cursor
		if (static_cast<size_t>(highlightedMenuItem) == i) {
			float bounceOffset = std::sin(totalElapsedTime * 5.0f) * 4.0f;
			int cursorXPos = menuItemXPos - cursorSize - cursorGap + (int)bounceOffset;
			int cursorYPos = menuItemYPos + ((textHeight - cursorSize) / 2);
			pge->DrawSprite(cursorXPos, cursorYPos, uiMenuCursor.get());
		}
	}


	DrawHighScoreMainMenu(pge, highScore);
}

void FaithRenderer::DrawCreditsScreen(olc::PixelGameEngine* pge) {
	std::string mainDev = "Jossie \"Demasu\" Brandt";
	std::string foxPartner = "Kit";
	std::string catPartner = "Larch";
	int titleScale = 9;
	int roleScale = 3;
	int regularScale = 2;
	int minorSpacing = 8;
	int majorSpacing = 30;

	int creditsTitlePos = 50;
	int mainCreditsStartPos = creditsTitlePos + (titleScale * 8) + majorSpacing;
	int mainDevNamePos      = mainCreditsStartPos + (roleScale * 8) + minorSpacing;
	int foxSupportOnePos = mainDevNamePos + (regularScale * 8) + majorSpacing;
	int foxSupportTwoPos = foxSupportOnePos + (roleScale * 8) + minorSpacing;
	int foxSupportNamePos = foxSupportTwoPos + (roleScale * 8) + minorSpacing;
	int catSupportOnePos = foxSupportNamePos + (regularScale * 8) + majorSpacing;
	int catSupportTwoPos = catSupportOnePos + (roleScale * 8) + minorSpacing;
	int catSupportThreePos = catSupportTwoPos + (roleScale * 8) + minorSpacing;
	int catSupportNamePos = catSupportThreePos + (roleScale * 8) + minorSpacing;

	olc::Pixel foxOrange(255, 153, 0);
	olc::Pixel seafoamGreen(159, 226, 191);

	DrawStringCentered(pge, 50, "CREDITS", olc::WHITE, titleScale);

	DrawStringCentered(pge, mainCreditsStartPos, "MAIN DEV", olc::DARK_MAGENTA, roleScale);
	DrawStringCentered(pge, mainDevNamePos, mainDev, olc::DARK_MAGENTA, regularScale);
	
	DrawStringCentered(pge, foxSupportOnePos, "EMOTIONAL SUPPORT FOX", foxOrange, roleScale);
	DrawStringCentered(pge, foxSupportTwoPos, "& AMAZING PARTNER", foxOrange, roleScale);
	DrawStringCentered(pge, foxSupportNamePos, foxPartner, foxOrange, regularScale);
	
	DrawStringCentered(pge, catSupportOnePos, "BEST LAP KITTY", seafoamGreen, roleScale);
	DrawStringCentered(pge, catSupportTwoPos, "& INCREDIBLE", seafoamGreen, roleScale);
	DrawStringCentered(pge, catSupportThreePos, "GIRLFRIEND", seafoamGreen, roleScale);
	DrawStringCentered(pge, catSupportNamePos, catPartner, seafoamGreen, regularScale);

}

void FaithRenderer::DrawGameOverScreen(olc::PixelGameEngine* pge) {
	int mainScale = 8;
	int regularScale = 2;
	int textDefaultHeight = 8;
	int mainTextSize = textDefaultHeight * mainScale;
	int regularTextSize = textDefaultHeight * regularScale;

	int gameOverStart = 50;
	int majorSpacing = textDefaultHeight * 2;
	int minorSpacing = textDefaultHeight;

	int instructionsStart = pge->ScreenHeight() / 2;


	DrawStringCentered(pge, gameOverStart, "GAME", olc::WHITE, mainScale);
	DrawStringCentered(pge, gameOverStart + mainTextSize + minorSpacing, "OVER", olc::WHITE, mainScale);
	DrawStringCentered(pge, instructionsStart, "To return to the main", olc::WHITE, regularScale);
	DrawStringCentered(pge, instructionsStart + regularTextSize + minorSpacing, "menu press ENTER", olc::WHITE, regularScale);
	DrawStringCentered(pge, instructionsStart + regularTextSize + minorSpacing + regularTextSize + majorSpacing, "To quit press ESCAPE", olc::WHITE, regularScale);
}

void FaithRenderer::DrawStringCentered(olc::PixelGameEngine* pge, int y, const std::string& text, olc::Pixel color, uint32_t scale) {
	int x = (pge->ScreenWidth() - (text.length() * 8 * scale)) / 2;
	pge->DrawString(x, y, text, color, scale);
}

void FaithRenderer::Reset() {
	currentState = FaithState::NONE;
	animationTimer = 0.0f;
}

void FaithRenderer::DrawHighScore(olc::PixelGameEngine* pge, int highScore) {
	int scale = 2;
	int spacing = 8;
	std::string highScoreString = std::to_string(highScore);
	olc::vi2d highScoreTitlePos(2, 2);
	olc::vi2d highScorePos(2, highScoreTitlePos.y + (8 * scale) + spacing);

	pge->DrawString(highScoreTitlePos, "HIGH SCORE:", olc::WHITE, scale);
	pge->DrawString(highScorePos, highScoreString, olc::WHITE, scale);
}

void FaithRenderer::DrawHighScoreMainMenu(olc::PixelGameEngine* pge, int highScore) {
	int scale = 2;
	int scoreStart = pge->ScreenHeight() - (scale * 8) - 8;
	DrawStringCentered(pge, scoreStart, "High Score: " + std::to_string(highScore), olc::WHITE, scale);
}

void FaithRenderer::DrawScore(olc::PixelGameEngine* pge, int currentScore) {
	int spacing = 8;
	int scale = 2;
	std::string scoreString = std::to_string(currentScore);
	olc::vi2d scoreTitlePos(pge->ScreenWidth() - (6*8*scale), 2);
	olc::vi2d scorePos(pge->ScreenWidth() - (scoreString.length() * 8 * scale + 8), scoreTitlePos.y + 8 + spacing);

	pge->DrawString(scoreTitlePos, "SCORE:", olc::WHITE, scale);
	pge->DrawString(scorePos, scoreString, olc::WHITE, scale);
}
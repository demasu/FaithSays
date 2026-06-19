#include "FaithRenderer.h"
#include <array>

FaithRenderer::FaithRenderer(FaithState initialState) : currentState(initialState), animationTimer(0.0f), animationDuration(0.5f) {
}

void FaithRenderer::LoadFaithSprites() {
	// Load sprites for Faith's face and actions
	faithNeutral = std::make_unique<olc::Sprite>("faith_head.png");
	faithMouthLeft = std::make_unique<olc::Sprite>("faith_head_left.png");
	faithMouthRight = std::make_unique<olc::Sprite>("faith_head_right.png");
	faithPawLeft = std::make_unique<olc::Sprite>("faith_paw_left.png");
	faithPawRight = std::make_unique<olc::Sprite>("faith_paw_right.png");
}

void FaithRenderer::TriggerAnimation(FaithState actionState, float duration) {
	currentState = actionState;
	animationTimer = 0.0f;
	animationDuration = duration;
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

void FaithRenderer::LoadUISprites() {
	uiInputLeft = std::make_unique<olc::Sprite>("button_mouth_left_new.png");
	uiInputRight = std::make_unique<olc::Sprite>("button_mouth_right_new.png");
	uiInputUp = std::make_unique<olc::Sprite>("button_paw_left_new.png");
	uiInputDown = std::make_unique<olc::Sprite>("button_paw_right_new.png");
	uiInputLeftPressed = std::make_unique<olc::Sprite>("button_mouth_left_new_pressed.png");
	uiInputRightPressed = std::make_unique<olc::Sprite>("button_mouth_right_new_pressed.png");
	uiInputUpPressed = std::make_unique<olc::Sprite>("button_paw_left_new_pressed.png");
	uiInputDownPressed = std::make_unique<olc::Sprite>("button_paw_right_new_pressed.png");
	uiMenuCursor = std::make_unique<olc::Sprite>("cursor.png");
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

void FaithRenderer::DrawMenu(olc::PixelGameEngine* pge, MenuItem highlightedMenuItem, float totalElapsedTime) {
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
}

void FaithRenderer::DrawCreditsScreen(olc::PixelGameEngine* pge) {

}

void FaithRenderer::DrawStringCentered(olc::PixelGameEngine* pge, int y, const std::string& text, olc::Pixel color, uint32_t scale) {
	int x = (pge->ScreenWidth() - (text.length() * 8 * scale)) / 2;
	pge->DrawString(x, y, text, color, scale);
}
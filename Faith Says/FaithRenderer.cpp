#include "FaithRenderer.h"

FaithRenderer::FaithRenderer(FaithState initialState) : currentState(initialState), animationTimer(0.0f), animationDuration(0.5f)
{
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
	if (currentState != NONE) {
		animationTimer += fElapsedTime;
		if (animationTimer >= animationDuration) {
			currentState = NONE; // Reset to default state after animation duration
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
	uiInputLeft = std::make_unique<olc::Sprite>("button_mouth_left.png");
	uiInputRight = std::make_unique<olc::Sprite>("button_mouth_right.png");
	uiInputUp = std::make_unique<olc::Sprite>("button_paw_left.png");
	uiInputDown = std::make_unique<olc::Sprite>("button_paw_right.png");
	uiInputLeftPressed = std::make_unique<olc::Sprite>("button_mouth_left_pressed.png");
	uiInputRightPressed = std::make_unique<olc::Sprite>("button_mouth_right_pressed.png");
	uiInputUpPressed = std::make_unique<olc::Sprite>("button_paw_left_pressed.png");
	uiInputDownPressed = std::make_unique<olc::Sprite>("button_paw_right_pressed.png");
}

void FaithRenderer::DrawUI(olc::PixelGameEngine* pge)
{
	// Button position helper variables
	int uiSpriteSize = 64;
	int uiSpriteHalfSize = uiSpriteSize / 2;
	int buttonCenterHorizontal = pge->ScreenWidth() / 2;
	int buttonCenterVertical = pge->ScreenHeight() - uiSpriteSize - 50;
	olc::vi2d buttonCenter(buttonCenterHorizontal, buttonCenterVertical);
	olc::vi2d buttonInputUpPos(buttonCenterHorizontal - uiSpriteSize, buttonCenterVertical - uiSpriteSize);
	olc::vi2d buttonInputDownPos(buttonCenterHorizontal, buttonCenterVertical - uiSpriteSize);
	olc::vi2d buttonInputLeftPos(buttonCenterHorizontal - uiSpriteSize, buttonCenterVertical);
	olc::vi2d buttonInputRightPos(buttonCenterHorizontal, buttonCenterVertical);

	// Text labels
	olc::vi2d upInputLabelPos   (buttonCenterHorizontal - (uiSpriteSize * 2) - 20, buttonCenterVertical - uiSpriteHalfSize);
	olc::vi2d downInputLabelPos (buttonCenterHorizontal + (uiSpriteSize) + 10,     buttonCenterVertical - uiSpriteHalfSize);
	olc::vi2d leftInputLabelPos (buttonCenterHorizontal - (uiSpriteSize * 2) - 20, buttonCenterVertical + uiSpriteHalfSize);
	olc::vi2d rightInputLabelPos(buttonCenterHorizontal + (uiSpriteSize) + 10,     buttonCenterVertical + uiSpriteHalfSize);

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
	pge->DrawString(upInputLabelPos, "Walk left");
	pge->DrawString(downInputLabelPos, "Walk right");
	pge->DrawString(leftInputLabelPos, "Meow left");
	pge->DrawString(rightInputLabelPos, "Meow right");
}
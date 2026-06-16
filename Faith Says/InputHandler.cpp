#include "InputHandler.h"

InputHandler::InputHandler() {}

FaithRenderer::FaithState InputHandler::HandleInput(olc::PixelGameEngine* pge)
{
	FaithRenderer::FaithState none = FaithRenderer::FaithState::NONE;
	FaithRenderer::FaithState mouthLeft = FaithRenderer::FaithState::MOUTH_LEFT;
	FaithRenderer::FaithState mouthRight = FaithRenderer::FaithState::MOUTH_RIGHT;
	FaithRenderer::FaithState pawLeft = FaithRenderer::FaithState::PAW_LEFT;
	FaithRenderer::FaithState pawRight = FaithRenderer::FaithState::PAW_RIGHT;

	// Check left inpputs
	if (pge->GetKey(olc::Key::LEFT).bPressed)
	{
		return mouthLeft;
	}
	else if (pge->GetKey(olc::Key::A).bPressed) {
		return mouthLeft;
	}
	else if (pge->GetKey(olc::Key::NP4).bPressed) {
		return mouthLeft;
	}

	// Check right inputs
	if (pge->GetKey(olc::Key::RIGHT).bPressed)
	{
		return mouthRight;
	}
	else if (pge->GetKey(olc::Key::D).bPressed) {
		return mouthRight;
	}
	else if (pge->GetKey(olc::Key::NP6).bPressed) {
		return mouthRight;
	}
	
	// Check up inputs
	if (pge->GetKey(olc::Key::UP).bPressed)
	{
		return pawLeft;
	}
	else if (pge->GetKey(olc::Key::W).bPressed) {
		return pawLeft;
	}
	else if (pge->GetKey(olc::Key::NP8).bPressed) {
		return pawLeft;
	}
	
	// Check down inputs
	if (pge->GetKey(olc::Key::DOWN).bPressed)
	{
		return pawRight;
	}
	else if (pge->GetKey(olc::Key::S).bPressed) {
		return pawRight;
	}
	else if (pge->GetKey(olc::Key::NP2).bPressed) {
		return pawRight;
	}

	// Default state
	return none;
}
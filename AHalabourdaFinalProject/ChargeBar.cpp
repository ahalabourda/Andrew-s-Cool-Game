#include "ChargeBar.h"
#include <iostream>

void ChargeBar::Draw(Vector2 pCenterPosition, Color pColour) const
{
	//std::cout << "trying to draw a triangle at " << static_cast<int>(pCenterPosition.x - msWidth / 2) << "," << static_cast<int>(pCenterPosition.y) << " sized " << static_cast<int>(msWidth) << "x" << static_cast<int>(msHeight) << std::endl;

	// here's the border
	DrawRectangle(	static_cast<int>(pCenterPosition.x - ((msWidth + msBorderWidth) / 2)), // centering ourselves within our quadrant
					static_cast<int>(pCenterPosition.y - (msBorderWidth / 2)), 
					static_cast<int>((GetScreenWidth() / 10.0f) + msBorderWidth ), 
					static_cast<int>((GetScreenHeight() / 25.0f) + msBorderWidth),
					BLACK);

	// here's the contents
	DrawRectangle(	static_cast<int>(pCenterPosition.x - (msWidth / 2)), // centering ourselves within our quadrant
					static_cast<int>(pCenterPosition.y),
					static_cast<int>(GetScreenWidth() / 10.0f * mFillCurrent / msFillMax), // filling based on charge level
					static_cast<int>(GetScreenHeight() / 25.0f), 
					pColour);
}
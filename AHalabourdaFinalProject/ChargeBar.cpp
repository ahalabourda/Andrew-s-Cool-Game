#include "ChargeBar.h"
#include <iostream>

int ChargeBar::msWidth;
int ChargeBar::msHeight;
int ChargeBar::msBorderWidth;

void ChargeBar::Draw(const Vector2& pCenterPosition, const Color& pColour) const
{

	

	// here's the border
	DrawRectangle(	(static_cast<int>(pCenterPosition.x) - ((msWidth + msBorderWidth) / 2)), // centering ourselves within our quadrant
					(static_cast<int>(pCenterPosition.y) - (msBorderWidth / 2)),
					(msWidth + msBorderWidth ),
					(msHeight + msBorderWidth),
					mBorderColor);

	// here's the contents
	DrawRectangle(	(static_cast<int>(pCenterPosition.x) - (msWidth / 2)), // centering ourselves within our quadrant
					static_cast<int>(pCenterPosition.y),
					static_cast<int>(msWidth * (mFillCurrent / msFillMax)), // filling based on charge level
					msHeight,
					pColour);

	if (mFillCurrent > msFillMax) {
		DrawText("MAX", (static_cast<int>(pCenterPosition.x) - ((MeasureText("MAX", mLabelFontSize) / 2))), static_cast<int>(pCenterPosition.y) + 2, mLabelFontSize, mLabelColor);
	}

}

void ChargeBar::InitializeChargeBarSize()
{
	msWidth = static_cast<int>(GetScreenWidth() / 10.0f);
	msHeight = static_cast<int>(GetScreenHeight() / 30.0f);
	msBorderWidth = static_cast<int>(GetScreenWidth() / 100.0f);

	std::cout << "Just set: " << msWidth << ", " << msHeight << ", " << msBorderWidth << std::endl;
}
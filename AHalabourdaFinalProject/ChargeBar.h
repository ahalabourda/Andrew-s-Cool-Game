#pragma once
#include <raylib.h>
class ChargeBar
{

public:
	
	void SetFillAmount(float pFillAmount) { mFillCurrent = pFillAmount; }
	void Draw(Vector2 pCenterPosition, Color pColour) const;

	int GetWidth() const { return msWidth; }
	int GetHeight() const { return msHeight; }
	float GetFillMax() const { return msFillMax; }

private:
	
	// i wish these were static but static initialization happens before raylib's screen height/width functions have valid numbers
	// sooo. no static. farewell bytes
	const int msWidth = static_cast<int>(GetScreenWidth() / 10.0f);
	const int msHeight = static_cast<int>(GetScreenHeight() / 50.0f);
	const int msBorderWidth = static_cast<int>(GetScreenWidth() / 100.0f);

	// unused since we're just doing black for now
	// inline const static Color msBorderColour{ 255, 255, 255, 255 };
	// inline const static Color msBodyColour{ 50, 50, 50, 255 };

	inline static const float msFillMax = 100.0f;
	float mFillCurrent = 0.0f;

	inline static const float mLabelFontSize = 24.0f;
	/*inline static const Color mLabelColor{ 255, 255, 255, 200 };*/
	inline static const Color mLabelColor = BLACK;

};
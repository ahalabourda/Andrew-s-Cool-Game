#pragma once
#include <raylib.h>
class ChargeBar
{

public:
	
	void SetFillAmount(float pFillAmount) { mFillCurrent = pFillAmount; }
	void Draw(const Vector2 & pCenterPosition, const Color & pColour) const;

	static int GetWidth() { return msWidth; }
	static int GetHeight() { return msHeight; }
	static float GetFillMax() { return msFillMax; }

	static void InitializeChargeBarSize();

private:
	
	// i wish these were static but static initialization happens before raylib's screen height/width functions have valid numbers
	// sooo. no static. farewell bytes
	static int msWidth;
	static int msHeight;
	static int msBorderWidth;

	// unused since we're just doing black for now
	// inline const static Color msBorderColour{ 255, 255, 255, 255 };
	// inline const static Color msBodyColour{ 50, 50, 50, 255 };

	inline static const float msFillMax = 100.0f;
	float mFillCurrent = 0.0f;

	inline static const float mLabelFontSize = 24.0f;
	/*inline static const Color mLabelColor{ 255, 255, 255, 200 };*/
	inline static const Color mLabelColor = BLACK;
	inline static const Color mBorderColor = BLACK;

};
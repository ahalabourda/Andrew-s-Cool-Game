#pragma once
#include <raylib.h>
class ChargeBar
{

public:
	
	float GetCurrentFillAmount() const { return mFillCurrent / msFillMax; }
	void SetFillAmount(float pFillAmount) { mFillCurrent = pFillAmount; }
	void Draw(const Vector2 & pCenterPosition, const Color & pColour) const;

	static int GetWidth() { return msWidth; }
	static int GetHeight() { return msHeight; }
	static float GetFillMax() { return msFillMax; }

	static void InitializeChargeBarSize();

private:
	
	// these are initialized late through a static method because they depend on some raylib screen-size functions that only work after some runtime init stuff happens
	static int msWidth;
	static int msHeight;
	static int msBorderWidth;

	inline static const float msFillMax = 100.0f;
	float mFillCurrent = 0.0f;

	inline static const float mLabelFontSize = 24.0f;
	inline static const Color mLabelColor = BLACK;
	inline static const Color mBorderColor = BLACK;

};
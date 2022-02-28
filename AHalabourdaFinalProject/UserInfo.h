#pragma once
#include <raylib.h>
#include <string>
class UserInfo
{

public:

	int GetMaxNameLength() const { return mMaxNameLength; }

	void AddLetter(char pNewLetter) { if (mName.length() + 1 <= mMaxNameLength) { mName += pNewLetter; } }
	void RemoveLetter() { if (mName.length() > 0) { mName.pop_back(); } }
	std::string GetName() const { return mName; }

	Rectangle GetTextBox() const { return mTextBox; }

	int GetFontSize() const { return mFontSize; }

	void Tick() { mTickCounter++; }


private:
	static const int mMaxNameLength = 10;
	std::string mName = "";

	Rectangle mTextBox = { GetScreenWidth() / 2.0f - 100, 250, 225, 50 };

	int mTickCounter = 0;

	const int mFontSize = 40;

};
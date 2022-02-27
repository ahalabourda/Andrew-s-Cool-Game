#pragma once
#include <string>

class LeaderboardManager
{

public:
	bool SubmitScore(std::string pUsername, int pScore);

	std::string GetLeaderboardData() const { return mLeaderboardData; }
	void UpdateLeaderboardData();

	const int GetFontSize() const { return mFontSize; }

private:
	// http request library doesn't allow https :[
	// seems complicated to implement
	std::string mBaseURL = "http://spacetank.andrew.gg/submit.php";

	std::string mLeaderboardData = "Loading leaderboard data...";

	const int mFontSize = 36;
	bool mHasSubmitted = false;

};
#pragma once
#include <string>

class LeaderboardManager
{

public:
	bool SubmitScore(std::string pUsername, int pScore);

	std::string GetLeaderboardData() const { return mLeaderboardData; }
	void FetchLeaderboardData();

	const int GetFontSize() const { return mFontSize; }

private:
	// http request library doesn't support https :[
	// seems complicated to implement myself
	std::string mBaseURL = "http://spacetank.andrew.gg/submit.php";

	// safety message in case of lag time
	std::string mLeaderboardData = "Loading leaderboard data...";

	const int mFontSize = 36;

};
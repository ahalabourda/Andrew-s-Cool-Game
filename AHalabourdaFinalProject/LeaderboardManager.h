#pragma once
#include <string>

class LeaderboardManager
{

public:
	void Testeroonie();

	bool SubmitScore(std::string pUsername, int pScore, int pMovespeedLevel, int pMultiplierLevel, int pDamageLevel, int pFirerateLevel, int pDurationInSeconds, int pAsteroidsExploded);

private:
	std::string mBaseURL = "https://andrew.gg/spacetank/submit.php";

};
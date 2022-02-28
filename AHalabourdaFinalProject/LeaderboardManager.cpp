#include "LeaderboardManager.h"
#include "HTTPHeader.hpp"
#include "json.hpp"
#include <sstream>


bool LeaderboardManager::SubmitScore(std::string pUsername, int pScore)
{
    
    std::stringstream ss;

    ss << mBaseURL << "?username=" << pUsername << "&score=" << pScore;
    
    try {
        http::Request request{ ss.str() };

        const auto response = request.send("GET");

        return true;
    }
    catch (...) {
        return false;
    }

}

void LeaderboardManager::FetchLeaderboardData()
{

    try {

        // hardcoding this here is a little bad but oh well. would do this more nicely on a bigger project
        http::Request request{ "http://spacetank.andrew.gg/get-leaderboards.php" };

        const auto response = request.send();

        mLeaderboardData = std::string{ response.body.begin(), response.body.end() };

    }
    catch (...) {
        mLeaderboardData = std::string("Error retrieving leaderboards!");
    }

}
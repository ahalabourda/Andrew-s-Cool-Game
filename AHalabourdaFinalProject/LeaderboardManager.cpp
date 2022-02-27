#include "LeaderboardManager.h"
#include "HTTPHeader.hpp"
#include "json.hpp"
#include <iostream>
#include <sstream>


bool LeaderboardManager::SubmitScore(std::string pUsername, int pScore)
{
    
    std::stringstream ss;

    ss << mBaseURL << "?username=" << pUsername << "&score=" << pScore;
    
    try {
        http::Request request{ ss.str() };

        const auto response = request.send("GET");

        // print the result
        std::cout << std::string{ response.body.begin(), response.body.end() } << '\n';

        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Submission failed: " << e.what() << std::endl;
        return false;
    }

}

void LeaderboardManager::UpdateLeaderboardData()
{

    try {

        // hardcoding this here is a little bad but oh well. would do this more nicely on a bigger project
        http::Request request{ "http://spacetank.andrew.gg/get-leaderboards.php" };

        const auto response = request.send();

        mLeaderboardData = std::string{ response.body.begin(), response.body.end() };

    }
    catch (const std::exception& e) {
        std::cerr << "Submission failed: " << e.what() << std::endl;
        mLeaderboardData = std::string("Error retrieving leaderboards");
    }
}

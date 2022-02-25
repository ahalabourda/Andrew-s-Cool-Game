#include "LeaderboardManager.h"
#include "HTTPHeader.hpp"
#include "json.hpp"
#include <iostream>
#include <sstream>

// yay
void LeaderboardManager::Testeroonie()
{

    try
    {
        // you can pass http::InternetProtocol::V6 to Request to make an IPv6 request
        http::Request request{ "http://google.com/" };

        // send a get request
        const auto response = request.send("GET");
        std::cout << std::string{ response.body.begin(), response.body.end() } << '\n'; // print the result
    }
    catch (const std::exception& e)
    {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }

}

bool LeaderboardManager::SubmitScore(std::string pUsername, int pScore, int pMovespeedLevel, int pMultiplierLevel, int pDamageLevel, int pFirerateLevel, int pDurationInSeconds, int pAsteroidsExploded)
{
    
    std::stringstream ss;

    ss << mBaseURL << "?username=" << pUsername << "&score=" << pScore << "&movespeed_level=" << pMovespeedLevel << "&multiplier_level=" << pMultiplierLevel << "&damage_level=" << pDamageLevel << "&firerate_level" << pFirerateLevel << "&duration_in_seconds=" << pDurationInSeconds << "&asteroids_exploded=" << pAsteroidsExploded;
    
    try {
        http::Request request{ ss.str() };

        const auto response = request.send("GET");

        std::cout << std::string{ response.body.begin(), response.body.end() } << '\n'; // print the result

        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Submission failed: " << e.what() << std::endl;
        return false;
    }

}
#pragma once
#include <string>
#include <tuple>

class HttpClient
{
public:
    std::tuple<bool, std::string, std::string> performHttpRequest(const std::string& host, const std::string& target);
};

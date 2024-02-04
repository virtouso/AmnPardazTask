#include <fstream>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

#include "Helpers/FileManager.h"
#include "Helpers/HttpClient.h"


int main()
{
    std::string host = "jsonplaceholder.typicode.com";
    std::string target = "/todos";

    HttpClient cli{};
    auto [success,body,header] = cli.performHttpRequest(host, target);

    std::cout << "HTTP succ:\n" << success << std::endl;
    std::cout << "HTTP body:\n" << body << std::endl;
    std::cout << "HTTP header:\n" << header << std::endl;

    FileManager fileManager{};
    fileManager.Save(body + header, "D://test.txt");

    return 0;
}

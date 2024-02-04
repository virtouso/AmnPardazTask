#include "HttpClient.h"

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <nlohmann/json.hpp>
namespace asio = boost::asio;
namespace beast = boost::beast;
using tcp = asio::ip::tcp;


std::tuple<bool, std::string, std::string> HttpClient::performHttpRequest(const std::string& host,const std::string& target)
{
    try
    {
        // Create IO context
        asio::io_context ioContext;

        // Resolve the host name and port
        tcp::resolver resolver(ioContext);
        auto endpoints = resolver.resolve(host, "http");

        // Create and connect the socket
        tcp::socket socket(ioContext);
        asio::connect(socket, endpoints.begin(), endpoints.end());

        // Form the HTTP request
        beast::http::request<beast::http::string_body> request(beast::http::verb::get, target, 11);
        request.set(beast::http::field::host, host);
        request.set(beast::http::field::user_agent, "Boost Beast HTTP Client");

        // Send the request
        beast::http::write(socket, request);

        // Receive the response
        beast::flat_buffer buffer;
        beast::http::response<beast::http::dynamic_body> response;
        beast::http::read(socket, buffer, response);

        nlohmann::json headersJson;
        for (auto it = response.base().begin(); it != response.base().end(); ++it) {
            headersJson[it->name_string()] = it->value();
        }

        
        // Convert the response body to a string
        return  std::make_tuple(true, boost::beast::buffers_to_string(response.body().data()), headersJson.dump(2));
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return std::make_tuple(false,nullptr,nullptr);
    }
}


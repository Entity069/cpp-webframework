#include <iostream>
#include "./include/server.h"
#include "./include/nlohmann/json.hpp"
#include "./include/inja/inja.hpp"

using namespace MicroWeb;
using json = nlohmann::json;

int main() {
    Server server;

    // Basic route
    server.route("GET", "/hello", [](Request& req, Response& res) {
        res.setContentType(MIME_JSON);
        json response = {
            {"message", "Hello, World!"},
            {"status", "success"}
        };
        res.json(response);
    });

    server.route("POST", "/login", [](Request& req, Response& res) {
        json body = req.getJsonBody();
        // std::cout << "Body from main.cpp " << body << std::endl;
        std::string username = body["username"];
        std::string password = body["password"];

        if (username == "admin" && password == "heyjuuuuuude") {
            res.setStatus(HTTP_OK);
            res.json({{"user_auth", "true"}});
        } else {
            res.setStatus(HTTP_BAD_REQUEST);
            res.json({{"error", "Invalid credentials"}});
        }
    });

//    server.use("auth", Middleware::authMiddleware);
    server.use("cookie_parser", Middleware::cookieMiddleware);

    server.start();

    return 0;
}
#pragma once
#include <httplib.h>
#include <iostream>
#include <vector>
#include <functional>
namespace ServerRoute{
    enum RouteType {
        GET = 0,
        POST,
    };


    struct HttplibRoute {
        RouteType type;
        std::string path;
        std::function<void(const httplib::Request&, httplib::Response&)> callback;
    };
    
}
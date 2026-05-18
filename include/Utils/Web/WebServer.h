#ifdef ENABLE_WEB_SERVER
#include <httplib.h>
#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include "Route.h"
class HttpLibServer {
    std::thread serverThread;
    httplib::Server svr;
    std::vector<ServerRoute::HttplibRoute> serverRoutes;


    std::string ip_port;
    public:

    void AddRoute(ServerRoute::HttplibRoute rt){
        serverRoutes.push_back(rt);
        
    }
    void StartServer(std::string ip = "0.0.0.0", int port = 1234) {
        ip_port = ip + ":" + std::to_string(port);
        for(int i = 0; i < serverRoutes.size(); i++){
            ServerRoute::HttplibRoute rt = serverRoutes[i];
            if(rt.type == ServerRoute::RouteType::GET){
                auto callback = rt.callback;
                svr.Get(rt.path, [rt, callback](const httplib::Request& req, httplib::Response& res) {
                    if(callback)
                        callback(req,res);
                });
            }
        }
        serverThread = std::thread([this, &ip, &port]() {
            this->svr.listen(ip, port);
           
        });
        
    }
    void StopServer(){
        svr.stop();
    }
};
#endif

/*
    - USAGE -

    HttpLibServer svr;

    ServerRoute::HttplibRoute rt = ServerRoute::HttplibRoute();
    rt.path = "/login";
    rt.callback = Function;   void Function(const httplib::Request& req, httplib::Response& res)
    rt.type = Types::GET;
    svr->AddRoute(rt);


    svr->StartServer(ip, port);

*/
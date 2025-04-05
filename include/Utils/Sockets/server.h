#ifdef ENABLE_SOCKETS
#pragma once
#include <Utils/json.hpp>
#include <Utils/Logger.h>
#include <stdio.h>
#include <functional>
#include <tuple>
#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN  // Exclude rarely-used components from Windows headers
    #define _WINSOCKAPI_
    #define NOMINMAX
            // Main Windows API header
    #include <winsock2.h>
    #include <iphlpapi.h>
    #include <ws2tcpip.h>       // Additional Winsock functions
    #include <Windows.h> 
    #pragma comment(lib, "ws2_32.lib")
    #pragma comment(lib, "iphlpapi.lib")
#elif __linux__ || __APPLE__
    #include <ifaddrs.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
#endif
class SocketServer{
    private:
    #ifdef _WIN32
    WSADATA wsa;
    #endif
    int ServerPort;
    std::string ip;
    Logger logger = Logger("Server", "Log.txt", true);
    
    
   
    
    int serverSocket, clientSocket;
    sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);

    char buffer[1024] = {0};
    char clientIP[INET_ADDRSTRLEN];
    std::function<void(std::vector<char>, nlohmann::json)> recivedDataCallback;
    public:
    SocketServer(std::string ip_addr = "0.0.0.0",int port){
        ServerPort = port;
        ip = ip_addr;
    }
    int InitSocket(){
        #ifdef _WIN32
        logger.DebugLog("Initalising WinSock");
        if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
        {
            logger.ErrorLog("Failed. Error Code : %d",WSAGetLastError());
            return 1;
        }

        logger.DebugLog("Intialised WinSock");
        #endif
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        
        serverAddr.sin_family = AF_INET;
        if(ip == "0.0.0.0")
            serverAddr.sin_addr.s_addr = INADDR_ANY;
        else{
            inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr);
        }
        serverAddr.sin_port = htons(ServerPort);

        // Create socket
        
        bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
        return 0;
    }
    void Listen(){
        listen(serverSocket, 3);
        logger.DebugLog("Server listening on port %i", ServerPort);
        clientAddrSize = sizeof(clientAddr);
        clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize); 
        inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
        int clientPort = ntohs(clientAddr.sin_port);
        logger.DebugLog("Client has connected ",clientIP,clientPort);
    }

    void Close(){
    #ifdef _WIN32
        closesocket(clientSocket);
        closesocket(serverSocket);
        WSACleanup();
    #else
        close(clientSocket);
        close(serverSocket);
    #endif
    }

    void SendData(std::vector<char> chunkDataToSend, nlohmann::json header){

        header["chunk_size"] = chunkDataToSend.size();
        std::string jsonString = header.dump();
        std::size_t jsonSize = jsonString.size();
        int headerSize = jsonSize;
        logger.InfoLog("Sent data, chunk_size %i     HEADER: %s", chunkDataToSend.size(),jsonString.c_str());
        send(clientSocket, reinterpret_cast<char*>(&headerSize), sizeof(headerSize),0); // send the size of the header
        send(clientSocket, jsonString.c_str(), jsonSize, 0); // send the header
        send(clientSocket, chunkDataToSend.data(), chunkDataToSend.size(), 0); // send the chunk
    }
    
    std::tuple<std::vector<char>, nlohmann::json>  RecieveData(){
        int headerSize;           
        recv(clientSocket, reinterpret_cast<char*>(&headerSize), sizeof(headerSize), 0);
        logger.DebugLog("Size of header %i", headerSize);

        std::vector<char> buffer(headerSize); // SIZE OF THE HEADER

        int bytesReceived = recv(clientSocket, buffer.data(), buffer.size(), 0); // THE ACTUAL HEADER
        if (bytesReceived == -1 || bytesReceived == 0) {
            logger.ErrorLog("RECV Failed");
            logger.ErrorLog("Connection closed by client");
            exit(EXIT_FAILURE);

            return {{}, {}};
        } else {
            logger.DebugLog("Recived %i bytes", bytesReceived);

            std::string receivedData(buffer.begin(), buffer.begin() + bytesReceived);
            nlohmann::json jsonData = nlohmann::json::parse(receivedData); // THE JSON HEADER
            int chunk_size = jsonData["chunk_size"];
            std::vector<char> chunk(chunk_size);
            
            recv(clientSocket, chunk.data(), chunk.size(), 0);

            return {chunk, jsonData};

            
        }

    }
    
};
#endif
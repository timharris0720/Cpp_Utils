#ifdef ENABLE_SOCKETS
#pragma once
#ifndef ENABLE_JSON
    #define ENABLE_JSON
#endif
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

class SocketClient {
    private:
    std::string ServerIP;
    int ServerPort;
    #ifdef _WIN32
    WSADATA wsaData;
    #endif
    int clientSocket;
    sockaddr_in serverAddr;
    std::function<void(std::vector<char>, nlohmann::json)> recivedDataCallback;
    Logger logger = Logger("Client", "Log.txt", true);

    public:
    bool isConnected = false;
    SocketClient(std::string ip, int port){
        ServerIP = ip;
        ServerPort = port;
    }
    void Init(){
        #ifdef _WIN32
        WSAStartup(MAKEWORD(2, 2), &wsaData);
        #endif
        // Create socket
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);

        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(ServerPort);
        inet_pton(AF_INET, ServerIP.c_str(), &serverAddr.sin_addr);
    }
    void Close(){
        #ifdef _WIN32
            closesocket(clientSocket);
        #else
            close(clientSocket);
        #endif
    }
    void Connect(){
        connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
        isConnected = true;
        logger.InfoLog("Connected to Server");
    }
    void SendData(std::vector<char> chunkDataToSend, nlohmann::json header){

        header["chunk_size"] = chunkDataToSend.size();
        std::string jsonString = header.dump();
        std::size_t jsonSize = jsonString.size();
        int headerSize = jsonSize;
        
        send(clientSocket, reinterpret_cast<char*>(&headerSize), sizeof(headerSize),0); // send the size of the header
        send(clientSocket, jsonString.c_str(), jsonSize, 0); // send the header
        send(clientSocket, chunkDataToSend.data(), chunkDataToSend.size(), 0);
    }

    

    std::tuple<std::vector<char>, nlohmann::json> RecieveData(){
        int headerSize;           
        recv(clientSocket, reinterpret_cast<char*>(&headerSize), sizeof(headerSize), 0);
        logger.DebugLog("Size of header %i", headerSize);

        std::vector<char> buffer(headerSize); // SIZE OF THE HEADER

        int bytesReceived = recv(clientSocket, buffer.data(), buffer.size(), 0); // THE ACTUAL HEADER
        if (bytesReceived == -1 || bytesReceived == 0) {
            logger.ErrorLog("RECV Failed");
            logger.ErrorLog("Connection closed by client");
            exit(EXIT_FAILURE);
        } else {
            logger.DebugLog("Recived %i bytes", bytesReceived);
            //std::cout.write(buffer.data(), bytesReceived);  // Print received data
            //std::cout << std::endl;

            std::string receivedData(buffer.begin(), buffer.begin() + bytesReceived);
            nlohmann::json jsonData = nlohmann::json::parse(receivedData); // THE JSON HEADER
            int chunk_size = jsonData["chunk_size"];
            std::vector<char> chunk(chunk_size);

            recv(clientSocket, chunk.data(), chunk_size, 0);

            return {chunk, jsonData};
            
        }
    }
};
#endif
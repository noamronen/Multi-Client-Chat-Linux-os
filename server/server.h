//
// Created by noam on 12/10/2021.
//

#ifndef BASIC_SERVER_SERVER_H
#define BASIC_SERVER_SERVER_H
#pragma once
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <thread>
#include <pthread.h>


using namespace std;

#pragma warning(disable:4996)

class server
{
private:
    int server_socket;
    std::vector<int> clients_vec;
    //SOCKET clients_arr[5];
    std::vector<std::thread>client_threads;
    //std::thread client_threads[5];
    struct sockaddr_in server_address;
    int numOfClients = 0;
public:
    server();
    void broadcast(int client_socket, char buffer[1024]);
    void recieve(int client_socket);
    void openChat();
    void closeServer();
};
#endif //BASIC_SERVER_SERVER_H

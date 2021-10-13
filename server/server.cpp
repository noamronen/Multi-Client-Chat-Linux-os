//
// Created by noam on 12/10/2021.
#include "server.h"
using namespace std;

#pragma warning(disable:4996)



server::server()
{
    //define the address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    //creating the socket
    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket < 0)
    {
        printf("server socket creation failed \n");
    }
    else
    {
        printf("server socket creation successfull \n");
    }

    //bind
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) <0)
    {
        printf("binding failed \n");
    }
    else
    {
        printf("binding successfull \n");
    }

    //listen
    if (listen(server_socket, 5) <0)
        printf("listening failed \n");
    else
        printf("listening successfull \n");

}


void server::recieve(int client_socket)
{
    char RecvBuffer[1024];
    while (true)
    {

        if (recv(client_socket, RecvBuffer, 1024, 0) >=0)
        {

            broadcast(client_socket, RecvBuffer);

        }


    }
}

void server::openChat()
{
    struct sockaddr_in client_addr;
    int iclient_addr = sizeof(client_addr);
    while (true)
    {
        int new_client;
        new_client = accept(server_socket, (struct sockaddr *)&client_addr, reinterpret_cast<socklen_t *>(&iclient_addr));//?
        //accept
        if (new_client >=0)
        {
            clients_vec.push_back(new_client);
            client_threads.push_back(thread(&server::recieve, this, clients_vec.back()));
        }
        /*
        for (int i = 0;i < numOfClients;i++)
        {
            client_threads[i].join();
        }
        */

    }
}
void server::broadcast(int client_socket, char buffer[1024])
{
    for (auto i : clients_vec)
    {
        if(i!=client_socket)
            send(i, buffer, strlen(buffer)+1, 0);
    }
}






void server::closeServer()
{
    //close
    if (close(server_socket)<0)
    {
        printf("closing failed \n");
    }
    else
    {
        printf("closing successfull \n");
    }
}

//


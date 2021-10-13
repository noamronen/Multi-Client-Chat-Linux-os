#pragma once
#include "Client.h"

using namespace std;

int main()
{
    Client client = Client();
    client.openChat();
    client.closeClient();
    return 0;
}

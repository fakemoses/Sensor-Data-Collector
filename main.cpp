#include "udp_client.h"
#include "data_recorder.h"
#include <iostream>


/// @brief Request data from socket server and append the file into a file for data collection purposes
/// @param argc 
/// @param argv 
/// @return 
int main(int argc, char const *argv[])
{
    std::string filename = "data.txt";
    std::string serverAddress = "192.168.0.20";
    int serverPort = 8090;

    udp_client_server::udp_client client(serverAddress, serverPort);
    DataRecord::DataRecorder writer(filename);

    char msg[] = "Request for data\n";

    client.send(msg, sizeof(msg));

    char receivedMsg[1024];
    client.receive(receivedMsg, sizeof(receivedMsg));

    writer.appendToFile(receivedMsg);

    return 0;
}

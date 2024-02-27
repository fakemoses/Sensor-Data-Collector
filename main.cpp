#include "UdpClient.h"
#include "DataRecorder.h"
#include <iostream>
#include <thread>

/// @brief Request data from socket server and append the file into a file for data collection purposes
/// @param argc
/// @param argv
/// @return
int main(int argc, char const *argv[])
{
    std::string filename = "data.txt";
    // Another solution would be scanning the whole network
    // and look for ESP in the string of the hostnames
    std::string serverAddress = "192.168.0.20";
    int serverPort = 8090;

    udp_client_server::UdpClient client(serverAddress, serverPort);
    DataRecord::DataRecorder writer(filename);

    char msg[] = "Request for data\n";

    const int duration_hours = 24;
    const int interval_seconds = 60;

    // Calculate total duration in seconds
    const int total_duration_seconds = duration_hours * 3600;

    // Loop for 24 hours
    for (int i = 0; i < total_duration_seconds; i += interval_seconds)
    {
        int sent = client.send(msg, sizeof(msg));

        if (sent != -1)
        {
            char receivedMsg[1024];
            int res = client.receive(receivedMsg, sizeof(receivedMsg));

            if (res != 0 || res != -1)
                writer.appendToFile(receivedMsg);
        } else
            break;

        // Sleep for 60 seconds
        std::this_thread::sleep_for(std::chrono::seconds(interval_seconds));
    }

    std::cout << "Finished executing for 24 hours." << std::endl;

    return 0;
}

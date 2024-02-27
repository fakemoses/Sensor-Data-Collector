#include "UdpClient.h"

namespace udp_client_server
{
    /// @brief Constructor for UDP client. Credit to: https://linux.m2osw.com/c-implementation-udp-clientserver
    /// @param addr 
    /// @param port 
    UdpClient::UdpClient(const std::string &addr, int port)
        : f_port(port), f_addr(addr)
    {
        char decimal_port[16];
        snprintf(decimal_port, sizeof(decimal_port), "%d", f_port);
        decimal_port[sizeof(decimal_port) / sizeof(decimal_port[0]) - 1] = '\0';
        struct addrinfo hints;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_DGRAM;
        hints.ai_protocol = IPPROTO_UDP;
        int r(getaddrinfo(addr.c_str(), decimal_port, &hints, &f_addrinfo));
        if (r != 0 || f_addrinfo == NULL)
        {
            throw udp_client_server_runtime_error(("invalid address or port: \"" + addr + ":" + decimal_port + "\"").c_str());
        }
        f_socket = socket(f_addrinfo->ai_family, SOCK_DGRAM | SOCK_CLOEXEC, IPPROTO_UDP);
        if (f_socket == -1)
        {
            freeaddrinfo(f_addrinfo);
            throw udp_client_server_runtime_error(("could not create socket for: \"" + addr + ":" + decimal_port + "\"").c_str());
        }
    }

    UdpClient::~UdpClient()
    {
        freeaddrinfo(f_addrinfo);
        close(f_socket);
    }

    /// @brief get socket 
    /// @return 
    int UdpClient::get_socket() const
    {
        return f_socket;
    }

    /// @brief get port value
    /// @return 
    int UdpClient::get_port() const
    {
        return f_port;
    }

    /// @brief get client address
    /// @return 
    std::string UdpClient::get_addr() const
    {
        return f_addr;
    }

    /// @brief Send message to the server
    /// @param msg 
    /// @param size 
    /// @return 
    int UdpClient::send(const char *msg, size_t size)
    {
        int sent = sendto(f_socket, msg, size, 0, f_addrinfo->ai_addr, f_addrinfo->ai_addrlen);

        if (sent == -1)
        {
            std::cerr << "Error occured while sending the request: " << errno << std::endl;
            return -1;
        }
        
        return sent; 
    }

    /// @brief Receive response from the server
    /// @param msg 
    /// @param size 
    /// @return 
    int UdpClient::receive(char *msg, size_t size)
    {
        int response = recvfrom(f_socket, msg, size,  
                MSG_WAITALL, f_addrinfo->ai_addr, 
                &f_addrinfo->ai_addrlen);
        
        if (response == 0 )
        {
            std::cout << "no messages received" << std::endl;
            return 0;
        } else if (response == -1)
        {
            std::cerr << "Error occured: " << errno << std::endl;
            return -1;
        }
        
        return response;
    }

}
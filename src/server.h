#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <ctime>
#include <thread>
#include <cstring>
#include <fcntl.h>
#include <string>
#include <fstream>
#include "router.h"

class httpServer
{
private:
    int socketFD; // file descriptor for the socket
    sockaddr_in sAddr; // structure to hold the IP address and port number
    int sAddrLen; // address of sAddr, to be used in accept function
    Router & routingTable; // reference to the routing table to be used for routings

    inline void log(std::string const & str); // simple logger function

    // function to respond to a request based on received parameters
    void respond(int newSocket);

    // function to send the data back to the client
    bool sendBack(int socket, std::string file);
public:
    // constructor, just inits the server address and does binding
    // pass reference to routing table, IP address and port address
    httpServer(Router & table, std::string const & IP, short port);

    //function to start the server
    void startServer();
};

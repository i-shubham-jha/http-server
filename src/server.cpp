#include "server.h"
#include <cstring>
#include <sstream>
#include <sys/socket.h>
#include <sys/types.h>

// simple logger function
void httpServer::log(std::string const & str)
{
    // TBD: create time stamps as "[date time]" without a new line at the end
    struct tm t;
    time_t now = time(0);
    char * tt = ctime(&now);
    std::cout << "\n" << tt << str << std::endl;
}

// constructor
httpServer::httpServer(Router & table, std::string const & IP, short port) : routingTable(table)
{
    // init the sAddr structure with addresses in proper representation
    sAddr.sin_family = AF_INET; // for IPv4
    sAddr.sin_port = htons(port);
    sAddr.sin_addr.s_addr = inet_addr(IP.c_str());
    sAddrLen = sizeof(sAddr);
    log("Initialisations of structure done");



    // CREATING A NEW SOCKET
    socketFD = socket(AF_INET, SOCK_STREAM, 0);

    if(socketFD == -1)
    {
        log("Failed to create socket\nExiting...");
        exit(1);
    }
    else
    {
        std::ostringstream str;
        str << "Socket successfully created with FD = " << socketFD;
        log(str.str());
    }
    // SOCKET CREATION DONE



    // BINDING THE SOCKET
    if( bind(socketFD, (sockaddr *)&sAddr, sAddrLen) == -1 )
    {
        std::ostringstream str;
        str << "Failure in binding socket to port " << ntohs(sAddr.sin_port);
        log(str.str() + "\nExiting...");
        exit(1);
    }
    else
    {
        std::ostringstream str;
        str << "Socket successfully bound to port " << ntohs(sAddr.sin_port);
        log(str.str());
    }
    // SOCKET BINDING DONE
}

// function to start the server and start accepting the connections
void httpServer::startServer()
{
    //STARTING LISTENING ON SOCKET
    if(listen(socketFD, 25) == -1)
    {
        log("failed to start listening\nExiting...");
        exit(1);
    }
    else
    {
        std::ostringstream str;
        str << ntohs(sAddr.sin_port);
        log("Server started listening on port " + str.str());
    }
    //LISTENING HAS STARTED

    // ACCEPTING NEW CONNECTIONS AND SERVING THEM
    while(true)
    {
        int newSocket = accept(socketFD, (sockaddr *) &sAddr , (socklen_t *) &sAddrLen );
        log("Accepted a new request");
        // creating a new thread for the respond function,
        // so that we don't have to wait for the response to finish
        // meanwhile we can start entertaining other requests
        // NOT worrying about any synchronisation problems as just reading happening in this projectk
        std::thread threadObj(&httpServer::respond, this, newSocket);
        threadObj.detach();
    }
}

// function to respond to a request based on received parameters
void httpServer::respond(int newSocket)
{
    log("Inside a new thread");
    // reading the request header
    char request[4096] = "";
    read(newSocket, request, sizeof(request));

    // finding the route
    // just use strtok() to find the second token with space charcter as delimiter
    char * route = strtok(request, " "); // the METHOD is returned here
    route = strtok(NULL, " " ); // the ROUTE is returned here

    if(sendBack(newSocket, routingTable.find(route)))
    {
        log("Data sent successfully");
    }
    else
    {
        log("Failure in sending data");
    }

    close(newSocket);
}

// function to send the data back to the client
bool httpServer::sendBack(int socket, std::string file )
{
    std::ifstream t(file);

    if(!t)
    {
        log("failure in opening file: " + file);
        exit(1);
    }

    std::stringstream buffer;
    buffer << t.rdbuf();


    std::ostringstream str;
    str << "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " << buffer.str().size() << "\n\n" << buffer.str();

    if(write(socket, str.str().c_str(), str.str().size()) == -1)
    {
        return false;
    }
    else
    {
        return true;
    }
}


// the main driver file of the server
#include "./src/server.h"

int main ()
{
    Router routingTable;
    routingTable.add("/home", "./static/index.html");
    routingTable.add("/about", "./static/about.html");
    routingTable.add("/contact", "./static/contact.html");
    httpServer server0(routingTable, "0.0.0.0", 5555);
    server0.startServer();
}

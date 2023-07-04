# http-server
This is a simple HTTP Server developed using the UNIX Socket API. Routing functionality is also provided.
## Compilation
- Clone this repo to your local machine.
- Open your terminal in the same directory containing `main.cpp`
- Enter the following command
```
g++ main.cpp ./src/*.cpp -o main
```
This will create the final executable named as `main`.


## Usage
**Note: This is just an educational project, and I do NOT recommend it for production use.**
- Port number can be specified in the constructor of `httpServer` object.
- Create a routing table in the `main.cpp` file.
- Add some routes to it.
- The routes should also specify the files to be served for those routes.
- Those files need to be created in `./static/` directory.
- If a non-existent route is entered, the file `./static/404.html` is served.
- Logs are printed on the terminal along with their timestamps for easy debugging.

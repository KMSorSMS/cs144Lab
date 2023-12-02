#include "socket.hh"

#include <cstdlib>
#include <iostream>
#include <span>
#include <string>

using namespace std;

void get_URL( const string& host, const string& path )
{
  // printf( "path is : %s\n", path.c_str() );
  // printf( "host is : %s\n", host.c_str() );
  // cerr << "Function called: get_URL(" << host << ", " << path << ")\n"; // For sticklers: this cerr is OK.
  // cerr << "Warning: get_URL() has not been implemented yet.\n";
  // *** implement get_URL ***
  // // 1. make the host to ip address, no need to do this.
  // string hostIP = host;
  // Address addr( host, "http" );
  // hostIP = addr.ip();

  // 2. create a socket,we need to use the socket to connect to the server,this is TCP socket
  TCPSocket socket;//create a TCP socket, havn't connect to the server yet
  // 3. connect to the server
  socket.connect( Address( host, "http" ) );//connect to the server
  // 4. send the request to the server
  string request = "GET " + path + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n";
  socket.write( request );//send the request to the server
  // 5. read the response from the server
  //init a buffer to accept the response
  string responseTemp, response;
  while (socket.eof() == false)
  {  
    socket.read( responseTemp );//read the response from the server
    response += responseTemp;
  }
  
  // 6. print the response to the terminal
  cout << response;
}

int main( int argc, char* argv[] )
{
  try {
    if ( argc <= 0 ) {
      abort(); // For sticklers: don't try to access argv[0] if argc <= 0.
    }

    auto args = span( argv, argc );

    // The program takes two command-line arguments: the hostname and "path" part of the URL.
    // Print the usage message unless there are these two arguments (plus the program name
    // itself, so arg count = 3 in total).
    if ( argc != 3 ) {
      cerr << "Usage: " << args.front() << " HOST PATH\n";
      cerr << "\tExample: " << args.front() << " stanford.edu /class/cs144\n";
      return EXIT_FAILURE;
    }

    // Get the command-line arguments.
    const string host { args[1] };
    const string path { args[2] };

    // Call the student-written function.
    get_URL( host, path );
  } catch ( const exception& e ) {
    cerr << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
#include <sys/socket.h> //For Socket functions
#include <netinet/in.h> // For socketaddr_in
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>

int main() {

  int sockcl = socket(AF_INET, SOCK_STREAM, 0);
  if (sockcl == -1) {
    std::cout << "Failed to create client socket. Error Number: " << errno << std::endl;
  }
  
  sockaddr_in sockaddr;
  sockaddr.sin_family = AF_INET;
  sockaddr.sin_addr.s_addr = INADDR_ANY;
  sockaddr.sin_port = htons(9999);

  if (connect(sockcl, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
    std::cout << "Failed to connect to server on port 9999. Error Number: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }

  const char* message ="Hello, server!";
  send(sockcl, message, strlen(message), 0);

  close(sockcl);
}

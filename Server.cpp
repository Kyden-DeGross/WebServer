#include <sys/socket.h> //For Linux Socket Functions
#include <netinet/in.h> // For socketaddr_in structure
#include <cstdlib>
#include <iostream> // For cout
#include <unistd.h> // For read

int main() {
  // create a socket (Ipv6, TCP) 
  // IPv6 is the internet protocol that is specific to the router that the
  // server is connected to. 
  // TCP is the communication protocol
  // Transmission control protocol

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    std::cout << "Failed to create socket. Error Number: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }
  
  // Listen to port 9999 on any address
  sockaddr_in sockaddr;
  sockaddr.sin_family = AF_INET;
  sockaddr.sin_addr.s_addr = INADDR_ANY;
  //htons converts number to network byte order
  sockaddr.sin_port = htons(9999);

  if (bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
    std::cout << "Failed to bind to port 9999. Error Number: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }

  // Start listening. Hold at most 10 connections in the queue
  if (listen(sockfd, 10) <0) {
    std::cout << "Failed to listen on socket. Error Number: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }

  //Grab a connection from the queue
  auto addrelen = sizeof(sockaddr);
  int connection = accept(sockfd, (struct sockaddr*)&sockaddr, (socklen_t*)&addrelen);
  if (connection <0) {
    std::cout << "Failed to grab connection. Error Number: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }

  //Read from the connection 
  char buffer[100];
  auto bytesRead = read(connection , buffer, 100);
  std:: cout << "The message was: " << buffer;
  
  // Send a message in return to the connection
  std:: string response = "Good talking to you\n";
  send(connection, response.c_str(), response.size(), 0);
  
  //Close the connection
  close(connection);
  close(sockfd);
}

//
// Created by sheid on 07.04.21.
//

#include "Socket.h"
#include <cstdlib>
#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <thread>
#include <unistd.h>

using std::string;

Socket::Socket(const char *SockPath) {
  // https://stackoverflow.com/a/37714620/13310191

  // create socket
  sockaddr_un Address;
  Sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
  SocketPath =SockPath;
  if (Sockfd == -1) {
    std::cerr << "could not create unix socket" << std::endl;
    exit(EXIT_FAILURE);
  }

  Address.sun_family = AF_UNIX;
  strcpy(Address.sun_path, SocketPath);

  // connect to socket
  unlink(SocketPath);
  if (bind(Sockfd, (sockaddr *)&Address, sizeof(Address)) == -1) {
    std::cerr << "could not bind to '" << SocketPath << "'" << std::endl;
    close(Sockfd);
    exit(EXIT_FAILURE);
  }

  /* Prepare for accepting connections. The backlog size is set
   * to 20. So while one request is being processed other requests
   * can be waiting. */
  if (listen(Sockfd, 20) == -1) {
    std::cerr << "could not listen to '" << SocketPath << "'" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (accept(Sockfd, NULL, NULL) == -1) {
    std::cerr << "could not accept connection to '" << SocketPath << "'"
              << std::endl;
    exit(EXIT_FAILURE);
  }
}

bool Socket::read(string &Out) {
  int N;
  const size_t Buflen = 200;
  char RetValue[Buflen + 1];
  Out = "";

  do {
    N = ::read(Sockfd, RetValue, Buflen);
    if (N < 0) {
      std::cout << "socket read failed" << std::endl;
      exit(EXIT_FAILURE);
    } else {
      Out.append(RetValue);
    }
  } while (N > 0);
  std::cout << Out << std::endl;
  return Out == "done";
}

bool Socket::write(string Data) {
  if (::write(Sockfd, Data.c_str(), Data.size()) == -1) {
    std::cout << "Error" << std::endl;
    close(Sockfd);
    exit(EXIT_FAILURE);
  }
  return true;
}
Socket::~Socket() {
  unlink(SocketPath);
}

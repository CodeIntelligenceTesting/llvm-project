//
// Created by sheid on 07.04.21.
//

#ifndef COMPILERRT_SOCKET_H
#define COMPILERRT_SOCKET_H
#include <string>

using std::string;

class Socket {
public:
  Socket(const char *Path);
  bool read(string &Out);
  bool write(string Data);
  ~ Socket();

private:
  int Sockfd;
  const char* SocketPath;
};

#endif // COMPILERRT_SOCKET_H

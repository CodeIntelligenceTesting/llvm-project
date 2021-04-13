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
  bool close();
  ~ Socket();

private:
  int Sockfd;
  int Conn;
  const char* SocketPath;
};

#endif // COMPILERRT_SOCKET_H

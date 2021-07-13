//
// Created by sheid on 07.04.21.
//

#ifndef COMPILERRT_SOCKET_H
#define COMPILERRT_SOCKET_H
#include <string>

using std::string;
typedef struct{
      int mutRep;
      std::string fileContents;
    } dataOut;
class Socket {
public:
  
  Socket(const char *Path);
  bool read(dataOut *Out);
  bool write(string Data);
  bool close();
  ~ Socket();
  

private:
  int Sockfd;
  int Conn;
  const char* SocketPath;
};

#endif // COMPILERRT_SOCKET_H

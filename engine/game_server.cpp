#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Socket {
public:
  ~Socket() { Close(); }

  bool Open(unsigned short port) {
    handle_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (handle_ <= 0) {
      printf("failed to create socket\n");
      return false;
    }

    sockaddr_in socket_address;
    memset((char *)&socket_address, 0, sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = INADDR_ANY;
    socket_address.sin_port = htons(port);
    if (bind(handle_, reinterpret_cast<sockaddr *>(&socket_address),
             sizeof(sockaddr_in)) < 0) {
      printf("failed to bind socket\n");
      return false;
    }

    int non_blocking = 1;
    if (fcntl(handle_, F_SETFL, O_NONBLOCK, non_blocking) == -1) {
      printf("failed to set non-blocking\n");
      return false;
    }

    return true;
  }

  std::string Recieve() {
      constexpr int kMaxRecieveSize = 256;
      char recv_buffer[kMaxRecieveSize];
      sockaddr_in from_socket;
      socklen_t from_length = sizeof(from_socket);
      int bytes =
          recvfrom(handle_, recv_buffer, kMaxRecieveSize, 0,
                   reinterpret_cast<sockaddr *>(&from_socket), &from_length);

      if (bytes <= 0) {
        return "";
      }

      unsigned int from_address = ntohl(from_socket.sin_addr.s_addr);
      unsigned int from_port = ntohs(from_socket.sin_port);

      std::cout << from_address << std::endl;
      std::cout << from_port << std::endl;

    return recv_buffer;
  }

  bool Send(const sockaddr &address, const std::string &data) {
    int sent_bytes = sendto(handle_, data.c_str(), data.size(), 0, &address,
                            sizeof(sockaddr_in));
    if (sent_bytes != data.size()) {
      printf("failed to send\n");
      return false;
    }

    return true;
  }

  bool Close() { return close(handle_); }

private:
  int handle_;
};

class GameServer {
public:
  bool Run(ushort port) {
    Socket server_socket;
    if (!server_socket.Open(port)) {
      printf("failed to create socket!\n");
      return false;
    }

    while (true) {
      std::string test = server_socket.Recieve();
      if (!test.empty()) {
        std::cout << test << std::endl;
      }
    }

    return true;
  }
};

int main(int argc, char **argv) {
  GameServer killer_queen_server;
  killer_queen_server.Run(3000);
  return 0;
};

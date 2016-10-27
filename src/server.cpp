#include <iostream>
#include <unordered_map>
#include <memory>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>

#include "player.h"
#include "character.h"
#include "util.h"

namespace killerqueen {

class Socket {
public:
  ~Socket() { Close(); }

  bool Open(unsigned short port) {
    handle_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (handle_ <= 0) {
      printf("Failed to create socket.\n");
      return false;
    }

    sockaddr_in socket_address;
    memset((char *)&socket_address, 0, sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = INADDR_ANY;
    socket_address.sin_port = htons(port);
    if (bind(handle_, reinterpret_cast<sockaddr *>(&socket_address),
             sizeof(sockaddr_in)) < 0) {
      printf("Failed to bind socket.\n");
      return false;
    }

    int non_blocking = 1;
    if (fcntl(handle_, F_SETFL, O_NONBLOCK, non_blocking) == -1) {
      printf("Failed to set non-blocking.\n");
      return false;
    }
    return true;
  }

  std::string Receive(unsigned short *from_address, unsigned short *from_port) {
    if (from_address == nullptr || from_port == nullptr) {
      printf("From address or port is nullptr.\n");
      return "";
    }
    char recv_buffer[kMaxReceiveDataSize];
    sockaddr_in from_socket;
    socklen_t from_length = sizeof(from_socket);
    int bytes =
        recvfrom(handle_, recv_buffer, kMaxReceiveDataSize, 0,
                 reinterpret_cast<sockaddr *>(&from_socket), &from_length);

    if (bytes <= 0) {
      return "";
    }

    *from_address = ntohl(from_socket.sin_addr.s_addr);
    *from_port = ntohs(from_socket.sin_port);
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

  static const int kMaxReceiveDataSize = 256;
};

class Connection {
public:
  struct Hash {
    std::size_t operator()(const Connection &connection) const {
      return (std::hash<unsigned short>()(
                  connection.GetAddress() ^
                  (std::hash<unsigned short>()(connection.GetPort()) << 1)) >>
              1);
    }
  };

  Connection(unsigned short address, unsigned short port)
      : address_(address), port_(port) {}

  bool operator==(const Connection &rhs) const {
    return address_ == rhs.GetAddress() && port_ == rhs.GetPort();
  }

  unsigned short GetAddress() const { return address_; }
  unsigned short GetPort() const { return port_; }

private:
  unsigned short address_;
  unsigned short port_;
};

class Server {
public:
  bool Run(ushort port) {
    Socket server_socket;
    if (!server_socket.Open(port)) {
      printf("failed to create socket!\n");
      return false;
    }

    while (true) {
      unsigned short from_address;
      unsigned short from_port;
      std::string received_data =
          server_socket.Receive(&from_address, &from_port);
      if (!received_data.empty()) {
        continue;
      }

      Connection new_connection(from_address, from_port);
      if (players_by_connection_.find(new_connection) ==
          players_by_connection_.end()) {
        players_by_connection_.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(std::move(new_connection)),
            std::forward_as_tuple(Point{0, 0}, std::make_unique<Worker>(),
                                  Team::RED));
      } else {
        // Parse request.
      }
    }

    return true;
  }

private:
  std::unordered_map<Connection, Player, Connection::Hash>
      players_by_connection_;
};

} // namespace killerqueen

int main(int argc, char **argv) {
  killerqueen::Server killer_queen_server;
  killer_queen_server.Run(3000);
  return 0;
};

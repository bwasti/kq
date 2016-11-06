#include <vector>

#include "gateway.h"
#include "platform.h"

namespace killerqueen {

class MapSpec {

public:
  std::vector<Platform> GetPlatforms() {
    return platforms_;
  }
  std::vector<Gateway> GetGateways() {
    return gateways_;
  }
  void SetPlatforms(std::vector<Platform> platforms) {
    platforms_ = platforms;
  }
  void SetGateways(std::vector<Gateway> gateways) {
    gateways_ = gateways;
  }

private:
  std::vector<Platform> platforms_;
  std::vector<Gateway> gateways_;
};
} // namespace killerqueen

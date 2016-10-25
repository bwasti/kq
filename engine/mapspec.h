#include <vector>

namespace killerqueen {

class MapSpec {

public:
  std::vector<Platform> getPlatforms() {
    return platforms;
  }
  std::vector<Gateway> getGateways() {
    return gateways;
  }
  setPlatforms(std::vector<Platform> platforms) {
    this.platforms = platforms;
  }
  setGateways(std::vector<Gateway> gateways) {
    this.gateways = gateways;
  }

private:
  std::vector<Platform> platforms;
  std::vector<Gateway> gateways;
}
} // namespace killerqueen

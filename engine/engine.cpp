#include <vector>
#include <string>

#include "util.h"
#include "character.h"
#include "player.h"

namespace killerqueen {

class Engine {

  void Setup() {
    const int kTeamWorkerCount = 5;

    // Add players.
    players.emplace_back(Point{0, 0}, std::make_unique<Queen>(), Team::RED);
    for (int i = 0; i < kTeamWorkerCount; ++i) {
      players.emplace_back(Point{0, 0}, std::make_unique<Worker>(), Team::RED);
    }

    players.emplace_back(Point{0, 0}, std::make_unique<Queen>(), Team::BLUE);
    for (int i = 0; i < kTeamWorkerCount; ++i) {
      players.emplace_back(Point{0, 0}, std::make_unique<Worker>(), Team::BLUE);
    }

    for (Player& player : players) {
      player.SetShouldMoveCallback(
          [](const Player &player_to_move, const Point &new_position) -> bool {
            // if (the_map.HasPlatformAt(new_position)) {
            //   return false;
            // }
            // if (the_map.HasBerryAt(new_position)) {
            //  Berries *collided_berries = the_map.GetBerrysAt(new_position)
            //  if (player is worker && collied_berries.berry > 0) {
            //    player.state = berry
            //    collided_berries--;
            //  }
            //  return true;
            // }
            // if (the_map.HasGatewayAt(new_position)) {
            //   Gateway* collided_gateway = the_map.GetGatewayAt(new_position)
            //   if (player is worker
            //       && collied_gateway.IsEmpty()
            //       && collided_gateway.GetColor() == Player.getTeam()
            //       && player.state == BERRY) {
            //     player.state = evolving
            //   }
            // }
            return true;
          });
    }
  }

  std::string GetState() {
    // Return json object representing engine state.
    return "";
  }

private:
  std::vector<Player> players;
};

} // namespace killerqueen

int main(int argc, char **argv) { return 0; }

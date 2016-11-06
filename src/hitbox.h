#include "util.h"

namespace killerqueen {

class Hitbox {

public:
  Hitbox(Point bl, Point tr) {
    bottom_left_ = bl;
    top_right_ = tr;
  }
  bool HasCollision(Point bl, Point tr) {
    return bl.x >= bottom_left_.x &&
           tr.x <= tr.x &&
           bl.y >= bottom_left_.y &&
           tr.y <= top_right_.y;
  }

private:
  Point bottom_left_;
  Point top_right_;
};
} // namespace killerqueen
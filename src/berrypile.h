#include "hitbox.h"

namespace killerqueen {

class BerryPile {

public:
  BerryPile(int max_berries, Hitbox &hitbox):
    num_berries_(max_berries), hitbox_(hitbox) {
  }
  Hitbox GetHitbox() { return hitbox_; }
  Size GetSize() { return size_; }
  Point GetPos() { return pos_; }

  bool TryToTakeBerry() {
    if (num_berries_ > 0) {
      num_berries_--;
      return true;
    }
    return false;
  }

  void SetSize(Size size) { size_ = size; }
  void SetPos(Point pos) { pos_ = pos; }

private:
  int num_berries_;
  Hitbox hitbox_;
  Point pos_; // bottom left corner of gateway
  Size size_;
};
} // namespace killerqueen
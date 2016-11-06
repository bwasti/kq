#include "hitbox.h"

namespace killerqueen {

class Gateway {

  enum class GatewayType {HASTE, FLY};

public:
  Gateway(GatewayType gateway_type, Hitbox &hitbox): gateway_type_(gateway_type), hitbox_(hitbox) {
  }
  GatewayType GetGatewayType() { return gateway_type_; }
  Hitbox GetHitbox() { return hitbox_; }
  Size GetSize() { return size_; }
  Point GetPos() { return pos_; }

  void SetSize(Size size) { size_ = size; }
  void SetPos(Point pos) { pos_ = pos; }

private:
  GatewayType gateway_type_;
  Hitbox hitbox_;
  Point pos_; // bottom left corner of gateway
  Size size_;
};
} // namespace killerqueen
namespace killerqueen {

class Gateway {

  enum class GatewayType {HASTE, FLY};

public:
  Gateway(GatewayType gateway_type) {
    this->gateway_type_ = gateway_type;
  }
  GatewayType GetGatewayType() { return gateway_type_; }
  Hitbox GetHitbox() { return hitbox_; }
  int GetSize() { return size_; }
  int GetPos() { return pos_; }

  void SetSize(Size size) { this.size_ = size; }
  void SetPos(Point pos) { this.pos_ = pos; }

private:
  GatewayType gateway_type_;
  Hitbox hitbox_;
  Point pos_; // bottom left corner of gateway
  Size size_;
};
} // namespace killerqueen
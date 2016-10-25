namespace killerqueen {

class Platform {

public:
  int GetStartX() { return start_x; }
  int GetStartY() { return start_y; }
  int GetWidth() { return width; }
  int GetHeight() { return height; }

  void SetStartX(int start_x) { this->start_x = start_x; }
  void SetStartY(int start_y) { this->start_y = start_y; }
  void SetWidth(int width) { this->width = width; }
  void SetHeight(int height) { this->height = height; }

private:
  int start_x, start_y, width, height;
};
} // namespace killerqueen

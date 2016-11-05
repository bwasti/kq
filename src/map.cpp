#include <vector>

#include "platform.h"

namespace killerqueen {

class Map {

public:

  Map() {
    InitializeMap();
  }

  ~Map() {
    DeleteMap();
  }

  void LoadMap(std::vector<Platform> platforms) {
    for (Platform &platform : platforms) {
      LoadPlatform(platform);
    }
  }

  char** GetMap() {
    return map;
  }

  bool HasPlatformAt(int width, int height) {
    return map[width][height];
  }

private:
  static const int WIDTH = 32;
  static const int HEIGHT = 64;
  char** map;

  void InitializeMap() {
    map = new char*[WIDTH];
    for (int i = 0; i < WIDTH; i++) {
      map[i] = new char[HEIGHT];
    }
  }

  void DeleteMap() {
    for (int i = 0; i < WIDTH; i++) {
      delete [] map[i];
    }
  }

  void LoadPlatform(Platform platform) {
    for (int w = platform.GetStartX(); w < platform.GetWidth(); w++) {
      for (int h = platform.GetStartY(); h < platform.GetHeight(); h++) {
        map[w][h] = 1;
      }
    }
  }
};
} // namespace killerqueen

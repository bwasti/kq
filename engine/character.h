#pragma once

namespace killerqueen {

class Character {
public:
  virtual Size GetSize() const = 0;
  virtual std::string GetCharacterName() const = 0;
};

class Worker: public Character {
public:
  Size GetSize() const override {
    return Size{0, 0};
  }

    std::string GetCharacterName() const override {
    return "worker";
  }
};

class Soldier: public Character {
public:
  Size GetSize() const override {
    return Size{0, 0};
  }

  std::string GetCharacterName() const override {
    return "soldier";
  }
};

class Queen: public Character {
public:
  Size GetSize() const override {
    return Size{0, 0};
  }

  std::string GetCharacterName() const override {
    return "queen";
  }
};

}  // namespace killerqueen

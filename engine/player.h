#pragma once

#include <memory>
#include <functional>

#include "character.h"
#include "util.h"

namespace killerqueen {

enum class Team { RED, BLUE };
enum class PlayerState { NORMAL, BERRY };

class Player {
public:
  Player(const Point &start_position,
         std::unique_ptr<Character> start_character, const Team &team)
      : team_(team), position_(start_position), current_character_(std::move(start_character)) {}

  void SetPosition(const Point &position) {
    if (should_move_callback_(*this, position)) {
      position_ = position;
    }
  }

  Point GetPosition() const;

  void SetShouldMoveCallback(std::function<bool(const Player&, const Point&)> should_move) {
    should_move_callback_ = should_move;
  }

  Size GetSize() const {
    return current_character_->GetSize();
  }

  std::string GetCharacterName() const {
    return current_character_->GetCharacterName();
  }

  void SetCharacter(std::unique_ptr<Character> character) {
    current_character_ = std::move(character);
  }

private:
  Team team_;
  Point position_;
  Size size_;
  Point velocity_;
  std::unique_ptr<Character> current_character_;
  std::function<bool(const Player&, const Point&)> should_move_callback_;
};

}  // namspace killerqueen

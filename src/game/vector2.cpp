#include "vector2.h"

namespace game {
vector2 vector2::operator+(const vector2& rhs) const { return {x + rhs.x, y + rhs.y}; }

bool vector2::operator==(const vector2& rhs) const { return x == rhs.x && y == rhs.y; }
} // namespace game

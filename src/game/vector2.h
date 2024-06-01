#pragma once

namespace game {

/**
 * 2-variable integral column-vector.
 *
 * (a point in 2D space, a direction, etc.)
 */
struct vector2 {
    vector2 operator+(const vector2& rhs) const;
    bool operator==(const vector2& rhs) const;
    int x;
    int y;
};

} // namespace game

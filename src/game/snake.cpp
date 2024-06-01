#include "snake.h"
#include "game/environment.h"
#include "game/vector2.h"

namespace game {

// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------
snake::snake(const vector2& start, unsigned int interval) : update_interval{interval} {
    segments.push_back({start.x, start.y});
}

snake::snake(const vector2& start) : snake{start, 60} {}

// -----------------------------------------------------------------------------
// Commands
// -----------------------------------------------------------------------------

// Update
void snake::update(float delta, const environment& env) {
    static unsigned int ticks = 0;
    ticks += delta * 1000;
    if (ticks >= update_interval) {
        ticks = 0;
        update_one_tick(env);
    }
}

// Real Update
void snake::update_one_tick(const environment& env) {
    if (out_of_bounds(env) || eating_self()) {
        die();
    }

    if (head() + velocity == env.apple) {
        eat();
        move_and_grow();
    } else {
        move();
    }

    velocity_change_enabled = true;
}

// Left
void snake::left() {
    if (velocity_change_enabled && velocity.x == 0) {
        velocity                = {-1, 0};
        velocity_change_enabled = false;
    }
}

// Right
void snake::right() {
    if (velocity_change_enabled && velocity.x == 0) {
        velocity                = {1, 0};
        velocity_change_enabled = false;
    }
}

// Up
void snake::up() {
    if (velocity_change_enabled && velocity.y == 0) {
        velocity                = {0, -1};
        velocity_change_enabled = false;
    }
}

// Down
void snake::down() {
    if (velocity_change_enabled && velocity.y == 0) {
        velocity                = {0, 1};
        velocity_change_enabled = false;
    }
}

// Move
void snake::move() {
    segments.push_front(segments.front() + velocity);
    segments.pop_back();
}

// Grow
void snake::move_and_grow() { segments.push_front(segments.front() + velocity); }

// Set "eat" handler
void snake::on_eat(std::function<void()> callback) { eat = callback; }

// Set "die" handler
void snake::on_death(std::function<void()> callback) { die = callback; }

// -----------------------------------------------------------------------------
// Queries
// -----------------------------------------------------------------------------

// Head
vector2 snake::head() const { return segments.front(); }

// Tail
const std::list<vector2> snake::tail() const {
    return std::list<vector2>{std::next(segments.begin()), segments.end()};
}

// Body
const std::list<vector2> snake::body() const { return segments; }

bool snake::out_of_bounds(const environment& env) {
    vector2 subject    = head() + velocity;
    bool too_far_left  = subject.x < 0;
    bool too_far_right = env.size.x < subject.x;
    bool too_far_up    = subject.y < 0;
    bool too_far_down  = env.size.y < subject.y;
    return too_far_left || too_far_right || too_far_up || too_far_down;
}

bool snake::eating_self() {
    for (const auto& segment : tail()) {
        if (head() + velocity == segment) {
            return true;
        }
    }
    return false;
}

} // namespace game

#pragma once

#include <functional>
#include <list>

#include "environment.h"
#include "vector2.h"

namespace game {

/**
 * Abstraction of the "Snake" in the game "Snake".
 */
class snake {
  public:
    // --- Constructors

    /**
     * Construct a snake at `starting_position` that updates every
     * `update_interval` milliseconds (ticks).
     */
    snake(const vector2& starting_position, unsigned int update_interval);

    /**
     * Construct a snake at `starting_position` that updates every
     * few milliseconds (ticks) at some sane default speed.
     */
    snake(const vector2& starting_position);

    // --- Commands

    /**
     * Update as a function of time (seconds).
     */
    void update(float delta, const environment& env);

    /**
     * Set motion leftward.
     */
    void left();

    /**
     * Set motion rightward.
     */
    void right();

    /**
     * Set motion upward.
     */
    void up();

    /**
     * Set motion downward.
     */
    void down();

    /**
     * What to do when the snake "eats"?
     */
    void on_eat(std::function<void()> callback);

    /**
     * What do to when the snake "dies"?
     */
    void on_death(std::function<void()> callback);

    // --- Queries

    /**
     * Point occupied exclusively by the body.
     */
    vector2 head() const;

    /**
     * All points occupied by the body, excluding the head.
     */
    const std::list<vector2> tail() const;

    /**
     * All points accupied by the body.
     */
    const std::list<vector2> body() const;

  private:
    /**
     * Real update functions.
     *
     * Move or grow based on direction and environment.
     */
    void update_one_tick(const environment& env);

    /**
     * Move by adding a new head, reducing the size of the tail (effectively moving).
     */
    void move();

    /**
     * Move by adding a new head, without reducing the tail (effectively growing).
     */
    void move_and_grow();

    /**
     * Am I out of bounds?
     */
    bool out_of_bounds(const environment& env);

    /**
     * Am I "eating" myself?
     */
    bool eating_self();

    /**
     * Called whenever the snake "eats" an apple.
     *
     * The snake does not understand "eating", but understands the conditions
     * for it. It is thus expected that the snake notifies this function when
     * the conditions are met to do the actual handling.
     */
    std::function<void()> eat{[]() {}};

    /**
     * Called whenever the snake "dies", for whatever reason.
     *
     * The snake does not understand "death", but understands the conditions
     * for it. It is thus expected that the snake notifies this function when
     * the conditions are met to do the actual handling.
     */
    std::function<void()> die{[]() {}};

    /**
     * Segments composing the snake's body.
     *
     * Just a collection of points in 2d space.
     */
    std::list<vector2> segments;

    /**
     * The current direction the snake is moving.
     */
    vector2 velocity{1, 0};

    /**
     * How frequently the snake's motion updates.
     */
    const unsigned update_interval;

    /**
     * Locking flag (not a mutex) that prevents the snake from "eating itself".
     */
    bool velocity_change_enabled;
};

} // namespace game

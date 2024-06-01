#include <cstdlib>
#include <list>
#include <random>

#include <sos/sos.h>

#include "game/environment.h"
#include "game/snake.h"

/**
 * Random Number Generator.
 *
 * Does exactly what you think it does.
 */
class random_number_generator {
  public:
    /**
     * Specify the range, exclusive.
     */
    random_number_generator(int low, int high) {
        std::random_device random_device;
        generator    = std::mt19937{random_device()};
        distribution = std::uniform_int_distribution<>(low, high - 1);
    }

    /**
     * Call me for a random number!
     */
    int operator()() { return distribution(generator); }

  private:
    std::mt19937 generator;
    std::uniform_int_distribution<> distribution;
};

int main() {

    // Set the scale for the grid
    constexpr int scale = 16;

    // Configure the environment visible to the snake
    static game::environment environment = {
        .apple = {8, 8},
        .size  = {32, 32},
    };

    // Set up some random number generators for apple placement
    static random_number_generator rng_x(0, environment.size.x);
    static random_number_generator rng_y(0, environment.size.y);

    // Initialize SDL2
    sos::root::init({.headless = false,
                     .window   = {
                           .title = "snake",
                           .x     = 64,
                           .y     = 64,
                           .w     = static_cast<unsigned int>(scale * environment.size.x),
                           .h     = static_cast<unsigned int>(scale * environment.size.y),
                     }});

    // Configure the snake
    game::snake snake{{4, 4}};
    // ... to eat apples
    snake.on_eat([]() {
        environment.apple.x = rng_x();
        environment.apple.y = rng_y();
    });
    // ... and close the program on "death".
    snake.on_death([]() { sos::process::stop(); });

    // Tell the snake we want to move when using the arrow keys
    sos::input::keyboard::on_event([&](const auto& event) {
        using namespace sos::input::keyboard;
        if (event.state == keystate::pressed) {
            switch (event.scancode) {
                case scancode::scancode_left:
                    snake.left();
                    break;
                case scancode::scancode_right:
                    snake.right();
                    break;
                case scancode::scancode_up:
                    snake.up();
                    break;
                case scancode::scancode_down:
                    snake.down();
                    break;
                default:
                    break;
            }
        }
    });

    // Start the primary gameplay loop
    sos::process::start(20, [&](float delta) {
        // Update the snake
        snake.update(delta, environment);

        // Colors
        constexpr sos::video::color snake_color{100, 100, 200, 255};
        constexpr sos::video::color apple_color{200, 100, 100, 255};
        constexpr sos::video::color background_color{0, 0, 0, 255};

        // Render background
        sos::video::renderer::set_color(background_color);
        sos::video::renderer::clear();

        // Render apple
        sos::video::renderer::set_color(apple_color);
        sos::rect apple_rect{environment.apple.x * scale, environment.apple.y * scale,
                             scale, scale};
        sos::video::renderer ::draw(apple_rect);

        // Render snake
        sos::video::renderer::set_color(snake_color);
        for (auto segment : snake.body()) {
            sos::rect rect{
                segment.x * scale,
                segment.y * scale,
                scale,
                scale,
            };
            sos::video::renderer::draw(rect);
        }

        // Show everything
        sos::video::renderer::show();
    });

    // Cleanup
    sos::root::quit();

    // Tell POSIX we're alive
    return EXIT_SUCCESS;
}

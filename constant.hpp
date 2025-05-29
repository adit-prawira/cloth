#include <string>

namespace constants {
  constexpr int WINDOW_WIDTH = 1080;
  constexpr int WINDOW_HEIGHT = 800;
  constexpr int FRAMERATE_LIMIT = 60;
  constexpr float PARTICLE_RADIUS = 5.0f;
  constexpr float GRAVITY = 9.81f;
  constexpr float TIMES_STEP = 0.1f;
  constexpr float PARTICLE_DISTANCE = 20.0f;

  constexpr float CLICK_TOLERANCE = 10.0f;
  const std::string NAME = "Cloth Particle Simulation";
}

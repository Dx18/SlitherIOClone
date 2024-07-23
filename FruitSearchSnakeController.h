#pragma once

#include <optional>

#include "ISnakeController.h"
#include "Snake.h"

#include <glm/glm.hpp>

/** Controller for AI-controlled snake */
class FruitSearchSnakeController : public ISnakeController
{
public:
  virtual SnakeControls GetControls(float dt, const Snake &curr_snake, const Snakes &snakes,
                                    const Fruits &fruits) override;

private:
  std::optional<glm::vec2> target_;

  SnakeControls last_controls_{
      .turn = 0,
  };
  float controls_change_timer_{0.0};

  float fruit_relocate_timer_{0.0};
};

#pragma once

#include "ISnakeController.h"

/** Controller for player-controlled snake */
class PlayerInputSnakeController : public ISnakeController
{
public:
  virtual SnakeControls GetControls(float dt, const Snake &curr_snake, const Snakes &snakes,
                                    const Fruits &fruits) override;
};

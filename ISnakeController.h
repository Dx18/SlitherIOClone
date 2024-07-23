#pragma once

struct SnakeControls;
class Snake;
class ISnakeController;

class Snakes;
class Fruits;

/** Snake controller (can be player or AI) */
class ISnakeController
{
public:
  virtual ~ISnakeController() = 0;

  virtual SnakeControls GetControls(float dt, const Snake &curr_snake, const Snakes &snakes, const Fruits &fruits) = 0;
};

inline ISnakeController::~ISnakeController() = default;

#pragma once

#include <memory>

#include "ISnakeController.h"
#include "Snake.h"

/** Snake manager: spawning and drawing */
class Snakes
{
public:
  Snakes();

  const Snake &GetPlayerSnake() const;

  const std::vector<Snake> &GetSnakes() const;

  void Act(float dt, Fruits &fruits);

  void Draw(Renderer &renderer, const Camera &camera);

private:
  std::vector<Snake> snakes_;
  std::vector<std::unique_ptr<ISnakeController>> controllers_;

  std::mt19937 random_;
};

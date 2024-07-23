#include "PlayerInputSnakeController.h"

#include "Engine.h"
#include "Snake.h"

SnakeControls PlayerInputSnakeController::GetControls(float, const Snake &, const Snakes &, const Fruits &)
{
  int turn = 0;
  if (is_key_pressed(VK_LEFT))
  {
    ++turn;
  }
  if (is_key_pressed(VK_RIGHT))
  {
    --turn;
  }

  return SnakeControls{
      .turn = turn,
  };
}

#include "PlayerCameraController.h"

static constexpr float kCameraFollowHardness = 0.7;

void PlayerCameraController::Act(float dt, Camera &camera, const Snakes &snakes)
{
  const Snake &player_snake = snakes.GetPlayerSnake();
  camera.position =
      glm::mix(camera.position, player_snake.GetHeadPosition() + player_snake.GetMoveDirection() * kSnakeMoveSpeed,
               kCameraFollowHardness);
}

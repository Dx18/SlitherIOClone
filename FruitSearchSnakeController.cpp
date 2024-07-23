#include "FruitSearchSnakeController.h"

#include "Snake.h"

SnakeControls FruitSearchSnakeController::GetControls(float dt, const Snake &curr_snake, const Snakes &snakes,
                                                      const Fruits &fruits)
{
  controls_change_timer_ += dt;
  fruit_relocate_timer_ += dt;
  if (controls_change_timer_ < 0.2)
  {
    return last_controls_;
  }
  controls_change_timer_ = 0.0;

  glm::vec2 head_position = curr_snake.GetHeadPosition();
  glm::vec2 move_direction = curr_snake.GetMoveDirection();

  if (!target_.has_value() || fruit_relocate_timer_ >= 3.0)
  {
    target_ = fruits.GetClosestFruitPosition(head_position);
    if (!target_.has_value())
    {
      last_controls_ = SnakeControls{
          .turn = 0,
      };
      return last_controls_;
    }
  }

  glm::vec2 target = *target_;

  if (glm::length(head_position - target) < kSnakeHeadRadius + kFruitRadius)
  {
    target_ = std::nullopt;
    last_controls_ = SnakeControls{
        .turn = 0,
    };
    return last_controls_;
  }

  float radius = kSnakeMoveSpeed / kSnakeTurnSpeed;

  glm::vec2 center_left = head_position + glm::vec2(-move_direction.y, move_direction.x) * radius;
  glm::vec2 center_right = head_position + glm::vec2(move_direction.y, -move_direction.x) * radius;

  if (glm::length(target - center_left) <= radius * 0.8 || glm::length(target - center_right) <= radius * 0.8)
  {
    last_controls_ = SnakeControls{
        .turn = 0,
    };
    return last_controls_;
  }

  float dot_result = glm::dot(target - head_position, move_direction);
  float cross_result = glm::cross(glm::vec3(target - head_position, 0.0), glm::vec3(move_direction, 0.0)).z;

  int turn;

  if (dot_result >= 0.0)
  {
    turn = cross_result > 0.0 ? -1 : (cross_result < 0.0 ? 1 : 0);
  }
  else
  {
    turn = cross_result > 0.0 ? -1 : 1;
  }

  last_controls_ = SnakeControls{
      .turn = turn,
  };
  return last_controls_;
}

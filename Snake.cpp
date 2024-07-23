#include "Snake.h"

#include <glm/gtc/matrix_transform.hpp>

static constexpr glm::u8vec4 mix_colors(glm::u8vec4 color_begin, glm::u8vec4 color_end, float t)
{
  return glm::u8vec4(glm::vec4(color_begin) + t * (glm::vec4(color_end) - glm::vec4(color_begin)));
}

Snake::Snake(glm::vec2 position, glm::vec2 direction, SnakeColoring coloring)
    : form_points_({position}), grow_length_(1.0), head_position_(position), move_direction_(glm::normalize(direction)),
      fruits_eaten_(0), coloring_(coloring)
{
}

glm::vec2 Snake::GetHeadPosition() const
{
  return head_position_;
}

glm::vec2 Snake::GetMoveDirection() const
{
  return move_direction_;
}

const std::deque<glm::vec2> &Snake::GetFormPoints() const
{
  return form_points_;
}

size_t Snake::GetFruitsEaten() const
{
  return fruits_eaten_;
}

SnakeColoring Snake::GetColoring() const
{
  return coloring_;
}

void Snake::Act(float dt, Fruits &fruits, const SnakeControls &controls)
{
  if (fruits.CheckFruitCollision(head_position_, kSnakeHeadRadius))
  {
    ++fruits_eaten_;
    grow_length_ += 1.0;
  }

  if (controls.turn != 0)
  {
    move_direction_ =
        glm::rotate(glm::identity<glm::mat4>(), controls.turn * kSnakeTurnSpeed * dt, glm::vec3(0.0, 0.0, 1.0)) *
        glm::vec4(move_direction_, 0.0, 0.0);
    move_direction_ = glm::normalize(move_direction_);
  }

  head_position_ += move_direction_ * kSnakeMoveSpeed * dt;

  while (glm::length(head_position_ - form_points_.back()) >= kSnakeEdgeLength)
  {
    glm::vec2 new_point = form_points_.back() + glm::normalize(head_position_ - form_points_.back()) * kSnakeEdgeLength;

    Grow(new_point);
  }
}

void Snake::Draw(Renderer &renderer, const Camera &camera) const
{
  float shift = glm::length(head_position_ - form_points_.back()) / kSnakeEdgeLength;

  if (grow_length_ >= kSnakeEdgeLength)
  {
    renderer.DrawCircle(camera.ToScreenPoint(form_points_.front()), camera.ToScreenSize(kSnakeHeadRadius),
                        coloring_.tail_color);
  }

  for (size_t i = 0; i < form_points_.size() - 1; ++i)
  {
    glm::vec2 sprite_position = form_points_[i] + (form_points_[i + 1] - form_points_[i]) * shift;

    glm::u8vec4 color =
        mix_colors(coloring_.tail_color, coloring_.head_color, static_cast<float>(i) / (form_points_.size()));

    renderer.DrawCircle(camera.ToScreenPoint(sprite_position), camera.ToScreenSize(kSnakeHalfWidth), color);
  }

  renderer.DrawCircle(camera.ToScreenPoint(head_position_), camera.ToScreenSize(kSnakeHeadRadius),
                      coloring_.head_color);
}

void Snake::Grow(glm::vec2 new_point)
{
  if (grow_length_ >= kSnakeEdgeLength)
  {
    grow_length_ -= kSnakeEdgeLength;
  }
  else
  {
    form_points_.pop_front();
  }

  form_points_.push_back(new_point);
}

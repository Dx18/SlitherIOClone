#pragma once

#include <deque>

#include "Camera.h"
#include "Fruits.h"
#include "Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

constexpr float kSnakeHalfWidth = 0.5;
constexpr float kSnakeHeadRadius = 0.55;
constexpr float kSnakeEdgeLength = 0.3;

constexpr float kSnakeMoveSpeed = 1.8;
constexpr float kSnakeTurnSpeed = glm::pi<float>() / 2.0;

/** Snake control input */
struct SnakeControls
{
  int turn{0};
};

/** The coloring of a snake */
struct SnakeColoring
{
  glm::u8vec4 head_color;
  glm::u8vec4 tail_color;
};

/** Snake */
class Snake
{
public:
  Snake(glm::vec2 position, glm::vec2 direction, SnakeColoring coloring);

  glm::vec2 GetHeadPosition() const;

  glm::vec2 GetMoveDirection() const;

  const std::deque<glm::vec2> &GetFormPoints() const;

  size_t GetFruitsEaten() const;

  SnakeColoring GetColoring() const;

  void Act(float dt, Fruits &fruits, const SnakeControls &controls);

  void Draw(Renderer &renderer, const Camera &camera) const;

private:
  std::deque<glm::vec2> form_points_;
  float grow_length_;

  glm::vec2 head_position_;
  glm::vec2 move_direction_;

  size_t fruits_eaten_;

  SnakeColoring coloring_;

  void Grow(glm::vec2 new_point);
};

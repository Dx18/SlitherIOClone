#pragma once

#include <glm/glm.hpp>

/** Camera */
class Camera
{
public:
  glm::vec2 position{glm::vec2(0.0)};
  float view_scale{1.0};

  glm::ivec2 ToScreenPoint(glm::vec2 query_position) const;

  glm::ivec2 ToScreenSize(glm::vec2 size) const;

  int ToScreenSize(float size) const;
};

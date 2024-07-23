#include "Camera.h"

#include "Engine.h"

glm::ivec2 Camera::ToScreenPoint(glm::vec2 query_position) const
{
  return glm::ivec2(static_cast<float>(SCREEN_WIDTH) / 2.0f / view_scale * glm::vec2(1.0, -1.0) *
                    (query_position - position)) +
         glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT) / 2;
}

glm::ivec2 Camera::ToScreenSize(glm::vec2 size) const
{
  return glm::ivec2(static_cast<float>(SCREEN_WIDTH) / 2.0f / view_scale * size);
}

int Camera::ToScreenSize(float size) const
{
  return static_cast<int>(static_cast<float>(SCREEN_WIDTH) / 2.0f / view_scale * size);
}

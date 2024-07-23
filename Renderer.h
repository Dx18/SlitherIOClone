#pragma once

#include <glm/glm.hpp>

/** Renderer which writes colors to in-memory buffer */
class Renderer
{
public:
  Renderer(uint32_t *buffer, size_t width, size_t height);

  void Clear(glm::u8vec4 color);

  void DrawRectangle(glm::ivec2 begin, glm::ivec2 end, glm::u8vec4 color);

  void DrawCircle(glm::ivec2 center, int radius, glm::u8vec4 color);

private:
  uint32_t *buffer_;
  size_t width_;
  size_t height_;

  static uint32_t PackColor(glm::u8vec4 color);
};

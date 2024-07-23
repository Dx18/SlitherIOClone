#include "Renderer.h"

Renderer::Renderer(uint32_t *buffer, size_t width, size_t height) : buffer_(buffer), width_(width), height_(height)
{
}

void Renderer::Clear(glm::u8vec4 color)
{
  std::fill(buffer_, buffer_ + width_ * height_, PackColor(color));
}

void Renderer::DrawRectangle(glm::ivec2 begin, glm::ivec2 end, glm::u8vec4 color)
{
  if (begin.x > end.x)
  {
    std::swap(begin.x, end.x);
  }
  if (begin.y > end.y)
  {
    std::swap(begin.y, end.y);
  }

  for (int y = begin.y; y <= end.y; ++y)
  {
    if (y < 0 || y >= height_)
    {
      continue;
    }

    for (int x = begin.x; x <= end.x; ++x)
    {
      if (x < 0 || x >= width_)
      {
        continue;
      }

      buffer_[y * width_ + x] = PackColor(color);
    }
  }
}

void Renderer::DrawCircle(glm::ivec2 center, int radius, glm::u8vec4 color)
{
  for (int y = center.y - radius; y <= center.y + radius; ++y)
  {
    if (y < 0 || y >= height_)
    {
      continue;
    }

    for (int x = center.x - radius; x <= center.x + radius; ++x)
    {
      if (x < 0 || x >= width_)
      {
        continue;
      }

      glm::ivec2 vec = glm::ivec2(x, y) - center;
      if (vec.x * vec.x + vec.y * vec.y <= radius * radius)
      {
        buffer_[y * width_ + x] = PackColor(color);
      }
    }
  }
}

uint32_t Renderer::PackColor(glm::u8vec4 color)
{
  return (static_cast<uint32_t>(color.a) << 24) | (static_cast<uint32_t>(color.r) << 16) |
         (static_cast<uint32_t>(color.g) << 8) | color.b;
}

#include "PlayArea.h"

static constexpr size_t kAreaBoundDivision = 10;

static constexpr glm::u8vec4 kAreaBoundsLightColor = glm::u8vec4(240, 230, 0, 255);
static constexpr glm::u8vec4 kAreaBoundsDarkColor = glm::u8vec4(15, 15, 15, 255);

void PlayArea::Draw(Renderer &renderer, const Camera &camera)
{
  DrawCorner(renderer, camera, glm::imat2x2(1, 0, 0, 1), false);
  DrawEdge(renderer, camera, glm::imat2x2(1, 0, 0, 1), false);
  DrawCorner(renderer, camera, glm::imat2x2(0, 1, -1, 0), kAreaBoundDivision % 2 == 0);
  DrawEdge(renderer, camera, glm::imat2x2(0, 1, -1, 0), kAreaBoundDivision % 2 == 0);
  DrawCorner(renderer, camera, glm::imat2x2(-1, 0, 0, -1), false);
  DrawEdge(renderer, camera, glm::imat2x2(-1, 0, 0, -1), false);
  DrawCorner(renderer, camera, glm::imat2x2(0, -1, 1, 0), kAreaBoundDivision % 2 == 0);
  DrawEdge(renderer, camera, glm::imat2x2(0, -1, 1, 0), kAreaBoundDivision % 2 == 0);
}

void PlayArea::DrawCorner(Renderer &renderer, const Camera &camera, glm::imat2x2 transform, bool is_light)
{
  glm::vec2 begin = camera.ToScreenPoint(transform * glm::vec2(kAreaHalfSize, -kAreaHalfSize));
  glm::vec2 end = camera.ToScreenPoint(transform * glm::vec2(kAreaHalfSize + 1.0, -kAreaHalfSize - 1.0));

  renderer.DrawRectangle(begin, end, is_light ? kAreaBoundsLightColor : kAreaBoundsDarkColor);
}

void PlayArea::DrawEdge(Renderer &renderer, const Camera &camera, glm::imat2x2 transform, bool start_with_dark)
{
  for (int i = 0; i < kAreaBoundDivision; ++i)
  {
    glm::vec2 begin = camera.ToScreenPoint(
        glm::mat2(transform) * glm::vec2(kAreaHalfSize, -kAreaHalfSize + kAreaHalfSize * 2.0 / kAreaBoundDivision * i));
    glm::vec2 end = camera.ToScreenPoint(
        glm::mat2(transform) *
        glm::vec2(kAreaHalfSize + 1.0, -kAreaHalfSize + kAreaHalfSize * 2.0 / kAreaBoundDivision * (i + 1)));

    renderer.DrawRectangle(begin, end,
                           i % 2 == static_cast<int>(start_with_dark) ? kAreaBoundsLightColor : kAreaBoundsDarkColor);
  }
}

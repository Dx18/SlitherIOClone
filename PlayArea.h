#pragma once

#include "Camera.h"
#include "Renderer.h"

constexpr float kAreaHalfSize = 32.0;

class PlayArea
{
public:
  void Draw(Renderer &renderer, const Camera &camera);

private:
  void DrawCorner(Renderer &renderer, const Camera &camera, glm::imat2x2 transform, bool is_light);
  void DrawEdge(Renderer &renderer, const Camera &camera, glm::imat2x2 transform, bool start_with_dark);
};

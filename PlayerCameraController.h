#pragma once

#include "Camera.h"
#include "Snakes.h"

class PlayerCameraController
{
public:
  void Act(float dt, Camera &camera, const Snakes &snakes);
};

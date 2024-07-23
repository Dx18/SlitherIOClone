#include "Engine.h"

#include "Camera.h"
#include "Fruits.h"
#include "PlayArea.h"
#include "PlayerCameraController.h"
#include "Renderer.h"
#include "Snakes.h"

PlayArea play_area;

Renderer renderer(reinterpret_cast<uint32_t *>(buffer), SCREEN_WIDTH, SCREEN_HEIGHT);

Camera camera;

PlayerCameraController player_camera_controller;

Fruits fruits;

Snakes snakes;

void initialize()
{
  camera.view_scale = 16.0;
}

void act(float dt)
{
  if (is_key_pressed(VK_ESCAPE))
  {
    schedule_quit_game();
  }

  fruits.Act(dt);

  snakes.Act(dt, fruits);

  player_camera_controller.Act(dt, camera, snakes);
}

void draw()
{
  renderer.Clear(glm::u8vec4(30, 30, 30, 255));

  play_area.Draw(renderer, camera);

  fruits.Draw(renderer, camera);

  snakes.Draw(renderer, camera);
}

void finalize()
{
}

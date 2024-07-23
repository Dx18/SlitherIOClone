#pragma once

#include <optional>
#include <random>

#include "Camera.h"
#include "Renderer.h"

constexpr float kFruitRadius = 0.3;

/** Fruit manager: querying, spawning, and drawing */
class Fruits
{
public:
  Fruits();

  bool CheckFruitCollision(glm::vec2 center, float radius);

  std::optional<glm::vec2> GetClosestFruitPosition(glm::vec2 query_position) const;

  void SpawnFruit(glm::vec2 point);

  void Act(float dt);

  void Draw(Renderer &renderer, const Camera &camera) const;

private:
  std::vector<glm::vec2> positions_;

  float timer_{0.0};

  std::mt19937 random_;

  void SpawnRandomFruit();
};

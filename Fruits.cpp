#include "Fruits.h"

#include "PlayArea.h"

static constexpr size_t kMaxFruitCount = 60;

static constexpr float kFruitSpawnPeriod = 0.3;

static constexpr glm::u8vec4 kFruitColor = glm::u8vec4(240, 15, 10, 255);

Fruits::Fruits() : random_(std::random_device{}())
{
}

bool Fruits::CheckFruitCollision(glm::vec2 center, float radius)
{
  for (glm::vec2 &position : positions_)
  {
    if (glm::length(position - center) < radius + kFruitRadius)
    {
      std::swap(position, positions_.back());
      positions_.pop_back();

      return true;
    }
  }

  return false;
}

std::optional<glm::vec2> Fruits::GetClosestFruitPosition(glm::vec2 query_position) const
{
  std::optional<glm::vec2> result;
  float min_distance = std::numeric_limits<float>::max();
  for (glm::vec2 position : positions_)
  {
    float distance = glm::length(query_position - position);
    if (distance < min_distance)
    {
      result = position;
      min_distance = distance;
    }
  }

  return result;
}

void Fruits::SpawnFruit(glm::vec2 point)
{
  positions_.push_back(point);
}

void Fruits::Act(float dt)
{
  timer_ += dt;

  while (positions_.size() < kMaxFruitCount && timer_ >= kFruitSpawnPeriod)
  {
    timer_ -= kFruitSpawnPeriod;
    SpawnRandomFruit();
  }
}

void Fruits::Draw(Renderer &renderer, const Camera &camera) const
{
  for (size_t i = 0; i < positions_.size(); ++i)
  {
    renderer.DrawCircle(camera.ToScreenPoint(positions_[i]), camera.ToScreenSize(kFruitRadius), kFruitColor);
  }
}

void Fruits::SpawnRandomFruit()
{
  std::uniform_real_distribution<float> gen_coordinate(-kAreaHalfSize, kAreaHalfSize);

  float x = gen_coordinate(random_);
  float y = gen_coordinate(random_);

  positions_.push_back(glm::vec2(x, y));
}

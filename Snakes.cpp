#include "Snakes.h"

#include "FruitSearchSnakeController.h"
#include "PlayArea.h"
#include "PlayerInputSnakeController.h"

#include <algorithm>

static constexpr size_t kSnakeCount = 20;

static constexpr glm::u8vec4 kPlayerSnakeHeadColor = glm::u8vec4(20, 230, 10, 255);
static constexpr glm::u8vec4 kPlayerSnakeTailColor = glm::u8vec4(70, 200, 15, 255);

static constexpr glm::u8vec4 kAISnakeHeadColor = glm::u8vec4(200, 15, 230, 255);
static constexpr glm::u8vec4 kAISnakeTailColor = glm::u8vec4(230, 15, 180, 255);

Snakes::Snakes() : random_(std::random_device{}())
{
  snakes_.push_back(Snake(glm::vec2(0.0), glm::vec2(1.0, 0.0),
                          SnakeColoring{
                              .head_color = kPlayerSnakeHeadColor,
                              .tail_color = kPlayerSnakeTailColor,
                          }));
  controllers_.push_back(std::make_unique<PlayerInputSnakeController>());

  std::uniform_real_distribution<float> gen_coordinate(-kAreaHalfSize, kAreaHalfSize);
  std::uniform_real_distribution<float> gen_angle(0.0, glm::pi<float>());

  for (size_t i = 0; i < kSnakeCount; ++i)
  {
    float x = gen_coordinate(random_);
    float y = gen_coordinate(random_);
    glm::vec2 head_position = glm::vec2(x, y);

    float angle = gen_angle(random_);
    glm::vec2 move_direction = glm::vec2(std::cos(angle), std::sin(angle));

    snakes_.push_back(Snake(head_position, move_direction,
                            SnakeColoring{
                                .head_color = kAISnakeHeadColor,
                                .tail_color = kAISnakeTailColor,
                            }));
    controllers_.push_back(std::make_unique<FruitSearchSnakeController>());
  }
}

const Snake &Snakes::GetPlayerSnake() const
{
  return snakes_[0];
}

const std::vector<Snake> &Snakes::GetSnakes() const
{
  return snakes_;
}

void Snakes::Act(float dt, Fruits &fruits)
{
  for (size_t i = 0; i < snakes_.size(); ++i)
  {
    SnakeControls controls = controllers_[i]->GetControls(dt, snakes_[i], *this, fruits);
    snakes_[i].Act(dt, fruits, controls);
  }

  std::vector<size_t> snakes_to_destroy;

  for (size_t i = 0; i < snakes_.size(); ++i)
  {
    glm::vec2 head_position = snakes_[i].GetHeadPosition();

    if (std::abs(head_position.x) + kSnakeHeadRadius >= kAreaHalfSize ||
        std::abs(head_position.y) + kSnakeHeadRadius >= kAreaHalfSize)
    {
      snakes_to_destroy.push_back(i);
      continue;
    }

    for (size_t j = 0; j < snakes_.size(); ++j)
    {
      if (j == i)
      {
        continue;
      }

      auto &form_points = snakes_[j].GetFormPoints();
      assert(!form_points.empty());

      if (form_points.size() == 1)
      {
        glm::vec2 point = form_points.front();

        if (glm::length(point - head_position) <= kSnakeHeadRadius)
        {
          snakes_to_destroy.push_back(i);
          break;
        }

        continue;
      }

      bool destroyed = false;
      for (auto curr_iter = form_points.begin();; ++curr_iter)
      {
        auto next_iter = curr_iter;
        ++next_iter;

        if (next_iter == form_points.end())
        {
          break;
        }

        glm::vec2 curr_point = *curr_iter;
        glm::vec2 next_point = *next_iter;

        float denominator = glm::dot(next_point - curr_point, next_point - curr_point);

        if (denominator <= 1e-4)
        {
          glm::vec2 point = curr_point + 0.5f * (next_point - curr_point);

          if (glm::length(point - head_position) <= kSnakeHeadRadius)
          {
            destroyed = true;
            snakes_to_destroy.push_back(i);
            break;
          }
        }

        float numerator = glm::dot(head_position - curr_point, next_point - curr_point);

        float t = std::clamp(numerator / denominator, 0.0f, 1.0f);

        float distance = glm::length(curr_point + t * (next_point - curr_point) - head_position);
        if (distance <= kSnakeHeadRadius)
        {
          destroyed = true;
          snakes_to_destroy.push_back(i);
          break;
        }
      }

      if (destroyed)
      {
        break;
      }
    }
  }

  for (size_t snake_index : snakes_to_destroy)
  {
    const Snake &snake = snakes_[snake_index];

    if (snake.GetFormPoints().size() >= 2)
    {
      size_t fruit_count = snake.GetFruitsEaten() / 2;

      std::uniform_int_distribution<size_t> gen_segment_index(0, snake.GetFormPoints().size() - 2);
      std::uniform_real_distribution<float> gen_local_coordinate(0.0, 1.0);

      for (size_t i = 0; i < fruit_count; ++i)
      {
        size_t index = gen_segment_index(random_);
        float coordinate = gen_local_coordinate(random_);

        glm::vec2 curr_point = snake.GetFormPoints()[index];
        glm::vec2 next_point = snake.GetFormPoints()[index + 1];

        fruits.SpawnFruit(curr_point + coordinate * (next_point - curr_point));
      }
    }

    std::uniform_real_distribution<float> gen_coordinate(-kAreaHalfSize, kAreaHalfSize);

    float x = gen_coordinate(random_);
    float y = gen_coordinate(random_);
    glm::vec2 head_position = glm::vec2(x, y);

    glm::vec2 move_direction = snake.GetMoveDirection();

    SnakeColoring coloring = snake.GetColoring();

    snakes_[snake_index] = Snake(head_position, move_direction, coloring);
  }
}

void Snakes::Draw(Renderer &renderer, const Camera &camera)
{
  for (size_t i = 0; i < snakes_.size(); ++i)
  {
    snakes_[i].Draw(renderer, camera);
  }
}

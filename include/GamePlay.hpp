#pragma once

#include <memory>
#include <array>
#include <vector>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Game.hpp"
#include "State.hpp"
#include "Snake.hpp"

class GamePlay : public Engine::State
{
    private:
        std::shared_ptr<Context> m_context;
        sf::Sprite m_grass;
        std::vector<sf::Sprite> m_food;
        std::array<sf::Sprite, 4> m_walls;
        std::vector<sf::Sprite> m_difWalls;

        Snake m_snake; 

        sf::Vector2f m_snakeDirection;
        sf::Time m_elapsedTime;
        float m_st_elapsedTime;
        float m_cur_elapsedTime;
        int m_repeats;

        int x_tileCount;
        int y_tileCount;

        sf::Text m_scoreText;
        int m_score;

        int difficult;


    public:
        GamePlay(std::shared_ptr<Context> &context, int difficult);
        ~GamePlay();

        void Init() override;
        void ProcessInput() override;
        void Update(sf::Time deltaTime) override;
        void Draw() override;
        void Pause() override;
        void Start() override;
        void SpawnFood(sf::Sprite& food);
};
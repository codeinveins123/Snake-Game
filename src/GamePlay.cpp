#include "GamePlay.hpp"
#include "GameOver.hpp"
#include "PauseGame.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System.hpp>

#include <stdlib.h>
#include <vector>
#include <algorithm>

const int tilesize = 32;

GamePlay::GamePlay(std::shared_ptr<Context> &context, int difficult) : 
    m_context(context), difficult(difficult), m_snakeDirection({32.0f, 0.f}), m_elapsedTime(),
    m_st_elapsedTime(0.125), m_cur_elapsedTime(m_st_elapsedTime),
    x_tileCount(m_context->m_window->getSize().x / tilesize - 2),
    y_tileCount(m_context->m_window->getSize().y / tilesize - 2),
    m_score(0), m_repeats(0)
{
    srand(time(0));
    m_food.push_back(sf::Sprite());
}

GamePlay::~GamePlay()
{

}

void GamePlay::Init()
{

    m_context->m_assets->AddTexture(GRASS, "../assets/textures/Grass.png", true);
    m_context->m_assets->AddTexture(FOOD, "../assets/textures/Apple.png");
    m_context->m_assets->AddTexture(FOOD2, "../assets/textures/Apple2.png");
    m_context->m_assets->AddTexture(SNAKE_BODY, "../assets/textures/SneakBody.png");
    m_context->m_assets->AddTexture(SNAKE_HEAD, "../assets/textures/SneakHead.png");
    m_context->m_assets->AddTexture(WALL, "../assets/textures/Wall2.png", true);

    m_context->m_assets->AddTexture(SPEEDUP, "../assets/textures/SpeedUp.png");
    m_context->m_assets->AddTexture(SPEEDDOWN, "../assets/textures/SpeedDown.png");

    m_context->m_assets->AddSound(FOODSOUND, "../assets/music/FoodSound.ogg");
    m_context->m_assets->AddSound(WALLSOUND, "../assets/music/WallSound.ogg");
    m_context->m_assets->AddSound(GAMEOVER_SOUND, "../assets/music/GameOverSound.ogg");
    m_context->m_assets->AddSound(SELECT_SOUND, "../assets/music/SelectSound.ogg");

    m_grass.setTexture(m_context->m_assets->GetTexture(GRASS));
    m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

    for(auto& wall : m_walls)
    {
        wall.setTexture(m_context->m_assets->GetTexture(WALL));
    }

    for (int i = 0; i < difficult; ++i)
    {
        m_difWalls.push_back(sf::Sprite());
        m_difWalls[i].setTexture(m_context->m_assets->GetTexture(WALL));
        
        bool intersect;
        do
        {
            intersect = false;
            m_difWalls[i].setPosition(
                tilesize * ((rand() % (x_tileCount - 2)) + 2), 
                tilesize * ((rand() % (y_tileCount - 2)) + 2)
            );
    
            auto it = std::find_if(m_difWalls.begin(), m_difWalls.end(), 
                [this, i](const sf::Sprite& sprite) 
                {
                    return sprite.getPosition() == m_difWalls[i].getPosition();
                });
    
            if (it != m_difWalls.end())
            {
                sf::Vector2f itPos = it->getPosition();
    
                for (auto wall = m_difWalls.begin(); wall != m_difWalls.end(); ++wall)
                {
                    sf::Vector2f v = wall->getPosition();
                    if (itPos + sf::Vector2f(-32.0f, -32.0f) == v ||
                        itPos + sf::Vector2f(32.0f, -32.0f) == v ||
                        itPos + sf::Vector2f(-32.0f, 32.0f) == v ||
                        itPos + sf::Vector2f(32.0f, 32.0f) == v)
                    {
                        intersect = true;
                        break;
                    }
                }
            }
    
        } while (intersect);
    
        m_difWalls[i].setTextureRect({0, 0, tilesize, tilesize});
    }

    m_food.back().setTexture(m_context->m_assets->GetTexture(FOOD2));
    SpawnFood(m_food.back());


    m_walls[0].setTextureRect({0, 0, static_cast<int>(m_context->m_window->getSize().x), tilesize});
    m_walls[1].setTextureRect({0, 0, static_cast<int>(m_context->m_window->getSize().x), tilesize});
    m_walls[1].setPosition(0, m_context->m_window->getSize().y - tilesize);

    m_walls[2].setTextureRect({0, 0, tilesize, static_cast<int>(m_context->m_window->getSize().y)});
    m_walls[3].setTextureRect({0, 0, tilesize, static_cast<int>(m_context->m_window->getSize().y)});
    m_walls[3].setPosition(m_context->m_window->getSize().x - tilesize, 0);

    m_snake.Init(m_context->m_assets->GetTexture(SNAKE_BODY), m_context->m_assets->GetTexture(SNAKE_HEAD));

    m_scoreText.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_scoreText.setString("Score: " + std::to_string(m_score));
    m_scoreText.setFillColor(sf::Color::Black);
    //m_scoreText.setCharacterSize(15); //bad for 32x32textures, but good for 16x16
}

void GamePlay::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_context->m_window->close();
        }
        else if(event.type == sf::Event::KeyPressed)
        {
            sf::Vector2f newDirection = m_snakeDirection;
            switch (event.key.code)
            {
                case sf::Keyboard::Up: case sf::Keyboard::W:
                    newDirection = {0.f, -32.f};
                    break;
                case sf::Keyboard::Left: case sf::Keyboard::A:
                    newDirection = {-32.f, 0.f};
                    break;
                case sf::Keyboard::Down: case sf::Keyboard::S:
                    newDirection = {0.f, 32.f};
                    break;
                case sf::Keyboard::Right: case sf::Keyboard::D:
                    newDirection = {32.f, 0.f};
                    break;
                case sf::Keyboard::Escape: case sf::Keyboard::Space:
                    m_context->m_states->Add(std::make_unique<PauseGame>(m_context), false);
                    break;
                default:
                    break;
            }
            if(abs(m_snakeDirection.x) != abs(newDirection.x) ||
                abs(m_snakeDirection.y) != abs(newDirection.y) )
            {
                m_snakeDirection = newDirection;
            }
        }
    }

}

void GamePlay::Update(sf::Time deltaTime)
{
    if(m_repeats == 0)
    {
        m_cur_elapsedTime = m_st_elapsedTime;
    }
    m_elapsedTime += deltaTime;

    auto old_head = m_snake.getHead();

    for(auto& wall:  m_walls)
    {
        if(m_snake.IsOn(wall))
        {
            m_context->m_assets->GetSound(FUNNY_MUSIC).pause();
            m_context->m_assets->GetSound(WALLSOUND).play();
            sf::sleep(sf::seconds(1.5f));
            m_context->m_states->Add(std::make_unique<GameOver>(m_context, difficult), true);
        }
    }

    for(auto& wall:  m_difWalls)
    {
        if(m_snake.IsOn(wall))
        {
            m_context->m_assets->GetSound(FUNNY_MUSIC).pause();
            m_context->m_assets->GetSound(WALLSOUND).play();
            sf::sleep(sf::seconds(1.5f));
            m_context->m_states->Add(std::make_unique<GameOver>(m_context, difficult), true);
        }
    }

    if (m_elapsedTime.asSeconds() > m_cur_elapsedTime)
    {
        bool foodEaten = false;
    
        for (size_t i = 0; i < m_food.size(); ++i)
        {
            if (m_snake.IsOn(m_food[i]))  
            {
                m_context->m_assets->GetSound(FOODSOUND).play();
                if(m_food[i].getTexture() == &m_context->m_assets->GetTexture(SPEEDDOWN))
                {
                    m_snake.GrowT(m_snakeDirection);
                    m_score += 1;
                    m_cur_elapsedTime += 0.4f;
                    m_repeats += 10;
                    m_food[i].setTexture(m_context->m_assets->GetTexture(FOOD2));
                }
                else if(m_food[i].getTexture() == &m_context->m_assets->GetTexture(SPEEDUP))
                {
                    m_snake.GrowT(m_snakeDirection);
                    m_score += 1;
                    m_cur_elapsedTime -= 0.5f;
                    m_repeats += 3;
                    m_food[i].setTexture(m_context->m_assets->GetTexture(FOOD2));
                }
                
                if(rand() % 5 == 0)
                {
                    if(rand() % 2 == 0)
                    {
                        m_food[i].setTexture(m_context->m_assets->GetTexture(SPEEDDOWN));
                    }
                    else
                    {
                        m_food[i].setTexture(m_context->m_assets->GetTexture(SPEEDUP));
                    }
                }
                SpawnFood(m_food[i]);

                foodEaten = true;
                
                if (rand() % (100 - m_score) == 0 && m_score < 100)
                {
                    sf::Sprite newFood;
                    newFood.setTexture(m_context->m_assets->GetTexture(FOOD2));
                    SpawnFood(newFood);
    
                    m_food.push_back(newFood);
                }

    
                m_snake.GrowH(m_snakeDirection);
                m_score += 1;
                m_scoreText.setString("Score: " + std::to_string(m_score));
    
                break;
            }
        }
    
        if (!foodEaten)
        {
            m_snake.Move(m_snakeDirection);
        }
    
        if(m_snake.IsOnBody(*(m_snake.getHead())))
        {
            m_context->m_assets->GetSound(FUNNY_MUSIC).pause();
            sf::sleep(sf::seconds(1.5f));
            m_context->m_assets->GetSound(GAMEOVER_SOUND).play();
            m_context->m_states->Add(std::make_unique<GameOver>(m_context, difficult));
        }
        if(m_repeats > 0)
        {
            m_repeats -= 1;
        }
        else
        {
            m_repeats = 0;
        }
    
        m_elapsedTime = sf::Time::Zero;
    }
    

    old_head->setTexture(m_context->m_assets->GetTexture(SNAKE_BODY));
    m_snake.getHead()->setTexture(m_context->m_assets->GetTexture(SNAKE_HEAD));

}

void GamePlay::Draw()
{
    m_context->m_window->clear();
    m_context->m_window->draw(m_grass);
    for(auto& wall : m_walls)
    {
        m_context->m_window->draw(wall);
    }
    for(auto& wall : m_difWalls)
    {
        m_context->m_window->draw(wall);
    }
    for(auto& food : m_food)
    {
        m_context->m_window->draw(food);
    }
    m_context->m_window->draw(m_snake);
    m_context->m_window->draw(m_scoreText);
    m_context->m_window->display();
}

void GamePlay::SpawnFood(sf::Sprite& food)
{
    bool intersects;
    do
    {
        intersects = false;
        food.setPosition(tilesize * (rand() % x_tileCount + 1), tilesize *  (rand() % y_tileCount + 1));
        for(auto& wall : m_difWalls)
        {
            if(food.getGlobalBounds().intersects(wall.getGlobalBounds()))
            {
                intersects = true;
                break;
            }
        }
        for(auto& snake : m_snake.getBody())
        {
            if(food.getGlobalBounds().intersects(snake.getGlobalBounds()))
            {
                intersects = true;
                break;
            }
        }
        auto it = std::find_if(m_food.begin(), m_food.end(), [&food](const sf::Sprite& sprite)
        {
            return sprite.getPosition() == food.getPosition();
        });
        for(auto otherFood = m_food.begin(); otherFood != m_food.end(); ++otherFood)
        {
            if(otherFood != it)
            {
                if(it->getGlobalBounds().intersects(otherFood->getGlobalBounds()))
                {
                    intersects = true;
                    break;
                }
            }
        }
    }
    while(intersects);
}

void GamePlay::Pause()
{

}

void GamePlay::Start()
{

}

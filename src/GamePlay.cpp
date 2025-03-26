#include "GamePlay.hpp"
#include "GameOver.hpp"
#include "PauseGame.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>

#include <stdlib.h>
#include <vector>

const int tilesize = 32;

GamePlay::GamePlay(std::shared_ptr<Context> &context) : 
    m_context(context), m_snakeDirection({32.0f, 0.f}), m_elapsedTime(sf::Time::Zero),
    x_tileCount(m_context->m_window->getSize().x / tilesize - 2),
    y_tileCount(m_context->m_window->getSize().y / tilesize - 2),
    m_score(0)
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

    m_grass.setTexture(m_context->m_assets->GetTexture(GRASS));
    m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

    m_food.back().setTexture(m_context->m_assets->GetTexture(FOOD2));
    m_food.back().setPosition(tilesize * (rand() % x_tileCount + 1), tilesize *  (rand() % y_tileCount + 1));

    for(auto& wall : m_walls)
    {
        wall.setTexture(m_context->m_assets->GetTexture(WALL));
    }

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
    m_elapsedTime += deltaTime;

    auto old_head = m_snake.getHead();

    for(auto& wall:  m_walls)
    {
        if(m_snake.IsOn(wall))
        {
            m_context->m_states->Add(std::make_unique<GameOver>(m_context), true);
        }
    }

    if (m_elapsedTime.asSeconds() > 0.11)
    {
        bool foodEaten = false;
    
        for (size_t i = 0; i < m_food.size(); ++i)  
        {
            if (m_snake.IsOn(m_food[i]))  
            {
                do
                {
                    m_food[i].setPosition(tilesize * (rand() % x_tileCount + 1), 
                                          tilesize * (rand() % y_tileCount + 1));
                } 
                while (m_snake.IsOnBody(m_food[i]) || m_snake.IsOn(m_food[i]));
                foodEaten = true;
                
                if (rand() % (125 - m_score) == 0 && m_score < 100)
                {
                    sf::Sprite newFood;
                    newFood.setTexture(m_context->m_assets->GetTexture(FOOD2));
                    do
                    {
                        newFood.setPosition(tilesize * (rand() % x_tileCount + 1), 
                                            tilesize * (rand() % y_tileCount + 1));
                    } 
                    while (m_snake.IsOnBody(newFood) || m_snake.IsOn(newFood));
    
                    m_food.push_back(newFood); // Добавляем в список
                }

    
                m_snake.Grow(m_snakeDirection);
                m_score += 1;
                m_scoreText.setString("Score: " + std::to_string(m_score));
    
                break;  // Выходим, чтобы змея не ела сразу несколько предметов
            }
        }
    
        if (!foodEaten)  // Двигаем змею только если она НЕ съела еду
        {
            m_snake.Move(m_snakeDirection);
        }
    
        if(m_snake.IsOnBody(*(m_snake.getHead())))
        {
            m_context->m_states->Add(std::make_unique<GameOver>(m_context));
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
    for(auto& food : m_food)
    {
        m_context->m_window->draw(food);
    }
    m_context->m_window->draw(m_snake);
    m_context->m_window->draw(m_scoreText);
    m_context->m_window->display();
}

void GamePlay::Pause()
{

}

void GamePlay::Start()
{

}

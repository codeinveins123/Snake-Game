#include "GameOver.hpp"
#include "GamePlay.hpp"

#include <SFML/Window/Event.hpp>

GameOver::GameOver(std::shared_ptr<Context>& context)
    : m_context(context), m_isRetryButtonSelected(true), m_isExitButtonSelected(false),
    m_isExitButtonPressed(false), m_isRetryButtonPressed(false)
{

}

GameOver::~GameOver() 
{

}

void GameOver::Init()
{
    m_context->m_assets->AddFont(MAIN_FONT, "../assets/fonts/Anton/Anton-Regular.ttf");
    //GameOverTitle
    m_gameOverTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameOverTitle.setString("Game Over");
    m_gameOverTitle.setOrigin(m_gameOverTitle.getLocalBounds().width / 2,
                          m_gameOverTitle.getLocalBounds().height / 2);
    m_gameOverTitle.setPosition(m_context->m_window->getSize().x / 2,
                            m_context->m_window->getSize().y / 2 - 150.f);
    //Retry
    m_retryButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_retryButton.setString("Retry");
    m_retryButton.setOrigin(m_retryButton.getLocalBounds().width / 2,
                          m_retryButton.getLocalBounds().height / 2);
    m_retryButton.setPosition(m_context->m_window->getSize().x / 2,
                            m_context->m_window->getSize().y / 2 - 25.f);
    m_retryButton.setCharacterSize(20);                            
    //Exit
    m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_exitButton.setString("Exit");
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2,
                          m_exitButton.getLocalBounds().height / 2);
    m_exitButton.setPosition(m_context->m_window->getSize().x / 2,
                            m_context->m_window->getSize().y / 2 + 25.f);
    m_exitButton.setCharacterSize(20);                                                                                            
}

void GameOver::ProcessInput()
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
            switch (event.key.code)
            {
                case sf::Keyboard::Up: case sf::Keyboard::W:
                {
                    if(!m_isRetryButtonSelected)
                    {
                        m_isRetryButtonSelected = true;
                        m_isExitButtonSelected = false;
                    }
                    break;
                }
                    
                case sf::Keyboard::Down: case sf::Keyboard::S:
                {
                    if(!m_isExitButtonSelected)
                    {
                        m_isRetryButtonSelected = false;
                        m_isExitButtonSelected = true;
                    }
                    break;
                }
                case sf::Keyboard::Return:
                {
                    m_isRetryButtonPressed = false;
                    m_isExitButtonPressed = false;

                    if(m_isRetryButtonSelected)
                    {
                        m_isRetryButtonPressed = true;
                    }
                    else
                    {
                        m_isExitButtonPressed = true;
                    }
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }
}

void GameOver::Update(sf::Time deltaTime)
{
    m_gameOverTitle.setFillColor(sf::Color::Yellow);
    if(m_isRetryButtonSelected)
    {
        m_retryButton.setFillColor(sf::Color::Black);
        m_exitButton.setFillColor(sf::Color::Yellow);
    }
    else
    {
        m_exitButton.setFillColor(sf::Color::Black);
        m_retryButton.setFillColor(sf::Color::Yellow);
    }

    if(m_isRetryButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);
    }
    else if(m_isExitButtonPressed)
    {
        m_context->m_window->close();
    }
}

void GameOver::Draw()
{
    m_context->m_window->clear(sf::Color::Red);
    m_context->m_window->draw(m_gameOverTitle);
    m_context->m_window->draw(m_retryButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->display();
}
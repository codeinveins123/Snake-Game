#include "PauseGame.hpp"

#include <SFML/Window/Event.hpp>

PauseGame::PauseGame(std::shared_ptr<Context>& context) :
    m_context(context)
{
}

PauseGame::~PauseGame()
{

}

void PauseGame::Init()
{
    //GameTitle
    m_pauseTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_pauseTitle.setString("Game Paused");
    m_pauseTitle.setCharacterSize(120);
    m_pauseTitle.setOrigin(m_pauseTitle.getLocalBounds().width / 2,
                            m_pauseTitle.getLocalBounds().height / 2);
    m_pauseTitle.setPosition(m_context->m_window->getSize().x / 2,
                            m_context->m_window->getSize().y / 2);      
    m_pauseTitle.setFillColor(sf::Color::Black);                       
}

void PauseGame::ProcessInput()
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
                case sf::Keyboard::Escape: case sf::Keyboard::Space:
                {
                    m_context->m_states->PopCurrent();
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

void PauseGame::Update(sf::Time deltaTime)
{
}

void PauseGame::Draw()
{
    m_context->m_window->draw(m_pauseTitle);
    m_context->m_window->display();
}

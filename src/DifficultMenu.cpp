#include "DifficultMenu.hpp"
#include "GamePlay.hpp"

#include <SFML/Window/Event.hpp>

DifficultMenu::DifficultMenu(std::shared_ptr<Context>& context)
        : m_context(context),
        m_isEasyButtonSelected(true), m_isNormalButtonSelected(false), m_isHardButtonSelected(false), m_isBackButtonSelected(false),
        m_isEasyButtonPressed(false), m_isNormalButtonPressed(false), m_isHardButtonPressed(false), m_isBackButtonPressed(false)
{

}

DifficultMenu::~DifficultMenu()
{

}

void DifficultMenu::Init()
{
    //Title
    m_DifficultTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_DifficultTitle.setString("Select Difficulty");
    m_DifficultTitle.setOrigin(m_DifficultTitle.getLocalBounds().width / 2,
                               m_DifficultTitle.getLocalBounds().height / 2);
    m_DifficultTitle.setPosition(m_context->m_window->getSize().x / 2,
                            m_context->m_window->getSize().y / 2 - 150.f);
    //Easy
    m_easyButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_easyButton.setString("Easy");
    m_easyButton.setOrigin(m_easyButton.getLocalBounds().width / 2,
                          m_easyButton.getLocalBounds().height / 2);
    m_easyButton.setPosition(m_context->m_window->getSize().x / 2,
                            m_context->m_window->getSize().y / 2 - 50.f);
    m_easyButton.setCharacterSize(25);                            
    //Normal
    m_normalButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_normalButton.setString("Normal");
    m_normalButton.setOrigin(m_normalButton.getLocalBounds().width / 2,
                          m_normalButton.getLocalBounds().height / 2);
    m_normalButton.setPosition(m_context->m_window->getSize().x / 2,
                            m_context->m_window->getSize().y / 2 + 0.f);
    m_normalButton.setCharacterSize(25);
    //Hard
    m_hardButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_hardButton.setString("Hard");
    m_hardButton.setOrigin(m_hardButton.getLocalBounds().width / 2,
                          m_hardButton.getLocalBounds().height / 2);
    m_hardButton.setPosition(m_context->m_window->getSize().x / 2,
                            m_context->m_window->getSize().y / 2 + 50.f);
    m_hardButton.setCharacterSize(25);  
    //Back 
    m_backButton.setCharacterSize(50);
    m_backButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_backButton.setString(L"←");
    m_backButton.setOrigin(m_backButton.getLocalBounds().width / 2,
                          m_backButton.getLocalBounds().height / 2);
    m_backButton.setPosition(m_context->m_window->getSize().x / 2,
                            m_context->m_window->getSize().y / 2 + 100.f);
                     
}

void DifficultMenu::ProcessInput()
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
                    if(m_isEasyButtonSelected)
                    {
                        m_isBackButtonSelected = true;
                        m_isEasyButtonSelected = false;
                        m_context->m_assets->GetSound(SELECT_SOUND).play();
                    }
                    else if(m_isNormalButtonSelected)
                    {
                        m_isNormalButtonSelected = false;
                        m_isEasyButtonSelected = true;
                        m_context->m_assets->GetSound(SELECT_SOUND).play();
                    }
                    else if(m_isHardButtonSelected)
                    {
                        m_isNormalButtonSelected = true;
                        m_isHardButtonSelected = false;
                        m_context->m_assets->GetSound(SELECT_SOUND).play();
                    }
                    else
                    {
                        m_isHardButtonSelected = true;
                        m_isBackButtonSelected = false;
                        m_context->m_assets->GetSound(SELECT_SOUND).play();
                    }
                    break;
                }
                case sf::Keyboard::Down: case sf::Keyboard::S:
                {
                    if(m_isEasyButtonSelected)
                    {
                        m_isNormalButtonSelected = true;
                        m_isEasyButtonSelected = false;
                        m_context->m_assets->GetSound(SELECT_SOUND).play();
                    }
                    else if(m_isNormalButtonSelected)
                    {
                        m_isNormalButtonSelected = false;
                        m_isHardButtonSelected = true;
                        m_context->m_assets->GetSound(SELECT_SOUND).play();
                    }
                    else if(m_isHardButtonSelected)
                    {
                        m_isBackButtonSelected = true;
                        m_isHardButtonSelected = false;
                        m_context->m_assets->GetSound(SELECT_SOUND).play();
                    }
                    else
                    {
                        m_isEasyButtonSelected = true;
                        m_isBackButtonSelected = false;
                        m_context->m_assets->GetSound(SELECT_SOUND).play();
                    }
                    break;
                }
                case sf::Keyboard::Return: case sf::Keyboard::Space:
                {
                    m_context->m_assets->GetSound(SELECT_SOUND).play();
                    m_isEasyButtonPressed = false;
                    m_isNormalButtonPressed = false;
                    m_isHardButtonPressed = false;
                    m_isBackButtonPressed = false;

                    if(m_isEasyButtonSelected)
                    {
                        m_isEasyButtonPressed = true;
                    }
                    else if(m_isNormalButtonSelected)
                    {
                        m_isNormalButtonPressed = true;
                    }
                    else if(m_isHardButtonSelected)
                    {
                        m_isHardButtonPressed = true;
                    }
                    else if(m_isBackButtonSelected)
                    {
                        m_isBackButtonPressed = true;
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

void DifficultMenu::Update(sf::Time deltaTime)
{
    if(m_isEasyButtonSelected)
    {
        m_easyButton.setFillColor(sf::Color::Black);
        m_normalButton.setFillColor(sf::Color::White);
        m_backButton.setFillColor(sf::Color::White);
    }
    else if(m_isNormalButtonSelected)
    {
        m_normalButton.setFillColor(sf::Color::Black);
        m_easyButton.setFillColor(sf::Color::White);
        m_hardButton.setFillColor(sf::Color::White);
    }
    else if(m_isHardButtonSelected)
    {
        m_hardButton.setFillColor(sf::Color::Black);
        m_normalButton.setFillColor(sf::Color::White);
        m_backButton.setFillColor(sf::Color::White);
    }
    else
    {
        m_backButton.setFillColor(sf::Color::Black);
        m_easyButton.setFillColor(sf::Color::White);
        m_hardButton.setFillColor(sf::Color::White);
    }
    
    if(m_isEasyButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context, rand() % 3), true);
    }
    else if(m_isNormalButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context, rand() % 10 + 3), true);
    }
    else if(m_isHardButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context, rand() % 15 + 5), true);
    }
    else if(m_isBackButtonPressed)
    {
        m_context->m_states->PopCurrent();
        return;
    }
}

void DifficultMenu::Draw()
{
    m_context->m_window->clear(sf::Color::Cyan);
    m_context->m_window->draw(m_DifficultTitle);
    m_context->m_window->draw(m_easyButton);
    m_context->m_window->draw(m_normalButton);
    m_context->m_window->draw(m_hardButton);
    m_context->m_window->draw(m_backButton);
    m_context->m_window->display();
}

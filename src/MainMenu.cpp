#include "MainMenu.hpp"
#include "GamePlay.hpp"

#include <SFML/Window/Event.hpp>

MainMenu::MainMenu(std::shared_ptr<Context>& context)
    : m_context(context), m_isPlayButtonSelected(true), m_isExitButtonSelected(false),
    m_isExitButtonPressed(false), m_isPlayButtonPressed(false)
{

}

MainMenu::~MainMenu()
{

}

void MainMenu::Init()
{
    m_context->m_assets->AddFont(MAIN_FONT, "../assets/fonts/Anton/Anton-Regular.ttf");
    //GameTitle
    m_gameTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameTitle.setString("Snake Game");
    m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2,
                          m_gameTitle.getLocalBounds().height / 2);
    m_gameTitle.setPosition(m_context->m_window->getSize().x / 2,
                            m_context->m_window->getSize().y / 2 - 150.f);
    //Play
    m_playButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_playButton.setString("Play");
    m_playButton.setOrigin(m_playButton.getLocalBounds().width / 2,
                          m_playButton.getLocalBounds().height / 2);
    m_playButton.setPosition(m_context->m_window->getSize().x / 2,
                            m_context->m_window->getSize().y / 2 - 25.f);
    m_playButton.setCharacterSize(20);                            
    //Exit
    m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_exitButton.setString("Exit");
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2,
                          m_exitButton.getLocalBounds().height / 2);
    m_exitButton.setPosition(m_context->m_window->getSize().x / 2,
                            m_context->m_window->getSize().y / 2 + 25.f);
    m_exitButton.setCharacterSize(20);          
    
    m_context->m_assets->AddSound(FUNNY_MUSIC, "../assets/music/FunnyMusic.ogg");
    m_context->m_assets->AddSound(SELECT_SOUND, "../assets/music/SelectSound.ogg");
    m_context->m_assets->GetSound(FUNNY_MUSIC).setVolume(80.f);
    m_context->m_assets->GetSound(FUNNY_MUSIC).play();
    m_context->m_assets->GetSound(FUNNY_MUSIC).setLoop(true);
}

void MainMenu::ProcessInput()
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
                    if(!m_isPlayButtonSelected)
                    {
                        m_isPlayButtonSelected = true;
                        m_isExitButtonSelected = false;
                        m_context->m_assets->GetSound(SELECT_SOUND).play();
                    }
                    break;
                }
                    
                case sf::Keyboard::Down: case sf::Keyboard::S:
                {
                    if(!m_isExitButtonSelected)
                    {
                        m_isPlayButtonSelected = false;
                        m_isExitButtonSelected = true;
                        m_context->m_assets->GetSound(SELECT_SOUND).play();
                    }
                    break;
                }
                case sf::Keyboard::Return: case sf::Keyboard::Space:
                {
                    m_context->m_assets->GetSound(SELECT_SOUND).play();
                    m_isPlayButtonPressed = false;
                    m_isExitButtonPressed = false;

                    if(m_isPlayButtonSelected)
                    {
                        m_isPlayButtonPressed = true;
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

void MainMenu::Update(sf::Time deltaTime)
{
    if(m_isPlayButtonSelected)
    {
        m_playButton.setFillColor(sf::Color::Black);
        m_exitButton.setFillColor(sf::Color::White);
    }
    else
    {
        m_exitButton.setFillColor(sf::Color::Black);
        m_playButton.setFillColor(sf::Color::White);
    }

    if(m_isPlayButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<DifficultMenu>(m_context), false);
        m_isPlayButtonPressed = false;
    }
    else if(m_isExitButtonPressed)
    {
        m_context->m_window->close();
    }
}

void MainMenu::Draw()
{
    m_context->m_window->clear(sf::Color::Cyan);
    m_context->m_window->draw(m_gameTitle);
    m_context->m_window->draw(m_playButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->display();
}
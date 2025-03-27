#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Game.hpp"

class DifficultMenu : public Engine::State
{
    private:
        std::shared_ptr<Context> m_context;
        sf::Text m_DifficultTitle;
        sf::Text m_easyButton;
        sf::Text m_normalButton;
        sf::Text m_hardButton;
        sf::Text m_backButton;


        bool m_isEasyButtonSelected;
        bool m_isEasyButtonPressed;
        bool m_isNormalButtonSelected;
        bool m_isNormalButtonPressed;
        bool m_isHardButtonSelected;
        bool m_isHardButtonPressed;
        bool m_isBackButtonSelected;
        bool m_isBackButtonPressed;
        
    public:
        DifficultMenu(std::shared_ptr<Context>& context);
        ~DifficultMenu();

        void Init() override;
        void ProcessInput() override;
        void Update(sf::Time deltaTime) override;
        void Draw() override;
};
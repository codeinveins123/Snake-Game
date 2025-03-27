#pragma once

#include <list>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Snake : public sf::Drawable
{
    private:
        std::list<sf::Sprite> m_body;
        std::list<sf::Sprite>::iterator m_head;
        std::list<sf::Sprite>::iterator m_tail;

    public:
        Snake();
        ~Snake();

        void Init(const sf::Texture& texture, const sf::Texture& textureHead);
        void Move(const sf::Vector2f& direction);
        bool IsOn(const sf::Sprite& other) const;
        bool IsOnBody(const sf::Sprite& other) const;
        bool IsSelfIntersecting() const;
        void GrowH(const sf::Vector2f& direction);
        void GrowT(const sf::Vector2f& direction);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        std::list<sf::Sprite>::iterator getTail() const;
        std::list<sf::Sprite>::iterator getHead() const;
        std::list<sf::Sprite>& getBody();
        
};
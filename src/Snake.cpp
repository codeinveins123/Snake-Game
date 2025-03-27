#include "Snake.hpp"



Snake::Snake() : m_body(std::list<sf::Sprite>(4))
{
    m_head = --m_body.end();
    m_tail = m_body.begin();
}

Snake::~Snake() 
{

}


void Snake::Init(const sf::Texture& texture, const sf::Texture& textureHead)
{
    float x = 32.f;
    for(auto& piece : m_body)
    {
        piece.setTexture(texture);
        piece.setPosition({x , 32.f});
        x += 32.f;
    }
    m_head->setTexture(textureHead);
}

void Snake::Move(const sf::Vector2f& direction)
{
    m_tail->setPosition(m_head->getPosition() + direction);
    m_head = m_tail;
    ++m_tail;

    if(m_tail == m_body.end())
    {
        m_tail = m_body.begin();
    }
}

bool Snake::IsOn(const sf::Sprite& other) const
{
    return other.getGlobalBounds().intersects(m_head->getGlobalBounds());
}

bool Snake::IsOnBody(const sf::Sprite& other) const
{
    for (auto it = m_body.begin(); it != m_body.end(); ++it)
    {
        if (it != m_head && other.getGlobalBounds().intersects(it->getGlobalBounds()))
        {
            return true;
        }
    }
    return false;
}

bool Snake::IsSelfIntersecting() const
{
    bool flag = false;

    for(auto piece = m_body.begin(); piece != m_body.end(); ++piece)
    {
        if(m_head != piece)
        {
            flag = IsOn(*piece);

            if(flag)
            {
                break;
            }
        }
    }
    return flag;
}

void Snake::GrowH(const sf::Vector2f& direction)
{
    sf::Sprite newPiece;
    newPiece.setTexture(*(m_body.begin()->getTexture()));
    newPiece.setPosition(m_head->getPosition() + direction);
    m_head = m_body.insert(++m_head, newPiece);
}

void Snake::GrowT(const sf::Vector2f& direction)
{
    sf::Sprite newPiece;
    newPiece.setTexture(*(m_body.begin()->getTexture()));

    // Новый сегмент появляется там, где раньше был старый `m_tail`
    newPiece.setPosition(m_tail->getPosition() - direction);

    // Вставляем перед `m_tail`, чтобы сохранить порядок
    m_tail = m_body.insert(m_tail, newPiece);
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(auto& piece : m_body)
    {
        target.draw(piece);
    }
}

std::list<sf::Sprite>::iterator Snake::getHead() const
{
    return m_head;
}

std::list<sf::Sprite>::iterator Snake::getTail() const
{
    return m_tail;
}

std::list<sf::Sprite>& Snake::getBody()
{
    return m_body;
}

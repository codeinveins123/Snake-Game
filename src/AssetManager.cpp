#include "AssetManager.hpp"

Engine::AssetManager::AssetManager()
{

}

Engine::AssetManager::~AssetManager()
{

}

void Engine::AssetManager::AddTexture(int id, const std::string& filePath, bool isRepeated)
{
    auto texture = std::make_unique<sf::Texture>();

    if(texture->loadFromFile(filePath))
    {   
        texture->setRepeated(isRepeated);
        m_textures[id] = std::move(texture);
    }
}

void Engine::AssetManager::AddFont(int id, const std::string& filePath)
{
    auto font = std::make_unique<sf::Font>();

    if(font->loadFromFile(filePath))
    {   
        m_fonts[id] = std::move(font);
    }
}

void Engine::AssetManager::AddSoundBuffer(int id, const std::string& filePath)
{
    auto buffer = std::make_unique<sf::SoundBuffer>();
    if(buffer->loadFromFile(filePath))
    {
        m_soundBuffers[id] = std::move(buffer);
    }
    auto sound = std::make_unique<sf::Sound>();
    sound->setBuffer(*m_soundBuffers[id]);
    m_sounds[id] = std::move(sound);
}

void Engine::AssetManager::AddSound(int id, const std::string& filePath)
{
    if(m_soundBuffers.find(id) == m_soundBuffers.end())
    {
        AddSoundBuffer(id, filePath);
    }
}

const sf::Texture &Engine::AssetManager::GetTexture(int id) const
{
    return *(m_textures.at(id).get());
}

const sf::Font &Engine::AssetManager::GetFont(int id) const
{
    return *(m_fonts.at(id).get());
}

const sf::SoundBuffer &Engine::AssetManager::GetSoundBuffer(int id) const
{
    return *(m_soundBuffers.at(id));
}

sf::Sound &Engine::AssetManager::GetSound(int id)
{
    return *(m_sounds.at(id));
}

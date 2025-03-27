#pragma once

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio.hpp>


namespace Engine
{
    class AssetManager
    {
        private:
        std::map<int, std::unique_ptr<sf::Texture>> m_textures;
        std::map<int, std::unique_ptr<sf::Font>> m_fonts;
        std::map<int, std::unique_ptr<sf::SoundBuffer>> m_soundBuffers;
        std::map<int, std::unique_ptr<sf::Sound>> m_sounds;

        public:
            AssetManager();
            ~AssetManager();

            void AddTexture(int id, const std::string& filePath, bool isRepeated = false);
            void AddFont(int id, const std::string& filePath);
            void AddSoundBuffer(int id, const std::string& filePath);
            void AddSound(int id, const std::string& filePath);

            const sf::Texture &GetTexture(int id) const;
            const sf::Font &GetFont(int id) const;
            const sf::SoundBuffer &GetSoundBuffer(int id) const;
            sf::Sound &GetSound(int id);
    };

}

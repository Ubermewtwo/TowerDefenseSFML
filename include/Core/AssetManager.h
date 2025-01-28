#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <unordered_map>

namespace sf
{
	class Texture;
}

class AssetManager
{
	public:

		static AssetManager* getInstance();

		~AssetManager() = default;

		// To-Do: Implement a clear()

		std::shared_ptr<sf::Texture> loadTexture(const char* assetPath);
		// To-Do: Implement a unloadTexture()

		std::shared_ptr<sf::Texture> getTexture(const char* assetPath) const;


	private:

		static AssetManager* a_instance;

		std::unordered_map<std::string, std::shared_ptr<sf::Texture>> m_texturePathToTexture;
};
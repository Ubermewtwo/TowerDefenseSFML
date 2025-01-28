#include <Core/AssetManager.h>
#include <SFML/Graphics/Texture.hpp>


AssetManager* AssetManager::a_instance{ nullptr };

AssetManager* AssetManager::getInstance()
{
	if (a_instance == nullptr)
	{
		a_instance = new AssetManager();
	}
	return a_instance;
}

std::shared_ptr<sf::Texture> AssetManager::loadTexture(const char* assetPath)
{
	auto it = m_texturePathToTexture.find(assetPath);
	if (it != m_texturePathToTexture.end())
	{
		return it->second; // Already loaded, reuse
	}
	else
	{
		std::shared_ptr<sf::Texture> newTexture = std::make_shared<sf::Texture>();
		const bool loadOk = newTexture->loadFromFile(assetPath);
		if (!loadOk)
		{
			return nullptr;
		}
		m_texturePathToTexture[assetPath] = newTexture;
		return newTexture; // just created a new one
	}
}

std::shared_ptr<sf::Texture> AssetManager::getTexture(const char* assetPath) const
{
	const auto it = m_texturePathToTexture.find(assetPath);
	return (it != m_texturePathToTexture.end()) ? it->second : nullptr;
}
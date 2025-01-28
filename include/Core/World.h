#pragma once

#include <Core/EnemySpawner.h>
#include <Core/ScreenInputManager.h>
#include <Core/TowerManager.h>
#include <Core/SoundManager.h>
#include <SFML/Audio.hpp>
#include <cstdint>
#include <vector>
#include <string>
#include <memory>

namespace sf
{
	class RenderWindow;
}

namespace tmx
{
	class Map;
}

class MapLayer;
class ObjectLayer;

class World
{
	public:
		struct LevelData {
			std::string WavesPath;
			std::string TilemapPath;
			float startingMoney;
			int startingLives;
		};

		static World* getInstance();

		~World();

		bool init();
		bool loadLevel();
		bool unloadLevel();

		void update(uint32_t deltaMilliseconds);
		void render(sf::RenderWindow& window);

		void notifyInput(sf::Vector2f mousePos);

		void removeLives(int lives);
		int getCurrentLives() const { return m_currentLives; }
		std::shared_ptr<sf::SoundBuffer> getBuffer() const { return m_buffer; }

		void reloadLevel();
		void loadNextLevel();
		bool noMoreLevels() { return m_currentLevelIndex + 1 >= m_levels.size(); }

	private:
		static World* w_instance;


		std::vector<LevelData> m_levels = {
		{ "../data/EnemyWaves/Level1Waves.json", "../data/Levels/TowerDefense.tmx", 800.0f, 10 },
		{ "../data/EnemyWaves/Level2Waves.json", "../data/Levels/TowerDefense.tmx", 1200.0f, 15 }
		};

		LevelData* m_currentLevel;
		int m_currentLevelIndex = 0;

		// This is just an example. Think a good way to group the actors of your game. If they need any type of manager, etc...
		std::unique_ptr<SoundManager> m_soundManager{ nullptr };
		std::unique_ptr<EnemySpawner> m_enemySpawner{ nullptr };
		std::unique_ptr<ScreenInputManager> m_inputManager{ nullptr };
		std::unique_ptr<TowerManager> m_towerManager{ nullptr };

		// To-Do: This should be in its own class, something like "Level" should work
		tmx::Map* m_map{ nullptr };

		MapLayer* m_layerZero{ nullptr };
		MapLayer* m_layerOne{ nullptr };

		int m_maxLives { 10 };
		int m_currentLives { 0 };

		bool m_hasWon { false };
		bool m_hasLost { false };

		// I know this should be in a different class, but maybe later
		sf::Music m_music{};
		std::shared_ptr<sf::SoundBuffer> m_buffer { nullptr };
};
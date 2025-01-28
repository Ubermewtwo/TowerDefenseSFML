#pragma once

#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include <Core/EnemyFactory.h>
#include <SFML/Graphics.hpp>
#include <Gameplay/Enemy.h>
#include <memory>
using json = nlohmann::json;

inline void from_json(const nlohmann::json& j, EnemyType& enemy) {
	std::string enemyStr = j.get<std::string>();  // Get the string value
	if (enemyStr == "Slime") {
		enemy = EnemyType::Slime;
	}
	else if (enemyStr == "Orc") {
		enemy = EnemyType::Orc;
	}
	else if (enemyStr == "Wolf") {
		enemy = EnemyType::Wolf;
	}
	else if (enemyStr == "Wasp") {
		enemy = EnemyType::Wasp;
	}
	else {
		throw std::invalid_argument("Unknown EnemyType: " + enemyStr);
	}
}

struct WaveData {
    std::vector<EnemyType> enemiesToSpawn;
    float delayUntilNextWave;
};

inline void from_json(const nlohmann::json& j, WaveData& wave) {
	j.at("enemies").get_to(wave.enemiesToSpawn);  // Deserialize enemiesToSpawn
	j.at("delayUntilNextWave").get_to(wave.delayUntilNextWave);  // Deserialize delayUntilNextWave
}

struct LevelWavesData {
    std::vector<WaveData> waves;
};

inline void from_json(const nlohmann::json& j, LevelWavesData& level) {
	level.waves.clear();  // Clear any existing data
	for (const auto& waveJson : j.at("waves")) {  // Deserialize each wave
		WaveData wave;
		waveJson.get_to(wave);  // Deserialize into WaveData
		level.waves.push_back(wave);  // Add the wave to the list
	}
}

class EnemySpawner 
{
	public:
		static EnemySpawner* getInstance();

		~EnemySpawner() = default;

		bool init(const json& enemyWavesData, const std::vector<sf::Vector2f>& path);
		bool reset();
		void update(uint32_t deltaMilliseconds);

		std::shared_ptr<Enemy> getClosestEnemy(const sf::Vector2f& position, float range, bool canAttackFlyingEnemies) const;
		std::vector<std::shared_ptr<Enemy>> getEnemiesInRange(const sf::Vector2f& position, float range, bool canAttackFlyingEnemies) const;
		std::vector<std::shared_ptr<Enemy>> getSpawnedEnemies() const { return m_activeEnemies; }
		std::vector<sf::RectangleShape> getHealthBars() const { return m_healthBars; }
		bool getAllEnemiesSpawned() const { return m_allEnemiesSpawned; }

		void startWaves() { m_isSpawning = true; }

	private:
		static EnemySpawner* e_instance;

		std::unique_ptr<EnemyFactory> m_enemyFactory;
		std::vector<std::shared_ptr<Enemy>> m_activeEnemies;
		std::vector<sf::RectangleShape> m_healthBars;

		std::vector<sf::Vector2f> m_path;
		LevelWavesData m_enemyWavesData;

		std::shared_ptr<WaveData> m_currentWave { nullptr };
		const float m_delayPerEnemy{ 0.5f };
		float m_currentDelay{ 0.0f };
		int m_enemyIndex{ 0 };
		int m_waveIndex{ 0 };
		bool m_isSpawning{ false };
		bool m_allEnemiesSpawned{ false };

		void spawnEnemy(EnemyType enemyType);
};
#include <Core/AssetManager.h>
#include <Core/EnemySpawner.h>
#include <vector>
#include <string>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

EnemySpawner* EnemySpawner::e_instance{ nullptr };

EnemySpawner* EnemySpawner::getInstance()
{
	if (e_instance == nullptr)
	{
		std::cout << "EnemySpawner not instanced\n";
	}
	return e_instance;
}

void EnemySpawner::spawnEnemy(EnemyType enemyType)
{
	m_activeEnemies.push_back(m_enemyFactory->createEnemy(enemyType, m_path));

	sf::RectangleShape healthBar;
	healthBar.setSize(sf::Vector2f(30.f, 4.f)); // Initial size (width and height)
	healthBar.setFillColor(sf::Color::Green);
	healthBar.setOutlineColor(sf::Color::Black);
	healthBar.setOutlineThickness(1.f);

	// Position it above the enemy
	healthBar.setPosition(m_activeEnemies[m_activeEnemies.size() - 1]->getSpritePosition().x - 15.f, m_activeEnemies[m_activeEnemies.size() - 1]->getSpritePosition().y - 20.f);

	// Add to the health bars list
	m_healthBars.push_back(healthBar);
}

std::shared_ptr<Enemy> EnemySpawner::getClosestEnemy(const sf::Vector2f& position, float range, bool canAttackFlyingEnemies) const {
	std::shared_ptr<Enemy> closestEnemy = nullptr;
	float minDistance = range; // Set the initial minimum distance to the maxRange

	for (const auto& enemy : m_activeEnemies) {
		if (enemy) { // Ensure the pointer is valid
			if (enemy->isDying()) continue;
			if (enemy->isFlying() && !canAttackFlyingEnemies) continue;
			sf::Vector2f a = position;
			sf::Vector2f b = enemy->getPosition();

			float distance = std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));

			if (distance < minDistance) { // Only consider enemies within maxRange
				minDistance = distance;
				closestEnemy = enemy;
			}
		}
	}

	return closestEnemy;
}

std::vector<std::shared_ptr<Enemy>> EnemySpawner::getEnemiesInRange(const sf::Vector2f& position, float range, bool canAttackFlyingEnemies) const {
	std::vector<std::shared_ptr<Enemy>> enemiesInRange;
	float minDistance = range; // Set the initial minimum distance to the maxRange

	for (const auto& enemy : m_activeEnemies) {
		if (enemy) { // Ensure the pointer is valid
			if (enemy->isDying()) continue;
			if (enemy->isFlying() && !canAttackFlyingEnemies) continue;
			sf::Vector2f a = position;
			sf::Vector2f b = enemy->getPosition();

			float distance = std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));

			if (distance < minDistance) { // Only consider enemies within maxRange
				enemiesInRange.push_back(enemy);
			}
		}
	}

	return enemiesInRange;
}

bool EnemySpawner::init(const json& enemyWavesData, const std::vector<sf::Vector2f>& path)
{
	e_instance = this;

	m_enemyFactory = std::make_unique<EnemyFactory>();
	m_enemyFactory->init(path);

	try {
		// Deserialize the JSON data into m_enemyWavesData
		m_enemyWavesData = enemyWavesData.get<LevelWavesData>();  // This now works because of the custom from_json functions
	}
	catch (const std::exception& e) {
		std::cout << "Error deserializing wave data: " << e.what() << std::endl;
		return false;
	}

	if (m_enemyWavesData.waves.empty()) {
		std::cout << "No waves found in level data\n";
		return false;
	}
	else {
		m_currentWave = std::make_shared<WaveData>(m_enemyWavesData.waves[0]);
	}

	m_path = path;

	return true;
}

bool EnemySpawner::reset() {
	m_activeEnemies.clear();
	m_healthBars.clear();

	m_currentWave = nullptr;
	m_currentDelay = 0.0f;
	m_enemyIndex = 0;
	m_waveIndex = 0;
	m_isSpawning = false;
	m_allEnemiesSpawned = false;

	return true;
}

void EnemySpawner::update(uint32_t deltaMilliseconds)
{
	float deltaSeconds = deltaMilliseconds / 1000.0f;

	m_currentDelay -= deltaSeconds;

	if (m_currentDelay <= 0 && m_isSpawning) {
		if (m_enemyIndex < m_currentWave->enemiesToSpawn.size()) {
			spawnEnemy(m_currentWave->enemiesToSpawn[m_enemyIndex]);

			m_enemyIndex++;
			m_currentDelay = m_delayPerEnemy;
		}
		else {
			m_waveIndex++;
			m_enemyIndex = 0;
			m_currentDelay = m_currentWave->delayUntilNextWave;

			if (m_waveIndex < m_enemyWavesData.waves.size()) {
				m_currentWave = std::make_shared<WaveData>(m_enemyWavesData.waves[m_waveIndex]);
			}
			else {
				m_isSpawning = false;
				m_allEnemiesSpawned = true;
			}
		}
	}

	for (size_t i = 0; i < m_activeEnemies.size(); ++i) {
		if (m_activeEnemies[i]->isDead()) {
			m_activeEnemies.erase(m_activeEnemies.begin() + i);
			m_healthBars.erase(m_healthBars.begin() + i); // Remove the corresponding health bar
			--i; // Adjust index to account for the removed element
		}
		else if (m_activeEnemies[i]->hasReachedTheEnd()) {
			m_activeEnemies.erase(m_activeEnemies.begin() + i);
			m_healthBars.erase(m_healthBars.begin() + i); // Remove the corresponding health bar
			--i; // Adjust index to account for the removed element
		}
	}

	for (auto& enemy : m_activeEnemies) {
		enemy->update(deltaMilliseconds);
	}

	for (size_t i = 0; i < m_activeEnemies.size(); ++i) {
		auto& enemy = m_activeEnemies[i];

		// Update health bar position
		sf::Vector2f enemyPosition = enemy->getSpritePosition();
		m_healthBars[i].setPosition(enemyPosition.x - 15.f, enemyPosition.y - 20.f);

		// Update health bar size based on health percentage
		float healthPercentage = enemy->getHealthPercentage();
		if (healthPercentage < 0.f) healthPercentage = 0.f;
		m_healthBars[i].setSize(sf::Vector2f(30.f * healthPercentage, 4.f));

		// Change color if health is low
		if (healthPercentage < 0.3f) {
			m_healthBars[i].setFillColor(sf::Color::Red);
		}
		else if (healthPercentage < 0.7f) {
			m_healthBars[i].setFillColor(sf::Color::Yellow);
		}
		else {
			m_healthBars[i].setFillColor(sf::Color::Green);
		}
	}
}
#include <Core/AssetManager.h>
#include <Core/World.h>
#include <Render/SFMLOrthogonalLayer.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <tmxlite/Object.hpp>
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <SFML/Audio.hpp>
using json = nlohmann::json;

World* World::w_instance{ nullptr };

World* World::getInstance()
{
	if (w_instance == nullptr)
	{
		std::cout << "World not instanced\n";
	}
	return w_instance;
}

World::~World() {
	delete m_map;
	delete m_layerZero;
	delete m_layerOne;
	delete m_currentLevel;
}

// Función para cargar el camino desde un tmx::Map
std::vector<sf::Vector2f> extractPointsFromMapLayer(const tmx::Map& map, const std::string& layerName) {
	std::vector<sf::Vector2f> path;

	// Buscar la capa de objetos con el nombre especificado
	for (const auto& layer : map.getLayers()) {
		if (layer->getType() == tmx::Layer::Type::Object && layer->getName() == layerName) {
			const auto& objectGroup = layer->getLayerAs<tmx::ObjectGroup>();

			// Extraer las posiciones de los objetos
			for (const auto& object : objectGroup.getObjects()) {
				path.push_back({ object.getPosition().x, object.getPosition().y });
			}
			break;
		}
	}

	if (path.empty()) {
		throw std::runtime_error("No se encontraron puntos en la capa: " + layerName);
	}

	return path;
}

bool World::init() {
	if (w_instance == nullptr) w_instance = this;

	m_currentLevel = &m_levels[m_currentLevelIndex];
	constexpr float millisecondsToSeconds = 1 / 1000.f;

	m_soundManager = std::make_unique<SoundManager>();
	m_enemySpawner = std::make_unique<EnemySpawner>();
	m_towerManager = std::make_unique<TowerManager>();
	m_inputManager = std::make_unique<ScreenInputManager>();

	return true;
}

bool World::loadLevel()
{
	//m_currentLives = m_maxLives;
	m_currentLives = m_currentLevel->startingLives;

	// File path to the JSON file
	//const std::string filePath = "../Data/EnemyWaves/Level1Waves.json";
	const std::string filePath = m_currentLevel->WavesPath;

	// Open the file
	std::ifstream inputFile(filePath);
	if (!inputFile.is_open()) {
		std::cerr << "Error: Could not open file " << filePath << "\n";
		return false;
	}

	// Parse the JSON data
	json jsonData;
	inputFile >> jsonData;

	// Close the file
	inputFile.close();

	// To-Do, Load level: this should have its own class
	m_map = new tmx::Map();
	//m_map->load("../Data/Levels/TowerDefense.tmx");
	m_map->load(m_currentLevel->TilemapPath);
	m_layerZero = new MapLayer(*m_map, 0);
	m_layerOne = new MapLayer(*m_map, 1);

	// Cargar los puntos del mapa
	std::vector<sf::Vector2f> path = extractPointsFromMapLayer(*m_map, "Path");
	std::vector<sf::Vector2f> buildingZones = extractPointsFromMapLayer(*m_map, "BuildingZones");

	m_soundManager->init();

	m_enemySpawner->init(jsonData, path);
	
	m_towerManager->init();
	m_towerManager->setCurrentMoney(m_currentLevel->startingMoney);
	
	m_inputManager->init(buildingZones);

	// Sound
	if (!m_music.openFromFile("../Data/Sounds/backgroundMusic.flac")) {
		return false;
	}

	m_music.setLoop(true);   // Enable looping
	m_music.setVolume(30.f); // Set volume
	m_music.play();
	
	return true;
}

bool World::unloadLevel() {
	m_enemySpawner->reset();
	m_towerManager->reset();
	m_inputManager->reset();
	m_hasLost = false;
	m_hasWon = false;
	return true;
}

void World::update(uint32_t deltaMilliseconds)
{
	m_layerZero->update(sf::milliseconds(deltaMilliseconds));
	m_layerOne->update(sf::milliseconds(deltaMilliseconds));

	m_inputManager->update(deltaMilliseconds);
	m_towerManager->update(deltaMilliseconds);
	m_enemySpawner->update(deltaMilliseconds);

	if (m_enemySpawner->getAllEnemiesSpawned() && m_enemySpawner->getSpawnedEnemies().empty() && !m_hasLost && !m_hasWon) {
		m_inputManager->showWinText();
		m_hasWon = true;
		m_music.stop();
		SoundManager::getInstance()->playWinSound();
	}
}

void World::render(sf::RenderWindow& window)
{
	window.draw(*m_layerZero);
	window.draw(*m_layerOne);

	std::vector < std::shared_ptr<AnimatedEntity>> entities;
	std::vector < std::shared_ptr<AnimatedEntity>> projectiles;
	std::vector<sf::RectangleShape> healthBars;

	for (const auto& enemy : m_enemySpawner->getSpawnedEnemies())
	{
		entities.push_back(enemy);
	}

	for (const auto& healthBar : m_enemySpawner->getHealthBars())
	{
		healthBars.push_back(healthBar);
	}

	for (const auto& tower : m_towerManager->getBuiltTowers())
	{
		entities.push_back(tower);
		for (auto& projectile : tower->getProjectiles())
		{
			projectiles.push_back(projectile);
		}
	}

	std::sort(entities.begin(), entities.end(), [](const auto& lhs, const auto& rhs) {
		return lhs->getSpritePosition().y < rhs->getSpritePosition().y;
	});
	std::sort(projectiles.begin(), projectiles.end(), [](const auto& lhs, const auto& rhs) {
		return lhs->getSpritePosition().y < rhs->getSpritePosition().y;
		});

	for (const auto& entity : entities) {
		entity->render(window);
	}

	for (const auto& projectile : projectiles) {
		projectile->render(window);
	}

	for (const auto& healthBar : healthBars) {
		if (healthBar.getSize().x == 30.f || healthBar.getSize().x == 0.f) continue;
		window.draw(healthBar);
	}

	m_inputManager->render(window);
}

void World::notifyInput(sf::Vector2f mousePos){
	m_inputManager->processInput(mousePos);
}

void World::removeLives(int lives) {
	m_currentLives -= lives;
	if (m_currentLives < 0) m_currentLives = 0;
	SoundManager::getInstance()->playLoseLifeSound();
	if (m_currentLives <= 0 && !m_hasLost && !m_hasWon) {
		m_inputManager->showLoseText();
		m_hasLost = true;
		m_music.stop();
		SoundManager::getInstance()->playLoseSound();
	}
}

void World::reloadLevel() {
	unloadLevel();
	loadLevel();
}

void World::loadNextLevel() {
	m_currentLevelIndex++;
	if (m_currentLevelIndex < m_levels.size()) {
		m_currentLevel = &m_levels[m_currentLevelIndex];
	}
	else
	{
		m_currentLevel = &m_levels[0];
	}
	unloadLevel();
	loadLevel();
}
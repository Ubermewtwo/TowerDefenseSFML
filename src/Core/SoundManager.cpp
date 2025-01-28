#include <Core/SoundManager.h>
#include <iostream>

SoundManager* SoundManager::s_instance{ nullptr };

SoundManager::~SoundManager() {
	delete s_instance;
}

SoundManager* SoundManager::getInstance() {
	if (s_instance == nullptr) {
		std::cout << "SoundManager not instanced\n";
	}
	return s_instance;
}

bool SoundManager::init() {
	s_instance = this;

	// Button pressed
	m_buttonPressedBuffer = sf::SoundBuffer();
	m_buttonPressedBuffer.loadFromFile("../Data/Sounds/buttonPressed.wav");

	// Waves start
	m_wavesStartBuffer = sf::SoundBuffer();
	m_wavesStartBuffer.loadFromFile("../Data/Sounds/wavesStart.wav");

	// Build
	m_buildBuffer = sf::SoundBuffer();
	m_buildBuffer.loadFromFile("../Data/Sounds/build.wav");

	// Upgrade
	m_upgradeBuffer = sf::SoundBuffer();
	m_upgradeBuffer.loadFromFile("../Data/Sounds/upgrade.wav");

	// Sell
	m_sellBuffer = sf::SoundBuffer();
	m_sellBuffer.loadFromFile("../Data/Sounds/sell.wav");

	// Lose life
	m_loseLifeBuffer = sf::SoundBuffer();
	m_loseLifeBuffer.loadFromFile("../Data/Sounds/loseLife.wav");

	// Win
	m_winBuffer = sf::SoundBuffer();
	m_winBuffer.loadFromFile("../Data/Sounds/win.wav");

	// Lose
	m_loseBuffer = sf::SoundBuffer();
	m_loseBuffer.loadFromFile("../Data/Sounds/lose.wav");

	// Slime death
	sf::SoundBuffer slimeDeathBuffer = sf::SoundBuffer();
	slimeDeathBuffer.loadFromFile("../Data/Sounds/slimeDeath.wav");
	m_enemyDeathBuffers[EnemyType::Slime] = slimeDeathBuffer;

	// Orc death
	sf::SoundBuffer orcDeathBuffer = sf::SoundBuffer();
	orcDeathBuffer.loadFromFile("../Data/Sounds/orcDeath.wav");
	m_enemyDeathBuffers[EnemyType::Orc] = orcDeathBuffer;

	// Wolf death
	sf::SoundBuffer wolfDeathBuffer = sf::SoundBuffer();
	wolfDeathBuffer.loadFromFile("../Data/Sounds/wolfDeath.wav");
	m_enemyDeathBuffers[EnemyType::Wolf] = wolfDeathBuffer;

	// Wasp death
	sf::SoundBuffer waspDeathBuffer = sf::SoundBuffer();
	waspDeathBuffer.loadFromFile("../Data/Sounds/waspDeath.wav");
	m_enemyDeathBuffers[EnemyType::Wasp] = waspDeathBuffer;

	// Archer tower attack
	sf::SoundBuffer archerTowerAttackBuffer = sf::SoundBuffer();
	archerTowerAttackBuffer.loadFromFile("../Data/Sounds/archerTowerAttack.wav");
	m_towerAttackBuffers[TowerType::Archer] = archerTowerAttackBuffer;

	// Mage tower attack
	sf::SoundBuffer mageTowerAttackBuffer = sf::SoundBuffer();
	mageTowerAttackBuffer.loadFromFile("../Data/Sounds/mageTowerAttack.wav");
	m_towerAttackBuffers[TowerType::Mage] = mageTowerAttackBuffer;

	// Catapult tower attack
	sf::SoundBuffer catapultTowerAttackBuffer = sf::SoundBuffer();
	catapultTowerAttackBuffer.loadFromFile("../Data/Sounds/catapultTowerAttack.wav");
	m_towerAttackBuffers[TowerType::Catapult] = catapultTowerAttackBuffer;

	// Archer tower projectile hit
	sf::SoundBuffer archerTowerProjectileHitBuffer = sf::SoundBuffer();
	archerTowerProjectileHitBuffer.loadFromFile("../Data/Sounds/archerTowerProjectileHit.wav");
	m_towerProjectileHitBuffers[TowerType::Archer] = archerTowerProjectileHitBuffer;

	// Mage tower projectile hit
	sf::SoundBuffer mageTowerProjectileHitBuffer = sf::SoundBuffer();
	mageTowerProjectileHitBuffer.loadFromFile("../Data/Sounds/mageTowerProjectileHit.wav");
	m_towerProjectileHitBuffers[TowerType::Mage] = mageTowerProjectileHitBuffer;

	// Catapult tower projectile hit
	sf::SoundBuffer catapultTowerProjectileHitBuffer = sf::SoundBuffer();
	catapultTowerProjectileHitBuffer.loadFromFile("../Data/Sounds/catapultTowerProjectileHit.wav");
	m_towerProjectileHitBuffers[TowerType::Catapult] = catapultTowerProjectileHitBuffer;

	return true;
}

void SoundManager::playSound(const sf::SoundBuffer& buffer) {
	// Clean up stopped sounds
	cleanupSounds();

	// Add a new sound to the list
	m_activeSounds.emplace_back(std::make_unique<sf::Sound>());

	// Set its buffer and play it
	m_activeSounds[m_activeSounds.size() - 1]->setBuffer(buffer);
	m_activeSounds[m_activeSounds.size() - 1]->setVolume(20.0f);
	m_activeSounds[m_activeSounds.size() - 1]->play();
}

void SoundManager::cleanupSounds() {
	
	m_activeSounds.erase(
		std::remove_if(
			m_activeSounds.begin(),
			m_activeSounds.end(),
			[](const std::unique_ptr<sf::Sound>& sound) {
				return sound->getStatus() == sf::Sound::Stopped;
			}
		),
		m_activeSounds.end()
	);
}

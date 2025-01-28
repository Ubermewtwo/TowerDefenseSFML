#include <Core/AssetManager.h>
#include <Core/EnemySpawner.h>
#include <Core/World.h>
#include <SFML/Audio.hpp>
#include <Core/ScreenInputManager.h>
#include <iostream>
#include <Core/SoundManager.h>

ScreenInputManager::~ScreenInputManager() {
	delete m_selectedBuildingZone;
}

bool isPointInRect(const sf::Vector2f& point, const sf::RectangleShape& rect) {
	sf::FloatRect bounds = rect.getGlobalBounds();
	return bounds.contains(point);
}

void ScreenInputManager::createTower(TowerType towerType) {

	if (TowerManager::getInstance()->createTower(m_selectedBuildingZone->zoneRect.getPosition(), towerType, m_selectedBuildingZone->index)) {
		SoundManager::getInstance()->playBuildSound();
		hideMenus(true);
	}
}

void ScreenInputManager::upgradeTower() {

	if (TowerManager::getInstance()->upgradeTower(m_selectedBuildingZone->index)) {
		SoundManager::getInstance()->playUpgradeSound();
		hideMenus(true);
	}
}

void ScreenInputManager::sellTower() {

	if (TowerManager::getInstance()->sellTower(m_selectedBuildingZone->index)) {
		SoundManager::getInstance()->playSellSound();
		hideMenus(true);
	}
}
void ScreenInputManager::showTowerMenu() {

	hideMenus(false);
	sf::Vector2f position = m_selectedBuildingZone->zoneRect.getPosition();

	if (TowerManager::getInstance()->getTower(m_selectedBuildingZone->index) == nullptr) {
		m_towerSelected = false;

		if (TowerManager::getInstance()->getCurrentMoney() < 70.f) {
			m_buildMenuZones[0].zoneRect.setFillColor(sf::Color::Red);
		}
		else {
			m_buildMenuZones[0].zoneRect.setFillColor(sf::Color::White);
		}
		if (TowerManager::getInstance()->getCurrentMoney() < 100.f) {
			m_buildMenuZones[1].zoneRect.setFillColor(sf::Color::Red);
		}
		else {
			m_buildMenuZones[1].zoneRect.setFillColor(sf::Color::White);
		}
		if (TowerManager::getInstance()->getCurrentMoney() < 125.f) {
			m_buildMenuZones[2].zoneRect.setFillColor(sf::Color::Red);
		}
		else {
			m_buildMenuZones[2].zoneRect.setFillColor(sf::Color::White);
		}

		for (auto& zone : m_buildMenuZones) {
			zone.zoneRect.setPosition(position + zone.offset); // Set position with offset
			zone.icon->setPosition(position + zone.offset);      // Align icon with the zone
			zone.isVisible = true;                              // Make the zone visible
		}
	}
	else {
		m_towerSelected = true;
		float towerRange = TowerManager::getInstance()->getTower(m_selectedBuildingZone->index)->getRange();
		m_towerRangeCircle.setRadius(towerRange);
		m_towerRangeCircle.setOrigin(towerRange, towerRange);
		m_towerRangeCircle.setPosition(position);

		if (TowerManager::getInstance()->getTower(m_selectedBuildingZone->index)->getNextTierCost() > TowerManager::getInstance()->getCurrentMoney()) {
			m_upgradeMenuZones[0].zoneRect.setFillColor(sf::Color::Red);
		}
		else if (TowerManager::getInstance()->getTower(m_selectedBuildingZone->index)->getCurrentTier() == 2) {
			m_upgradeMenuZones[0].zoneRect.setFillColor(sf::Color::Black);
		}
		else {
			m_upgradeMenuZones[0].zoneRect.setFillColor(sf::Color::White);
		}

		for (auto& zone : m_upgradeMenuZones) {
			zone.zoneRect.setPosition(position + zone.offset); // Set position with offset
			zone.icon->setPosition(position + zone.offset);      // Align icon with the zone
			zone.isVisible = true;                              // Make the zone visible
		}
	}
}

void ScreenInputManager::hideMenus(bool setZoneNull) {
	for (auto& zone : m_buildMenuZones) {
		zone.isVisible = false;
	}

	for (auto& zone : m_upgradeMenuZones) {
		zone.isVisible = false;
	}

	if (setZoneNull) {
		m_selectedBuildingZone = nullptr;
	}
	m_towerSelected = false;
}

void ScreenInputManager::startWaves() {
	EnemySpawner::getInstance()->startWaves();
	m_startWavesZone.isVisible = false;
	SoundManager::getInstance()->playWavesStartSound();
}

ScreenInputManager::MenuZoneData ScreenInputManager::createMenuZone(
	float size,
	sf::Color fillColor,
	std::function<void()> onClick,
	bool visibility,
	sf::Vector2f offset,
	std::string iconSpritePath,
	float iconSpriteSize,
	float iconSpriteVerticalOffset)
{
	MenuZoneData menuZoneData;

	sf::RectangleShape menuZone = sf::RectangleShape();
	menuZone.setSize({ size, size });
	menuZone.setOrigin({ size / 2.f, size / 2.f });
	menuZone.setFillColor(fillColor);

	menuZoneData.zoneRect = std::move(menuZone);
	menuZoneData.onClick = onClick;
	menuZoneData.isVisible = visibility; // Initially hidden
	menuZoneData.offset = offset;
	menuZoneData.icon = std::make_shared<sf::Sprite>();

	// Assign an icon (you can load different textures for each tower type)
	const char* path = iconSpritePath.c_str();
	std::shared_ptr<sf::Texture> iconTexture = AssetManager::getInstance()->loadTexture(path);

	menuZoneData.icon->setTexture(*iconTexture);
	menuZoneData.icon->setOrigin(iconSpriteSize / 2.f, iconSpriteSize / 2.f + iconSpriteVerticalOffset);
	menuZoneData.icon->setScale(1.0f, 1.0f); // Scale the icon to fit the zone

	menuZoneData.icon->setTextureRect(sf::IntRect(
		0,
		0,
		iconSpriteSize,
		iconSpriteSize
	));

	return menuZoneData;
}
bool ScreenInputManager::init(const std::vector<sf::Vector2f>& buildingZones) {

	if (!m_font.loadFromFile("../Data/Fonts/arial.ttf")) {
		std::cerr << "Failed to load font\n";
	}

	// Create the tower range circle
	m_towerRangeCircle = sf::CircleShape();
	m_towerRangeCircle.setOutlineColor(sf::Color::Yellow);
	m_towerRangeCircle.setOutlineThickness(2.f);
	m_towerRangeCircle.setFillColor(sf::Color::Transparent);

	// Create the text object
	m_moneyText.setFont(m_font);               // Set the font
	m_moneyText.setString("Money: 100");     // Initial string
	m_moneyText.setCharacterSize(24);        // Set text size
	m_moneyText.setFillColor(sf::Color::White); // Set text color
	m_moneyText.setPosition(10.f, 10.f);     // Set position on the screen

	m_livesText.setFont(m_font);               // Set the font
	m_livesText.setString("Lives: 100");     // Initial string
	m_livesText.setCharacterSize(24);        // Set text size
	m_livesText.setFillColor(sf::Color::White); // Set text color
	m_livesText.setPosition(840.f, 10.f);     // Set position on the screen

	int zoneIndex = 0;
	for (sf::Vector2f zone : buildingZones) {
		BuildingZoneData buildingZoneData;

		sf::RectangleShape buildingZoneRect = sf::RectangleShape();
		buildingZoneRect.setPosition(zone.x, zone.y);
		buildingZoneRect.setSize({ 64.f, 64.f }); 
		buildingZoneRect.setOrigin({ 32.f, 32.f });
		buildingZoneRect.setFillColor(sf::Color::Green);

		buildingZoneData.zoneRect = buildingZoneRect;
		buildingZoneData.onClick = [&]() { showTowerMenu(); };
		buildingZoneData.index = zoneIndex;

		m_buildingZones.push_back(std::move(buildingZoneData));
		zoneIndex++;
	}

	// build menu zones
	std::vector<sf::Vector2f> offsets = { {0.f, -80.f}, {-80.f, 0.f}, {80.f, 0.f}, {0.f, 80.f} };

	m_buildMenuZones.push_back(createMenuZone(40.f, sf::Color::White, [this]() { createTower(TowerType::Archer); }, false, offsets[0], "../Data/Images/UI/TowerIcons/Archer.png", 48.f, -4.f));
	m_buildMenuZones.push_back(createMenuZone(40.f, sf::Color::White, [this]() { createTower(TowerType::Mage); }, false, offsets[1], "../Data/Images/UI/TowerIcons/Mage.png", 48.f, -4.f));
	m_buildMenuZones.push_back(createMenuZone(40.f, sf::Color::White, [this]() { createTower(TowerType::Catapult); }, false, offsets[2], "../Data/Images/UI/TowerIcons/Catapult.png", 48.f, 5.f));
	m_buildMenuZones.push_back(createMenuZone(40.f, sf::Color::White, [this]() { hideMenus(true); }, false, offsets[3], "../Data/Images/UI/TowerIcons/Close.png", 48.f, 0.f));

	m_upgradeMenuZones.push_back(createMenuZone(40.f, sf::Color::White, [this]() { upgradeTower(); }, false, offsets[0], "../Data/Images/UI/TowerIcons/Upgrade.png", 48.f, 0.f));
	m_upgradeMenuZones.push_back(createMenuZone(40.f, sf::Color::White, [this]() { sellTower(); }, false, offsets[2], "../Data/Images/UI/TowerIcons/Sell.png", 48.f, 0.f));
	m_upgradeMenuZones.push_back(createMenuZone(40.f, sf::Color::White, [this]() { hideMenus(true); }, false, offsets[3], "../Data/Images/UI/TowerIcons/Close.png", 48.f, 0.f));

	m_startWavesZone = createMenuZone(40.f, sf::Color::Yellow, [this]() { startWaves(); }, true, sf::Vector2f(0.f, 0.f), "../Data/Images/UI/TowerIcons/WavesStart.png", 48.f, 0.f);
	m_startWavesZone.zoneRect.setPosition(40.f, 80.f);
	m_startWavesZone.icon->setPosition(40.f, 80.f);

	// Create the victory text
	m_victoryText.setFont(m_font);
	m_victoryText.setString("Victory!");
	m_victoryText.setCharacterSize(48);
	m_victoryText.setFillColor(sf::Color::Green);
	m_victoryText.setPosition(400.f, 100.f); // Adjust as needed

	// Create the defeat text
	m_defeatText.setFont(m_font);
	m_defeatText.setString("Defeat!");
	m_defeatText.setCharacterSize(48);
	m_defeatText.setFillColor(sf::Color::Red);
	m_defeatText.setPosition(400.f, 100.f); // Adjust as needed
	//m_defeatText.setOrigin();

	// Create retry level zone
	m_retryLevelZone = createMenuZone(120.f, sf::Color::White, [this]() { World::getInstance()->reloadLevel(); }, false, sf::Vector2f(0.f, 0.f), "../Data/Images/UI/TowerIcons/retryIcon.png", 48.f, 0.f);
	m_retryLevelZone.zoneRect.setPosition(480.f, 400.f);
	m_retryLevelZone.icon->setPosition(480.f, 400.f);

	// Create next level zone
	m_nextLevelZone = createMenuZone(120.f, sf::Color::White, [this]() { World::getInstance()->loadNextLevel(); }, false, sf::Vector2f(0.f, 0.f), "../Data/Images/UI/TowerIcons/nextLevelIcon.png", 48.f, 0.f);
	m_nextLevelZone.zoneRect.setPosition(480.f, 400.f);
	m_nextLevelZone.icon->setPosition(480.f, 400.f);

	return true;
}

bool ScreenInputManager::reset() {
	m_buildingZones.clear();
	m_selectedBuildingZone = nullptr;
	m_towerSelected = false;
	m_levelEnded = false;

	return true;
}

void ScreenInputManager::update(uint32_t deltaMilliseconds) {
	m_moneyText.setString("Money: " + std::to_string((int)TowerManager::getInstance()->getCurrentMoney())); // getCurrentMoney returns a float
	m_livesText.setString("Lives: " + std::to_string(World::getInstance()->getCurrentLives())); // getCurrentMoney returns a float
}

void ScreenInputManager::render(sf::RenderWindow& window) {
	
	//temporal
	for (auto& zone : m_buildingZones) {
		//window.draw(zone.zoneRect);
	}

	//permanent
	if (m_towerSelected) {
		window.draw(m_towerRangeCircle);
	}

	for (auto& zone : m_buildMenuZones) {
		if (zone.isVisible == false) continue;
		window.draw(zone.zoneRect);
		if (zone.icon != nullptr) {
			window.draw(*zone.icon);
		}
	}

	for (auto& zone : m_upgradeMenuZones) {
		if (zone.isVisible == false) continue;
		window.draw(zone.zoneRect);
		if (zone.icon != nullptr) {
			window.draw(*zone.icon);
		}
	}

	if (m_startWavesZone.isVisible) {
		window.draw(m_startWavesZone.zoneRect);
		if (m_startWavesZone.icon != nullptr) {
			window.draw(*m_startWavesZone.icon);
		}
	}

	if (m_nextLevelZone.isVisible) {
		window.draw(m_nextLevelZone.zoneRect);
		if (m_nextLevelZone.icon != nullptr) {
			window.draw(*m_nextLevelZone.icon);
		}
	}

	if (m_retryLevelZone.isVisible) {
		window.draw(m_retryLevelZone.zoneRect);
		if (m_retryLevelZone.icon != nullptr) {
			window.draw(*m_retryLevelZone.icon);
		}
	}

	window.draw(m_moneyText);
	window.draw(m_livesText);
	if (m_nextLevelZone.isVisible) window.draw(m_victoryText);
	if (m_retryLevelZone.isVisible) window.draw(m_defeatText);
}

void ScreenInputManager::processInput(const sf::Vector2f& mousePos) {

	if (m_nextLevelZone.isVisible) {
		if (isPointInRect(mousePos, m_nextLevelZone.zoneRect)) {
			m_lastMousePos = mousePos;
			m_nextLevelZone.onClick();
			return;
		}
	}

	if (m_retryLevelZone.isVisible) {
		if (isPointInRect(mousePos, m_retryLevelZone.zoneRect)) {
			m_lastMousePos = mousePos;
			m_retryLevelZone.onClick();
			return;
		}
	}

	if (m_levelEnded) return;

	if (m_startWavesZone.isVisible) {
		if (isPointInRect(mousePos, m_startWavesZone.zoneRect)) {
			m_lastMousePos = mousePos;
			m_startWavesZone.onClick();
			return;
		}
	}

	for (auto& zone : m_upgradeMenuZones) {
		if (zone.isVisible == false) continue;
		if (isPointInRect(mousePos, zone.zoneRect)) {
			m_lastMousePos = mousePos;
			zone.onClick();
			return;
		}
	}

	for (auto& zone : m_buildMenuZones) {
		if (zone.isVisible == false) continue;
		if (isPointInRect(mousePos, zone.zoneRect)) {
			m_lastMousePos = mousePos;
			zone.onClick();
			return;
		}
	}

	for (auto& zone : m_buildingZones) {
		if (isPointInRect(mousePos, zone.zoneRect)) {
			m_lastMousePos = mousePos;
			m_selectedBuildingZone = &zone;
			zone.onClick();
			SoundManager::getInstance()->playButtonPressedSound();
			return;
		}
	}
}

void ScreenInputManager::showWinText() {
	m_levelEnded = true;
	if (World::getInstance()->noMoreLevels()) {
		m_nextLevelZone.onClick = [this]() {};
	}
	m_nextLevelZone.isVisible = true;
}

void ScreenInputManager::showLoseText() {
	m_levelEnded = true;
	m_retryLevelZone.isVisible = true;
}
#pragma once

#include <Gameplay/Tower.h>
#include <Core/TowerManager.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <map>
#include <string>
#include <functional>

class ScreenInputManager
{
public:
	struct InputZoneData 
	{
		sf::RectangleShape zoneRect;
		std::function<void()> onClick;
	};

	struct BuildingZoneData : InputZoneData
	{
		int index{ -1 };
	};

	struct MenuZoneData : InputZoneData
	{
		bool isVisible{ false };
		sf::Vector2f offset{ 0, 0 };
		std::shared_ptr<sf::Sprite> icon{ nullptr }; // Icon representing the tower type
	};

	~ScreenInputManager();

	bool init(const std::vector<sf::Vector2f>& buildingZones);
	bool reset();
	void update(uint32_t deltaMilliseconds);
	void render(sf::RenderWindow& window);

	void processInput(const sf::Vector2f& mousePos);

	void showWinText();
	void showLoseText();

private:

	std::vector<BuildingZoneData> m_buildingZones;
	std::vector<MenuZoneData> m_buildMenuZones;
	std::vector<MenuZoneData> m_upgradeMenuZones;

	MenuZoneData m_startWavesZone;

	sf::CircleShape m_towerRangeCircle;
	bool m_towerSelected{ false };
	sf::Font m_font;
	sf::Text m_moneyText;
	sf::Text m_livesText;

	sf::Text m_victoryText;
	MenuZoneData m_retryLevelZone;
	sf::Text m_defeatText;
	MenuZoneData m_nextLevelZone;
	bool m_levelEnded{ false };

	sf::Vector2f m_lastMousePos{ 0, 0 };
	BuildingZoneData* m_selectedBuildingZone { nullptr };

	sf::Sound m_buyOrUpgradeTowerSound;
	sf::Sound m_sellTowerSound;

	void createTower(TowerType towerType);
	void upgradeTower();
	void sellTower();
	void showTowerMenu();
	void hideMenus(bool setZoneNull);
	void startWaves();

	MenuZoneData createMenuZone(
		float size, 
		sf::Color fillColor,
		std::function<void()> onClick,
		bool visibility,
		sf::Vector2f offset,
		std::string iconSpritePath,
		float iconSpriteSize,
		float iconSpriteVerticalOffset);
};
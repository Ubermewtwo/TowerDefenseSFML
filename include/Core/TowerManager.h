#pragma once

#include <Gameplay/Tower.h>
#include <Core/TowerFactory.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <map>
#include <string>
#include <functional>
#include <memory>

class TowerManager
{
public:
	static TowerManager* getInstance();

	~TowerManager() = default;

	bool init();
	bool reset();
	void update(uint32_t deltaMilliseconds);

	bool createTower(sf::Vector2f position, TowerType towerType, int index);
	bool upgradeTower(int index);
	bool sellTower(int index);
	std::shared_ptr<Tower> getTower(int index) const;
	float getCurrentMoney() const { return m_money; }
	void setCurrentMoney(float value) { m_money = value; }

	void addKillMoney(float money) { m_money += money; }

	std::vector<std::shared_ptr<Tower>> getBuiltTowers() const {
		std::vector<std::shared_ptr<Tower>> towers;
		for (const auto& [key, value] : m_towers) {
			towers.push_back(value);
		}
		return towers;
	}

	std::vector<std::shared_ptr<TowerProjectile>> getProjectiles() const {
		std::vector<std::shared_ptr<TowerProjectile>> projectiles;
		for (const auto& [key, value] : m_towers) {
			for (auto& projectile : value->getProjectiles()) {
				projectiles.push_back(projectile);
			}
		}
	}

private:
	static TowerManager* t_instance;

	float m_money{ 3000.f };
	std::unique_ptr<TowerFactory> m_towerFactory;
	std::map<int, std::shared_ptr<Tower>> m_towers;
};

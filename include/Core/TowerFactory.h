#pragma once

#include <Gameplay/Tower.h>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <map>
#include <utility>

class TowerFactory
{
public:
	~TowerFactory() = default;

	bool init();

	static std::pair<std::shared_ptr<Tower>, float> createTower(const TowerType& towerType, const sf::Vector2f& position, float currentMoney);
	static float getBuildCost(const TowerType& towerType) { return m_towerBuildCosts[towerType]; }
protected:
	static std::map<TowerType, float> m_towerBuildCosts;
	static std::map<TowerType, std::unique_ptr<Tower::TowerDescriptor>> m_towerDescriptors;
};
#include <Core/TowerManager.h>
#include <iostream>

TowerManager* TowerManager::t_instance{ nullptr };

TowerManager* TowerManager::getInstance()
{
	if (t_instance == nullptr)
	{
		std::cout << "TowerManager not instanced\n";
	}
	return t_instance;
}

bool TowerManager::createTower(sf::Vector2f position, TowerType towerType, int index) {
	auto towerPair = m_towerFactory->createTower(towerType, position, m_money);
	if (towerPair.first == nullptr) {
		return false;
	}
	else {
		m_money -= towerPair.second;
		m_towers[index] = towerPair.first;
		return true;
	}
}

bool TowerManager::upgradeTower(int index) {
	auto pair = m_towers.find(index);
	if (pair != m_towers.end()) {
		std::pair<bool, float> towerPair = pair->second->upgrade(m_money);
		if (towerPair.first) {
			m_money -= towerPair.second;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool TowerManager::sellTower(int index) {
	auto it = m_towers.find(index);
	if (it != m_towers.end()) {
		m_money += it->second->getSellPrice();
		m_towers.erase(it);
		return true;
	}
	else {
		return false;
	}
}

bool TowerManager::init() {
	t_instance = this;

	m_towerFactory = std::make_unique<TowerFactory>();
	m_towerFactory->init();

	return true;
}

bool TowerManager::reset() {
	m_towers.clear();

	return true;
}

void TowerManager::update(uint32_t deltaMilliseconds) {
	for (auto& pair : m_towers) {
		pair.second->update(deltaMilliseconds);
	}
}

std::shared_ptr<Tower> TowerManager::getTower(int index) const {
	auto it = m_towers.find(index);
	if (it != m_towers.end()) {
		return it->second;
	}
	else {
		return nullptr;
	}
}
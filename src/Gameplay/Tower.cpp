#include <Core/EnemySpawner.h>
#include <Gameplay/Tower.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <memory>

bool Tower::init(const TowerDescriptor& towerDescriptor)
{
	m_position = towerDescriptor.position;
	m_currentTier = 0;
	m_buildCost = towerDescriptor.buildCost;
	m_towerDataPerTier = towerDescriptor.towerDataPerTier;
	m_canAttackFlyingEnemies = towerDescriptor.canAttackFlyingEnemies;

	//create tower unit
	m_unit = std::make_unique<TowerUnit>();
	m_unit->init(m_towerDataPerTier[m_currentTier].towerUnitDescriptor, m_position + sf::Vector2f(0.f, m_towerDataPerTier[m_currentTier].unitVerticalOffset), m_towerDataPerTier[m_currentTier].attackDamage, m_canAttackFlyingEnemies);

	return AnimatedEntity::init(m_position, m_towerDataPerTier[0].towerAnimation);
}

void Tower::update(float deltaMilliseconds)
{
	float deltaSeconds = deltaMilliseconds / 1000.f;

	m_currentCooldown -= deltaSeconds;

	if (m_currentCooldown <= 0 && m_unit->isAttacking() == false) {
		std::shared_ptr<Enemy> closestEnemy = EnemySpawner::getInstance()->getClosestEnemy(m_position, m_towerDataPerTier[m_currentTier].attackRange, m_canAttackFlyingEnemies);
		
		if (closestEnemy != nullptr) {
			m_unit->attack(closestEnemy);
			m_currentCooldown = 1.f / m_towerDataPerTier[m_currentTier].attackSpeed;
		}
	}

	m_unit->update(deltaMilliseconds);
	AnimatedEntity::update(deltaMilliseconds);
}

void Tower::render(sf::RenderWindow& window) {

	AnimatedEntity::render(window);
	m_unit->render(window);
}

std::pair<bool, float> Tower::upgrade(float money)
{
	if (m_currentTier + 1 < m_towerDataPerTier.size()) {
		if (money >= m_towerDataPerTier[m_currentTier].nextTierCost) {
			float moneyConsumed = m_towerDataPerTier[m_currentTier].nextTierCost;
			m_currentTier++;
			setAnimation(m_towerDataPerTier[m_currentTier].towerAnimation);

			m_unit->upgrade(m_towerDataPerTier[m_currentTier].towerUnitDescriptor, m_position + sf::Vector2f(0.f, m_towerDataPerTier[m_currentTier].unitVerticalOffset), m_towerDataPerTier[m_currentTier].attackDamage);

			return std::pair<bool, float>(true, moneyConsumed);
		}
		else {
			return std::pair<bool, float>(false, 0.f);
		}
	}
	else {
		return std::pair<bool, float>(false, 0.f);
	}
}

float Tower::getSellPrice() const
{
	float sellPrice = 0.f;
	sellPrice += m_buildCost;

	for (int i = 0; i < m_currentTier; i++) {
		sellPrice += m_towerDataPerTier[i].nextTierCost;
	}

	//sellPrice /= 2.f;

	return sellPrice;
}
#pragma once

#include <Gameplay/Enemy.h>
#include <memory>
#include <map>
#include <iostream>

class EnemyFactory
{
public:
	~EnemyFactory() = default;

	bool init(const std::vector<sf::Vector2f>& path);

	static std::shared_ptr<Enemy> createEnemy(const EnemyType& enemyType, const std::vector<sf::Vector2f>& path);
protected:
	static std::map<EnemyType, std::unique_ptr<Enemy::EnemyDescriptor>> m_enemyDescriptors;
};
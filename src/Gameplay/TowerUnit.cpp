#include <Gameplay/TowerUnit.h>
#include <iostream>

Direction getEnemyDirection(const sf::Vector2f& point1, const sf::Vector2f& point2) {
	// Calculate the difference vector
	sf::Vector2f delta = point2 - point1;

	// Normalize the vector to determine its primary direction
	if (std::abs(delta.x) > std::abs(delta.y)) {
		// Horizontal movement dominates
		return (delta.x > 0) ? Direction::East : Direction::West;
	}
	else {
		// Vertical movement dominates
		return (delta.y > 0) ? Direction::South : Direction::North;
	}
}

void TowerUnit::attack(std::shared_ptr<Enemy> targetEnemy) {
	if (m_currentAction == Action::Attacking) return;

	m_targetEnemy = targetEnemy;

	m_hasSpawnedProjectile = false;
	m_currentFrame = 0;
	m_frameTimer = 0;
	m_currentAction = Action::Attacking;
	m_currentDirection = getEnemyDirection(m_position, targetEnemy->getPosition());
	setAnimation(m_animations[{m_currentAction, m_currentDirection}]);

	if (m_currentDirection == Direction::East) {
		m_sprite.setScale(-1.f, 1.f);
	}
	else {
		m_sprite.setScale(1.f, 1.f);
	}
}

bool TowerUnit::init(const TowerUnitDescriptor& descriptor, const sf::Vector2f& position, float damage, bool canAttackFlyingEnemies) {
	m_position = position;
	m_attackFrameIndex = descriptor.attackFrameIndex;
	m_animations = descriptor.animations;
	m_attackDamage = damage;
	m_projectileDescriptor = descriptor.projectileDescriptor;
	m_projectileSpawnVerticalOffset = descriptor.projectileSpawnVerticalOffset;
	m_canAttackFlyingEnemies = canAttackFlyingEnemies;

	m_currentAction = Action::Idle;
	m_currentDirection = Direction::West;

	setAnimation(m_animations[{m_currentAction, m_currentDirection}]);
	return AnimatedEntity::init(m_position, m_currentAnimation);
}

void TowerUnit::upgrade(const TowerUnitDescriptor& descriptor, const sf::Vector2f& position, float damage) {
	m_position = position;
	m_attackFrameIndex = descriptor.attackFrameIndex;
	m_animations = descriptor.animations;
	m_attackDamage = damage;
	m_projectileDescriptor = descriptor.projectileDescriptor;
	m_projectileSpawnVerticalOffset = descriptor.projectileSpawnVerticalOffset;

	setAnimation(m_animations[{m_currentAction, m_currentDirection}]);
}

void TowerUnit::update(float deltaMilliseconds) {

	if (m_currentAction == Action::Attacking) {
		if (m_currentFrame >= m_attackFrameIndex && m_hasSpawnedProjectile == false) {
			std::shared_ptr<TowerProjectile> projectile = std::make_shared<TowerProjectile>();
			projectile->init(m_projectileDescriptor, m_position + sf::Vector2f(0, m_projectileSpawnVerticalOffset), m_attackDamage, m_targetEnemy, m_canAttackFlyingEnemies);
			m_projectiles.push_back(projectile);

			m_hasSpawnedProjectile = true;
		}
		if (m_currentFrame >= m_currentAnimation->frameCount - 1) {
			m_currentAction = Action::Idle;
			setAnimation(m_animations[{m_currentAction, m_currentDirection}]);
		}
	}

	m_projectiles.erase(
		std::remove_if(
			m_projectiles.begin(),
			m_projectiles.end(),
			[](const std::shared_ptr<TowerProjectile>& projectile) {
				return projectile->isDead();
			}
		),
		m_projectiles.end()
	);

	for (auto& projectile : m_projectiles) {
		projectile->update(deltaMilliseconds);
	}

	AnimatedEntity::update(deltaMilliseconds);
}
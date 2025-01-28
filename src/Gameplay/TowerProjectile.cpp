#include <Gameplay/TowerProjectile.h>
#include <Core/EnemySpawner.h>
#include <Core/SoundManager.h>
#include <iostream>

bool TowerProjectile::init(const TowerProjectileDescriptor& descriptor, const sf::Vector2f& position, float damage, const std::shared_ptr<Enemy>& targetEnemy, bool canAttackFlyingEnemies) {

	m_position = position;
	m_originalPosition = m_position;
	m_isDead = false;
	m_maxHeight = descriptor.arch;
	m_elapsedTime = 0.f;
	m_towerType = descriptor.towerType;
	m_canAttackFlyingEnemies = canAttackFlyingEnemies;
	SoundManager::getInstance()->playTowerAttackSound(m_towerType);

	m_targetEnemy = targetEnemy;
	sf::Vector2f a = m_originalPosition;
	sf::Vector2f b = m_targetEnemy->getSpritePosition();
	float distance = std::sqrt((a.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
	m_travelTime = 100.f / descriptor.travelSpeed;

	m_currentAnimation = descriptor.travelAnimation;
	m_impactAnimation = descriptor.impactAnimation;
	setAnimation(descriptor.travelAnimation);
	m_attackDamage = damage;
	m_areaDamageRange = descriptor.areaDamageRange;

	m_sprite.setScale(2.f, 2.f);
	return AnimatedEntity::init(m_position, m_currentAnimation);
}

void TowerProjectile::update(float deltaMilliseconds) {

	if (m_targetEnemy == nullptr) {
		m_isDead = true;
		AnimatedEntity::update(deltaMilliseconds);
		return;
	}

	if (m_hasImpacted) {
		if (m_currentFrame >= m_impactAnimation->frameCount - 1) {
			m_isDead = true;
		}
		AnimatedEntity::update(deltaMilliseconds);
		return;
	}

	float deltaSeconds = deltaMilliseconds / 1000.f;

	m_elapsedTime += deltaSeconds;
	float t = m_elapsedTime / m_travelTime;

	if (t >= 1.f) {
		if (m_areaDamageRange > 0) {
			std::vector<std::shared_ptr<Enemy>> enemiesInRange = EnemySpawner::getInstance()->getEnemiesInRange(m_position, m_areaDamageRange, m_canAttackFlyingEnemies);

			for (auto& enemy : enemiesInRange) {
				enemy->receiveDamage(m_attackDamage);
			}
		}
		else {
			m_targetEnemy->receiveDamage(m_attackDamage);
		}

		m_hasImpacted = true;
		m_currentFrame = 0;
		m_sprite.setRotation(0);
		setAnimation(m_impactAnimation);
		SoundManager::getInstance()->playTowerProjectileHitSound(m_towerType);

		return;
	}

	m_lastPosition = m_position;
	float lerpedPositionX = m_originalPosition.x + t * (m_targetEnemy->getSpritePosition().x - m_originalPosition.x);
	float lerpedPositionY = m_originalPosition.y + t * (m_targetEnemy->getSpritePosition().y - m_originalPosition.y);

	float parabolicOffset = -4.0f * m_maxHeight * (t - 0.5f) * (t - 0.5f) + m_maxHeight;
	lerpedPositionY -= parabolicOffset;

	m_position = sf::Vector2f(lerpedPositionX, lerpedPositionY);

	// Rotation
	sf::Vector2f direction = getMovementDirection(m_position, m_lastPosition); // Get the normalized direction vector
	if (direction.x == 0.f && direction.y == 0.f) {
		return; // Avoid rotating for zero movement
	}

	// Calculate the angle in radians
	float angleRad = std::atan2(direction.y, direction.x);

	// Convert radians to degrees
	float angleDeg = angleRad * (180.f / static_cast<float>(3.14159265358979323846f));

	// Set the sprite's rotation
	m_sprite.setRotation(angleDeg - 90.f);

	AnimatedEntity::update(deltaMilliseconds);
}

sf::Vector2f normalize(const sf::Vector2f& vec) {
	float magnitude = std::sqrt(vec.x * vec.x + vec.y * vec.y);
	return (magnitude > 0) ? vec / magnitude : sf::Vector2f(0.f, 0.f);
}
sf::Vector2f TowerProjectile::getMovementDirection(sf::Vector2f a, sf::Vector2f b) const {
	return normalize(b - a);
}
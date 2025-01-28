#include <Gameplay/Enemy.h>
#include <Core/TowerManager.h>
#include <Core/World.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <random>
#include <iostream>

std::vector<sf::Vector2f> Enemy::m_path;

float getRandomFloat(float min, float max) {
	// Create a random device and generator
	std::random_device rd;
	std::mt19937 generator(rd());

	// Create a uniform real distribution
	std::uniform_real_distribution<float> distribution(min, max);

	// Generate and return the random float
	return distribution(generator);
}

// Función para calcular la distancia entre dos puntos
float distance(const sf::Vector2f& a, const sf::Vector2f& b) {
	return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

Direction getDirection(const sf::Vector2f& point1, const sf::Vector2f& point2) {
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

void Enemy::setTarget(const sf::Vector2f& target) {
	sf::Vector2f offsetTarget = target;
	m_currentDirection = getDirection(m_path[m_targetIndex - 1], m_path[m_targetIndex]);

	if (m_targetIndex + 1 < m_path.size()) {
		Direction nextDirection = getDirection(m_path[m_targetIndex], m_path[m_targetIndex + 1]);
		offsetTarget += m_targetOffsets.find({ m_currentDirection, nextDirection })->second;
	}

	switch (m_currentDirection) {
	case Direction::North:
		offsetTarget += sf::Vector2f(m_pathOffset, 0);
		break;
	case Direction::South:
		offsetTarget += sf::Vector2f(-m_pathOffset, 0);
		break;
	case Direction::East:
		offsetTarget += sf::Vector2f(0, m_pathOffset);
		break;
	case Direction::West:
		offsetTarget += sf::Vector2f(0, -m_pathOffset);
		break;
	}

	m_targetPos = offsetTarget;
	setAnimation(m_animations[{m_currentAction, m_currentDirection}]);

	if (m_currentDirection == Direction::East) {
		m_sprite.setScale(-1.f, 1.f);
	}
	else {
		m_sprite.setScale(1.f, 1.f);
	}
}

bool Enemy::init(const EnemyDescriptor& enemyDescriptor)
{
	if (m_path.empty()) m_path = enemyDescriptor.path;
	m_position = m_path[0];
	m_targetIndex = 1;
	m_currentDirection = getDirection(m_path[m_targetIndex - 1], m_path[m_targetIndex]);

	m_pathOffset = getRandomFloat(-20.0f, 20.0f);
	//m_pathOffset = 20;

	// Change spawn location based on offset
	switch (m_currentDirection) {
	case Direction::North:
		m_position += sf::Vector2f(m_pathOffset, 0);
		break;
	case Direction::South:
		m_position += sf::Vector2f(-m_pathOffset, 0);
		break;
	case Direction::East:
		m_position += sf::Vector2f(0, m_pathOffset);
		break;
	case Direction::West:
		m_position += sf::Vector2f(0, -m_pathOffset);
		break;
	}

	// Initialize target offsets
	m_targetOffsets = {
		{{Direction::North, Direction::North}, { 0, 0 }},
		{{Direction::North, Direction::South}, { 0, 0 }},
		{{Direction::North, Direction::East}, { 0, m_pathOffset }},
		{{Direction::North, Direction::West}, { 0, -m_pathOffset }},

		{{Direction::South, Direction::North}, { 0, 0 }},
		{{Direction::South, Direction::South}, { 0, 0 }},
		{{Direction::South, Direction::East}, { 0, m_pathOffset }},
		{{Direction::South, Direction::West}, { 0, -m_pathOffset }},

		{{Direction::East, Direction::North}, { m_pathOffset, 0 }},
		{{Direction::East, Direction::South}, { -m_pathOffset, 0 }},
		{{Direction::East, Direction::East}, { 0, 0 }},
		{{Direction::East, Direction::West}, { 0, 0 }},

		{{Direction::West, Direction::North}, { m_pathOffset, 0 }},
		{{Direction::West, Direction::South}, { -m_pathOffset, 0 }},
		{{Direction::West, Direction::East}, { 0, 0 }},
		{{Direction::West, Direction::West}, { 0, 0 }},
	};

	m_maxHealth = enemyDescriptor.maxHealth;
	m_currentHealth = m_maxHealth;
	m_movementSpeed = enemyDescriptor.movementSpeed;
	m_animations = enemyDescriptor.animations;
	m_killMoney = enemyDescriptor.killMoney;
	m_enemyType = enemyDescriptor.enemyType;

	setTarget(m_path[m_targetIndex]);

	return AnimatedEntity::init(m_position, m_currentAnimation);
}

void Enemy::update(float deltaMilliseconds)
{
	float deltaSeconds = deltaMilliseconds / 1000.f;

	if (m_currentAction == Action::Dying) {
		if (m_currentFrame == m_currentAnimation->frameCount - 1) {
			m_isDead = true;
		}
	}
	else if (m_targetIndex < m_path.size()) {
		sf::Vector2f direction = m_targetPos - m_position;

		float length = distance(m_position, m_targetPos);
		if (length > 0) {
			direction /= length; // Normalizar la dirección
		}

		// Mover al enemigo
		m_position += direction * m_movementSpeed * deltaSeconds;

		// Verificar si alcanzó el objetivo actual
		if (length < m_movementSpeed * deltaSeconds) {
			m_position = m_targetPos; // Ajustar posición al punto exacto
			m_targetIndex++; // Pasar al siguiente punto
			if (m_targetIndex < m_path.size()) {
				setTarget(m_path[m_targetIndex]);
			}
			else {
				m_hasReachedTheEnd = true;
				World::getInstance()->removeLives(1);
			}
		}
	}

	AnimatedEntity::update(deltaMilliseconds);
}

void Enemy::receiveDamage(float damage) {
	if (m_currentAction == Action::Dying) return; // No se puede recibir daño si el enemigo muere)

	m_currentHealth -= damage; // Subtract damage from current heal
	if (m_currentHealth <= 0) {
		m_currentAction = Action::Dying;
		m_currentFrame = 0;
		setAnimation(m_animations[{m_currentAction, m_currentDirection}]);
		SoundManager::getInstance()->playEnemyDeathSound(m_enemyType); // Play death sound for the ins
		TowerManager::getInstance()->addKillMoney(m_killMoney);
	}
}
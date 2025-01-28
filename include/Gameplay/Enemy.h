#pragma once

#include <Gameplay/AnimatedEntity.h>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <map>

enum class EnemyType { Slime, Orc, Wolf, Wasp };

class Enemy : public AnimatedEntity
{
	public:
		//template <typename PathType, typename SpeedType, typename AnimationMapType>
		struct EnemyDescriptor
		{
			std::vector<sf::Vector2f> path;
			float maxHealth{ .0f };
			float movementSpeed{ .0f };
			std::map<std::pair<Action, Direction>, std::shared_ptr<AnimationData>> animations;
			float killMoney;
			EnemyType enemyType;

			EnemyDescriptor(const std::vector<sf::Vector2f>& path = {}, float movementSpeed = 0.0f, const std::map<std::pair<Action, Direction>, std::shared_ptr<AnimationData>>& animations = {}, float killMoney = 0.0f, EnemyType enemyType = EnemyType::Slime)
				: path(path), movementSpeed(movementSpeed), animations(animations), killMoney(killMoney), enemyType(enemyType) {
			}
		};

		~Enemy() override = default;

		bool init(const EnemyDescriptor& enemyDescriptor);
		void update(float deltaMilliseconds) override;

		void receiveDamage(float damage);
		bool isDead() const { return m_isDead; }
		bool isDying() const { return m_currentAction == Action::Dying; }
		float getHealthPercentage() const { return m_currentHealth / m_maxHealth; }
		bool hasReachedTheEnd() const { return m_hasReachedTheEnd; }
		bool isFlying() { return m_enemyType == EnemyType::Wasp; }

	protected:
		static std::vector<sf::Vector2f> m_path;
		std::map<std::pair<Direction, Direction>, sf::Vector2f> m_targetOffsets;
		std::map<std::pair<Action, Direction>, std::shared_ptr<AnimationData>> m_animations;

		int m_targetIndex{ 0 };
		sf::Vector2f m_targetPos{ .0f, .0f };
		float m_pathOffset { .0f };

		float m_maxHealth{ .0f };
		float m_currentHealth{ .0f };
		bool m_isDead{ false };
		float m_movementSpeed{ .0f };
		float m_killMoney{ .0f };
		bool m_hasReachedTheEnd{ false };
		EnemyType m_enemyType;

		Action m_currentAction{ Action::Walking };
		Direction m_currentDirection{ Direction::North };

		void setTarget(const sf::Vector2f& target);
};
#pragma once

#include <Gameplay/AnimatedEntity.h>
#include <Gameplay/TowerUnit.h>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <map>
#include <utility>

class Tower : public AnimatedEntity
{
	public:
		struct TowerTierData {
			std::shared_ptr<AnimationData> towerAnimation { nullptr };   // The sprite sheet texture
			float attackDamage { 0 };
			float attackSpeed { 0 };
			float attackRange { 0 };
			float nextTierCost { 0 };
			float unitVerticalOffset{ 0 };
			TowerUnit::TowerUnitDescriptor towerUnitDescriptor;

			TowerTierData(
				const std::shared_ptr<AnimationData>& towerAnimation = nullptr,
				float attackDamage = 0,
				float attackSpeed = 0,
				float attackRange = 0,
				float nextTierCost = 0,
				float unitVerticalOffset = 0,
				TowerUnit::TowerUnitDescriptor towerUnitDescriptor = {}
			)
				: towerAnimation(towerAnimation),
				attackDamage(attackDamage),
				attackSpeed(attackSpeed),
				attackRange(attackRange),
				nextTierCost(nextTierCost),
				unitVerticalOffset(unitVerticalOffset),
				towerUnitDescriptor(towerUnitDescriptor) {
			}
		};

		struct TowerDescriptor
		{
			sf::Vector2f position { 0, 0 };
			float buildCost { 0 };
			bool canAttackFlyingEnemies{ false };
			std::vector<TowerTierData> towerDataPerTier;

			TowerDescriptor(
				const sf::Vector2f& position = { 0, 0 },
				float buildCost = 0,
				bool canAttackFlyingEnemies = false,
				const std::vector<TowerTierData>& towerDataPerTier = {}
			)
				: position(position), buildCost(buildCost), canAttackFlyingEnemies(canAttackFlyingEnemies), towerDataPerTier(towerDataPerTier) {
			}
		};

		~Tower() override = default;

		bool init(const TowerDescriptor& towerDescriptor);
		void update(float deltaMilliseconds) override;
		void render(sf::RenderWindow& window) override;

		std::pair<bool, float> upgrade(float money);

		int getCurrentTier() const { return m_currentTier; }
		float getNextTierCost() const { return m_towerDataPerTier[m_currentTier].nextTierCost; }
		float getRange() const { return m_towerDataPerTier[m_currentTier].attackRange; }
		float getSellPrice() const;
		std::vector<std::shared_ptr<TowerProjectile>> getProjectiles() const { return m_unit->getProjectiles(); }

	protected:
		int m_currentTier;
		float m_buildCost{ 0 };
		std::vector<TowerTierData> m_towerDataPerTier;
		bool m_canAttackFlyingEnemies;

		float m_currentCooldown { 0.f };

		std::unique_ptr<TowerUnit> m_unit { nullptr };
};
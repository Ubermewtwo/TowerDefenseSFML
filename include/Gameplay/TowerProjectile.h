#pragma once

#include <Gameplay/AnimatedEntity.h>
#include <Gameplay/Enemy.h>
#include <map>
#include <memory>

enum class TowerType { Archer, Mage, Catapult };

class TowerProjectile : public AnimatedEntity
{
public:

	struct TowerProjectileDescriptor
	{
		float arch{ 0.0f };
		float travelSpeed{ 0.0f };
		std::shared_ptr<AnimationData> travelAnimation;
		float areaDamageRange{ 0.0f };
		std::shared_ptr<AnimationData> impactAnimation;
		TowerType towerType;

		TowerProjectileDescriptor(float arch = 0.0f, float travelTime = 0.0f, const std::shared_ptr<AnimationData>& animation = {}, float areaDamageRange = 0.0f, const std::shared_ptr<AnimationData>& impactAnimation = {}, TowerType towerType = TowerType::Archer)
			: arch(arch), travelSpeed(travelTime), travelAnimation(animation), areaDamageRange(areaDamageRange), impactAnimation(impactAnimation), towerType(towerType) {
		}
	};

	~TowerProjectile() override = default;

	bool init(const TowerProjectileDescriptor& descriptor, const sf::Vector2f& position, float damage, const std::shared_ptr<Enemy>& targetEnemy, bool canAttackFlyingEnemies);
	void update(float deltaMilliseconds) override;
	bool isDead() const { return m_isDead; }

protected:
	sf::Vector2f m_originalPosition;
	std::shared_ptr<AnimationData> m_impactAnimation;

	float m_attackDamage{ 0.0f };
	float m_maxHeight{ 0.0f };
	float m_travelTime{ 0.0f };
	float m_elapsedTime{ 0.0f };
	float m_areaDamageRange{ 0.0f };
	bool m_hasImpacted{ false };
	bool m_isDead{ false };
	TowerType m_towerType;
	bool m_canAttackFlyingEnemies;

	sf::Vector2f m_lastPosition{ 0.0f, 0.0f };

	std::shared_ptr<Enemy> m_targetEnemy{ nullptr };

	sf::Vector2f getMovementDirection(sf::Vector2f a, sf::Vector2f b) const;
};

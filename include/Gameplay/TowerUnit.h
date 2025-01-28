#pragma once

#include <Gameplay/Enemy.h>
#include <Gameplay/TowerProjectile.h>
#include <map>
#include <memory>

class TowerUnit : public AnimatedEntity
{
public:

	struct TowerUnitDescriptor
	{
		float projectileSpawnVerticalOffset{ 0.0f };
		int attackFrameIndex{ 0 };
		std::map<std::pair<Action, Direction>, std::shared_ptr<AnimationData>> animations;
		TowerProjectile::TowerProjectileDescriptor projectileDescriptor;

		TowerUnitDescriptor(
			float projectileSpawnVerticalOffset = 0.0f, 
			int attackFrameIndex = 0, 
			const std::map<std::pair<Action, Direction>, 
			std::shared_ptr<AnimationData>>& animations = {}, const TowerProjectile::TowerProjectileDescriptor& projectileDescriptor = {}
		)
			: projectileSpawnVerticalOffset(projectileSpawnVerticalOffset), 
			attackFrameIndex(attackFrameIndex), 
			animations(animations), 
			projectileDescriptor(projectileDescriptor) {
		}
	};

	~TowerUnit() override = default;

	bool init(const TowerUnitDescriptor& descriptor, const sf::Vector2f& position, float damage, bool canAttackFlyingEnemies);
	void update(float deltaMilliseconds) override;

	void upgrade(const TowerUnitDescriptor& descriptor, const sf::Vector2f& position, float damage);
	void attack(std::shared_ptr<Enemy> targetEnemy);
	bool isAttacking() const { return m_currentAction == Action::Attacking; }
	std::vector<std::shared_ptr<TowerProjectile>> getProjectiles() const { return m_projectiles; }

protected:
	float m_projectileSpawnVerticalOffset{ 0.0f };
	int m_attackFrameIndex;
	std::map<std::pair<Action, Direction>, std::shared_ptr<AnimationData>> m_animations;
	float m_attackDamage;
	bool m_hasSpawnedProjectile{ false };
	bool m_canAttackFlyingEnemies;

	TowerProjectile::TowerProjectileDescriptor m_projectileDescriptor;
	std::vector<std::shared_ptr<TowerProjectile>> m_projectiles;

	Action m_currentAction;
	Direction m_currentDirection{ Direction::West };
	std::shared_ptr<Enemy> m_targetEnemy{ nullptr };
};

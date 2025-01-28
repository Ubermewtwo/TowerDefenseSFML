#include <Core/AssetManager.h>
#include <Core/TowerFactory.h>
#include <Gameplay/TowerUnit.h>
#include <Gameplay/TowerProjectile.h>
#include <Gameplay/AnimatedEntity.h>
#include <SFML/Graphics/Texture.hpp>

std::map<TowerType, float> TowerFactory::m_towerBuildCosts;
std::map<TowerType, std::unique_ptr<Tower::TowerDescriptor>> TowerFactory::m_towerDescriptors;

bool TowerFactory::init() {

    TowerFactory::m_towerBuildCosts[TowerType::Archer] = 70.f;
    TowerFactory::m_towerBuildCosts[TowerType::Mage] = 100.f;
    TowerFactory::m_towerBuildCosts[TowerType::Catapult] = 125.f;

    // Archer
    std::unique_ptr<Tower::TowerDescriptor> archerTowerDescriptor = std::make_unique<Tower::TowerDescriptor>();
    archerTowerDescriptor->buildCost = m_towerBuildCosts[TowerType::Archer];

    TowerUnit::TowerUnitDescriptor archerTowerTier1UnitDescriptor;
    archerTowerTier1UnitDescriptor.projectileSpawnVerticalOffset = -10.f;
    archerTowerTier1UnitDescriptor.attackFrameIndex = 5;

    archerTowerTier1UnitDescriptor.animations = {
        {{Action::Idle, Direction::North}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier1/Idle_Up.png"), 4, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Idle, Direction::South}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier1/Idle_Down.png"), 4, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Idle, Direction::East}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier1/Idle_Sideways.png"), 4, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Idle, Direction::West}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier1/Idle_Sideways.png"), 4, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Attacking, Direction::North}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier1/Attack_Up.png"), 6, sf::Vector2i(48, 48), 4.f, false)},
        {{Action::Attacking, Direction::South}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier1/Attack_Down.png"), 6, sf::Vector2i(48, 48), 4.f, false)},
        {{Action::Attacking, Direction::East}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier1/Attack_Sideways.png"), 6, sf::Vector2i(48, 48), 4.f, false)},
        {{Action::Attacking, Direction::West}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier1/Attack_Sideways.png"), 6, sf::Vector2i(48, 48), 4.f, false)}
    };

    // Projectile--------------------------------------------------------------------------------------------
    archerTowerTier1UnitDescriptor.projectileDescriptor = { 
        30.0f, 250.0f, 
        std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier1/Projectile.png"), 1, sf::Vector2i(3, 6), 0.f, true), 
        0.0f,
        std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier1/ProjectileImpact.png"), 3, sf::Vector2i(11, 11), 0.f, false),
        TowerType::Archer
    };
    // Projectile--------------------------------------------------------------------------------------------

    TowerUnit::TowerUnitDescriptor archerTowerTier2UnitDescriptor;
    archerTowerTier2UnitDescriptor.projectileSpawnVerticalOffset = -10.f;
    archerTowerTier2UnitDescriptor.attackFrameIndex = 5;

    archerTowerTier2UnitDescriptor.animations = {
        {{Action::Idle, Direction::North}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier2/Idle_Up.png"), 4, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Idle, Direction::South}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier2/Idle_Down.png"), 4, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Idle, Direction::East}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier2/Idle_Sideways.png"), 4, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Idle, Direction::West}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier2/Idle_Sideways.png"), 4, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Attacking, Direction::North}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier2/Attack_Up.png"), 6, sf::Vector2i(48, 48), 4.f, false)},
        {{Action::Attacking, Direction::South}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier2/Attack_Down.png"), 6, sf::Vector2i(48, 48), 4.f, false)},
        {{Action::Attacking, Direction::East}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier2/Attack_Sideways.png"), 6, sf::Vector2i(48, 48), 4.f, false)},
        {{Action::Attacking, Direction::West}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier2/Attack_Sideways.png"), 6, sf::Vector2i(48, 48), 4.f, false)}
    };

    // Projectile--------------------------------------------------------------------------------------------
    archerTowerTier2UnitDescriptor.projectileDescriptor = { 
        30.0f, 250.0f, 
        std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier2/Projectile.png"), 1, sf::Vector2i(3, 10), 0.f, true), 
        0.0f,
        std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier2/ProjectileImpact.png"), 3, sf::Vector2i(11, 11), 0.f, false),
        TowerType::Archer
    };
    // Projectile--------------------------------------------------------------------------------------------

    TowerUnit::TowerUnitDescriptor archerTowerTier3UnitDescriptor;
    archerTowerTier3UnitDescriptor.projectileSpawnVerticalOffset = -10.f;
    archerTowerTier3UnitDescriptor.attackFrameIndex = 5;

    archerTowerTier3UnitDescriptor.animations = {
        {{Action::Idle, Direction::North}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier3/Idle_Up.png"), 4, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Idle, Direction::South}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier3/Idle_Down.png"), 4, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Idle, Direction::East}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier3/Idle_Sideways.png"), 4, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Idle, Direction::West}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier3/Idle_Sideways.png"), 4, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Attacking, Direction::North}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier3/Attack_Up.png"), 6, sf::Vector2i(48, 48), 4.f, false)},
        {{Action::Attacking, Direction::South}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier3/Attack_Down.png"), 6, sf::Vector2i(48, 48), 4.f, false)},
        {{Action::Attacking, Direction::East}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier3/Attack_Sideways.png"), 6, sf::Vector2i(48, 48), 4.f, false)},
        {{Action::Attacking, Direction::West}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier3/Attack_Sideways.png"), 6, sf::Vector2i(48, 48), 4.f, false)}
    };

    // Projectile--------------------------------------------------------------------------------------------
    archerTowerTier3UnitDescriptor.projectileDescriptor = { 
        30.0f, 250.0f, 
        std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier3/Projectile.png"), 1, sf::Vector2i(3, 14), 0.f, true), 
        0.0f,
        std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Units/Tier3/ProjectileImpact.png"), 3, sf::Vector2i(11, 11), 0.f, false),
        TowerType::Archer
    };
    // Projectile--------------------------------------------------------------------------------------------

    archerTowerDescriptor->towerDataPerTier = {
        { std::make_shared<AnimatedEntity::AnimationData>(
            AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Idle/Idle_Tier1.png"),
            6, sf::Vector2i{70, 130}, 33.f),
            5.0f, 1.2f, 160.0f, 110.0f, -25.0f,
            std::move(archerTowerTier1UnitDescriptor)
        },
        { std::make_shared<AnimatedEntity::AnimationData>(
            AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Idle/Idle_Tier2.png"),
            6, sf::Vector2i{70, 130}, 33.f),
            9.0f, 1.6f, 200.0f, 160.0f, -25.0f,
            std::move(archerTowerTier2UnitDescriptor)
        },
        { std::make_shared<AnimatedEntity::AnimationData>(
            AssetManager::getInstance()->loadTexture("../Data/Images/Towers/ArcherTower/Idle/Idle_Tier3.png"),
            6, sf::Vector2i{70, 130}, 33.f),
            13.0f, 2.0f, 240.0f, -1.0f, -25.0f,
            std::move(archerTowerTier3UnitDescriptor)
        }
    };

    archerTowerDescriptor->canAttackFlyingEnemies = true;

    TowerFactory::m_towerDescriptors[TowerType::Archer] = std::move(archerTowerDescriptor);
    
    // Mage
    std::unique_ptr<Tower::TowerDescriptor> mageTowerDescriptor = std::make_unique<Tower::TowerDescriptor>();
    mageTowerDescriptor->buildCost = m_towerBuildCosts[TowerType::Mage];

    TowerUnit::TowerUnitDescriptor mageTowerTier1UnitDescriptor;
    mageTowerTier1UnitDescriptor.projectileSpawnVerticalOffset = -20.f;
    mageTowerTier1UnitDescriptor.attackFrameIndex = 4;

    mageTowerTier1UnitDescriptor.animations = {
        {{Action::Idle, Direction::North}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier1/Idle_Up.png"), 4, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Idle, Direction::South}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier1/Idle_Down.png"), 4, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Idle, Direction::East}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier1/Idle_Sideways.png"), 4, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Idle, Direction::West}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier1/Idle_Sideways.png"), 4, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Attacking, Direction::North}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier1/Attack_Up.png"), 6, sf::Vector2i(48, 48), 4.f, false)},
        {{Action::Attacking, Direction::South}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier1/Attack_Down.png"), 6, sf::Vector2i(48, 48), 4.f, false)},
        {{Action::Attacking, Direction::East}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier1/Attack_Sideways.png"), 6, sf::Vector2i(48, 48), 4.f, false)},
        {{Action::Attacking, Direction::West}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier1/Attack_Sideways.png"), 6, sf::Vector2i(48, 48), 4.f, false)}
    };

    // Projectile--------------------------------------------------------------------------------------------
    mageTowerTier1UnitDescriptor.projectileDescriptor = { 
        0.0f, 
        200.0f, 
        std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier1/Projectile.png"), 1, sf::Vector2i(5, 5), 0.f, true), 
        0.0f,
        std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier1/ProjectileImpact.png"), 4, sf::Vector2i(11, 11), 0.f, false),
        TowerType::Mage
    };
    // Projectile--------------------------------------------------------------------------------------------

    TowerUnit::TowerUnitDescriptor mageTowerTier2UnitDescriptor;
    mageTowerTier2UnitDescriptor.projectileSpawnVerticalOffset = -20.f;
    mageTowerTier2UnitDescriptor.attackFrameIndex = 4;

    mageTowerTier2UnitDescriptor.animations = {
        {{Action::Idle, Direction::North}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier2/Idle_Up.png"), 4, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Idle, Direction::South}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier2/Idle_Down.png"), 4, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Idle, Direction::East}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier2/Idle_Sideways.png"), 4, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Idle, Direction::West}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier2/Idle_Sideways.png"), 4, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Attacking, Direction::North}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier2/Attack_Up.png"), 6, sf::Vector2i(48, 48), 4.f, false)},
        {{Action::Attacking, Direction::South}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier2/Attack_Down.png"), 6, sf::Vector2i(48, 48), 4.f, false)},
        {{Action::Attacking, Direction::East}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier2/Attack_Sideways.png"), 6, sf::Vector2i(48, 48), 4.f, false)},
        {{Action::Attacking, Direction::West}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier2/Attack_Sideways.png"), 6, sf::Vector2i(48, 48), 4.f, false)}
    };

    // Projectile--------------------------------------------------------------------------------------------
    mageTowerTier2UnitDescriptor.projectileDescriptor = { 
        0.0f, 200.0f, 
        std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier2/Projectile.png"), 1, sf::Vector2i(5, 5), 0.f, true), 
        0.0f,
        std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier2/ProjectileImpact.png"), 4, sf::Vector2i(11, 11), 0.f, false),
        TowerType::Mage
    };
    // Projectile--------------------------------------------------------------------------------------------

    TowerUnit::TowerUnitDescriptor mageTowerTier3UnitDescriptor;
    mageTowerTier3UnitDescriptor.projectileSpawnVerticalOffset = -20.f;
    mageTowerTier3UnitDescriptor.attackFrameIndex = 4;

    mageTowerTier3UnitDescriptor.animations = {
        {{Action::Idle, Direction::North}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier3/Idle_Up.png"), 4, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Idle, Direction::South}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier3/Idle_Down.png"), 4, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Idle, Direction::East}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier3/Idle_Sideways.png"), 4, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Idle, Direction::West}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier3/Idle_Sideways.png"), 4, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Attacking, Direction::North}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier3/Attack_Up.png"), 6, sf::Vector2i(48, 48), 4.f, false)},
        {{Action::Attacking, Direction::South}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier3/Attack_Down.png"), 6, sf::Vector2i(48, 48), 4.f, false)},
        {{Action::Attacking, Direction::East}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier3/Attack_Sideways.png"), 6, sf::Vector2i(48, 48), 4.f, false)},
        {{Action::Attacking, Direction::West}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier3/Attack_Sideways.png"), 6, sf::Vector2i(48, 48), 4.f, false)}
    };

    // Projectile--------------------------------------------------------------------------------------------
    mageTowerTier3UnitDescriptor.projectileDescriptor = { 
        0.0f, 200.0f, 
        std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier3/Projectile.png"), 1, sf::Vector2i(5, 5), 0.f, true), 
        0.0f,
        std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Units/Tier3/ProjectileImpact.png"), 4, sf::Vector2i(11, 11), 0.f, false),
        TowerType::Mage
    };
    // Projectile--------------------------------------------------------------------------------------------

    mageTowerDescriptor->towerDataPerTier = {
        { std::make_shared<AnimatedEntity::AnimationData>(
            AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Idle/Idle_Tier1.png"),
            4, sf::Vector2i{70, 130}, 33.f),
            13.0f, 0.6f, 120.0f, 160.0f, -30.0f,
            std::move(mageTowerTier1UnitDescriptor)
        },
        { std::make_shared<AnimatedEntity::AnimationData>(
            AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Idle/Idle_Tier2.png"),
            4, sf::Vector2i{70, 130}, 33.f),
            33.0f, 0.65f, 140.0f, 240.0f, -35.0f,
            std::move(mageTowerTier2UnitDescriptor)
        },
        { std::make_shared<AnimatedEntity::AnimationData>(
            AssetManager::getInstance()->loadTexture("../Data/Images/Towers/MageTower/Idle/Idle_Tier3.png"),
            4, sf::Vector2i{70, 130}, 33.f),
            57.0f, 0.7f, 160.0f, -1.0f, -35.0f,
            std::move(mageTowerTier3UnitDescriptor)
        }
    };

    mageTowerDescriptor->canAttackFlyingEnemies = true;

    TowerFactory::m_towerDescriptors[TowerType::Mage] = std::move(mageTowerDescriptor);

    // Catapult
    std::unique_ptr<Tower::TowerDescriptor> catapultTowerDescriptor = std::make_unique<Tower::TowerDescriptor>();
    catapultTowerDescriptor->buildCost = m_towerBuildCosts[TowerType::Catapult];

    TowerUnit::TowerUnitDescriptor catapultTowerTier1UnitDescriptor;
    catapultTowerTier1UnitDescriptor.projectileSpawnVerticalOffset = -20.f;
    catapultTowerTier1UnitDescriptor.attackFrameIndex = 2;

    catapultTowerTier1UnitDescriptor.animations = {
        {{Action::Idle, Direction::North}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier1/Idle_Up.png"), 1, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Idle, Direction::South}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier1/Idle_Down.png"), 1, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Idle, Direction::East}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier1/Idle_Sideways.png"), 1, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Idle, Direction::West}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier1/Idle_Sideways.png"), 1, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Attacking, Direction::North}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier1/Attack_Up.png"), 6, sf::Vector2i(48, 48), 4.f, false)},
        {{Action::Attacking, Direction::South}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier1/Attack_Down.png"), 6, sf::Vector2i(48, 48), 4.f, false)},
        {{Action::Attacking, Direction::East}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier1/Attack_Sideways.png"), 6, sf::Vector2i(48, 48), 4.f, false)},
        {{Action::Attacking, Direction::West}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier1/Attack_Sideways.png"), 6, sf::Vector2i(48, 48), 4.f, false)}
    };

    // Projectile--------------------------------------------------------------------------------------------
    catapultTowerTier1UnitDescriptor.projectileDescriptor = { 
        80.0f, 100.0f, 
        std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier1/Projectile.png"), 1, sf::Vector2i(8, 8), 0.f, true), 
        50.0f,
        std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier1/ProjectileImpact.png"), 8, sf::Vector2i(48, 48), 0.f, false),
        TowerType::Catapult
    };
    // Projectile--------------------------------------------------------------------------------------------

    TowerUnit::TowerUnitDescriptor catapultTowerTier2UnitDescriptor;
    catapultTowerTier2UnitDescriptor.projectileSpawnVerticalOffset = -25.f;
    catapultTowerTier2UnitDescriptor.attackFrameIndex = 2;

    catapultTowerTier2UnitDescriptor.animations = {
        {{Action::Idle, Direction::North}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier2/Idle_Up.png"), 1, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Idle, Direction::South}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier2/Idle_Down.png"), 1, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Idle, Direction::East}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier2/Idle_Sideways.png"), 1, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Idle, Direction::West}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier2/Idle_Sideways.png"), 1, sf::Vector2i(48, 48), 4.f, true)},
        {{Action::Attacking, Direction::North}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier2/Attack_Up.png"), 6, sf::Vector2i(48, 48), 4.f, false)},
        {{Action::Attacking, Direction::South}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier2/Attack_Down.png"), 6, sf::Vector2i(48, 48), 4.f, false)},
        {{Action::Attacking, Direction::East}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier2/Attack_Sideways.png"), 6, sf::Vector2i(48, 48), 4.f, false)},
        {{Action::Attacking, Direction::West}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier2/Attack_Sideways.png"), 6, sf::Vector2i(48, 48), 4.f, false)}
    };

    // Projectile--------------------------------------------------------------------------------------------
    catapultTowerTier2UnitDescriptor.projectileDescriptor = { 
        80.0f, 100.0f, 
        std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier2/Projectile.png"), 1, sf::Vector2i(8, 8), 0.f, true), 
        50.0f,
        std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier2/ProjectileImpact.png"), 8, sf::Vector2i(48, 48), 0.f, false),
        TowerType::Catapult
    };
    // Projectile--------------------------------------------------------------------------------------------

    TowerUnit::TowerUnitDescriptor catapultTowerTier3UnitDescriptor;
    catapultTowerTier3UnitDescriptor.projectileSpawnVerticalOffset = -40.f;
    catapultTowerTier3UnitDescriptor.attackFrameIndex = 3;

    catapultTowerTier3UnitDescriptor.animations = {
        {{Action::Idle, Direction::North}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier3/Idle_Up.png"), 1, sf::Vector2i(72, 72), 16.f, true)},
        {{Action::Idle, Direction::South}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier3/Idle_Down.png"), 1, sf::Vector2i(72, 72), 16.f, true)},
        {{Action::Idle, Direction::East}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier3/Idle_Sideways.png"), 1, sf::Vector2i(72, 72), 16.f, true)},
        {{Action::Idle, Direction::West}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier3/Idle_Sideways.png"), 1, sf::Vector2i(72, 72), 16.f, true)},
        {{Action::Attacking, Direction::North}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier3/Attack_Up.png"), 8, sf::Vector2i(72, 72), 16.f, false)},
        {{Action::Attacking, Direction::South}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier3/Attack_Down.png"), 8, sf::Vector2i(72, 72), 16.f, false)},
        {{Action::Attacking, Direction::East}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier3/Attack_Sideways.png"), 8, sf::Vector2i(72, 72), 16.f, false)},
        {{Action::Attacking, Direction::West}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier3/Attack_Sideways.png"), 8, sf::Vector2i(72, 72), 16.f, false)}
    };

    // Projectile--------------------------------------------------------------------------------------------
    catapultTowerTier3UnitDescriptor.projectileDescriptor = { 
        80.0f, 100.0f, 
        std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier3/Projectile.png"), 1, sf::Vector2i(6, 6), 0.f, true), 
        50.0f,
        std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Units/Tier3/ProjectileImpact.png"), 8, sf::Vector2i(48, 48), 0.f, false),
        TowerType::Catapult
    };
    // Projectile--------------------------------------------------------------------------------------------

    catapultTowerDescriptor->towerDataPerTier = {
        { std::make_shared<AnimatedEntity::AnimationData>(
            AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Idle/Idle_Tier1.png"),
            4, sf::Vector2i{70, 130}, 33.f),
            12.0f, 0.27f, 160.0f, 220.0f, -20.0f,
            std::move(catapultTowerTier1UnitDescriptor)
        },
        { std::make_shared<AnimatedEntity::AnimationData>(
            AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Idle/Idle_Tier2.png"),
            4, sf::Vector2i{70, 130}, 33.f),
            33.0f, 0.3f, 180.0f, 320.0f, -32.0f,
            std::move(catapultTowerTier2UnitDescriptor)
        },
        { std::make_shared<AnimatedEntity::AnimationData>(
            AssetManager::getInstance()->loadTexture("../Data/Images/Towers/CatapultTower/Idle/Idle_Tier3.png"),
            6, sf::Vector2i{70, 130}, 33.f),
            45.0f, 0.33f, 200.0f, -1.0f, -45.0f,
            std::move(catapultTowerTier3UnitDescriptor)
        }
    };

    catapultTowerDescriptor->canAttackFlyingEnemies = false;


    TowerFactory::m_towerDescriptors[TowerType::Catapult] = std::move(catapultTowerDescriptor);

    return true;
}

std::pair<std::shared_ptr<Tower>, float> TowerFactory::createTower(const TowerType& towerType, const sf::Vector2f& position, float currentMoney) {
    if (currentMoney < m_towerBuildCosts[towerType]) return std::make_pair(nullptr, 0.0f);
    else {
        auto tower = std::make_shared<Tower>(); // Replace with derived classes if needed.
        Tower::TowerDescriptor towerDescriptor = *m_towerDescriptors[towerType];
        towerDescriptor.position = position;
        tower->init(towerDescriptor);
        return std::make_pair(tower, m_towerBuildCosts[towerType]);
    }
}
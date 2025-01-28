#include <Core/AssetManager.h>
#include <Core/EnemyFactory.h>
#include <Gameplay/AnimatedEntity.h>
#include <SFML/Graphics/Texture.hpp>

std::map<EnemyType, std::unique_ptr<Enemy::EnemyDescriptor>> EnemyFactory::m_enemyDescriptors;

bool EnemyFactory::init(const std::vector<sf::Vector2f>& path) {

    // Slime
    std::unique_ptr<Enemy::EnemyDescriptor> slimeDescriptor = std::make_unique<Enemy::EnemyDescriptor>();
    slimeDescriptor->path = path;
    slimeDescriptor->maxHealth = 64.0f;
    slimeDescriptor->movementSpeed = 40.0f;
    slimeDescriptor->killMoney = 9.0f;
    slimeDescriptor->enemyType = EnemyType::Slime;

    slimeDescriptor->animations = {
        {{Action::Walking, Direction::North}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Slime/Walk_Up.png"), 6, sf::Vector2i(48, 48), 8.f, true)},
        {{Action::Walking, Direction::South}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Slime/Walk_Down.png"), 6, sf::Vector2i(48, 48), 8.f, true)},
        {{Action::Walking, Direction::East}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Slime/Walk_Sideways.png"), 6, sf::Vector2i(48, 48), 8.f, true)},
        {{Action::Walking, Direction::West}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Slime/Walk_Sideways.png"), 6, sf::Vector2i(48, 48), 8.f, true)},
        {{Action::Dying, Direction::North}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Slime/Death_Up.png"), 6, sf::Vector2i(48, 48), 8.f, false)},
        {{Action::Dying, Direction::South}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Slime/Death_Down.png"), 6, sf::Vector2i(48, 48), 8.f, false)},
        {{Action::Dying, Direction::East}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Slime/Death_Sideways.png"), 6, sf::Vector2i(48, 48), 8.f, false)},
        {{Action::Dying, Direction::West}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Slime/Death_Sideways.png"), 6, sf::Vector2i(48, 48), 8.f, false)}
    };

    EnemyFactory::m_enemyDescriptors[EnemyType::Slime] = std::move(slimeDescriptor);

    // Orc
    std::unique_ptr<Enemy::EnemyDescriptor> orcDescriptor = std::make_unique<Enemy::EnemyDescriptor>();
    orcDescriptor->path = path;
    orcDescriptor->maxHealth = 192.0f;
    orcDescriptor->movementSpeed = 30.0f;
    orcDescriptor->killMoney = 15.0f;
	orcDescriptor->enemyType = EnemyType::Orc;

    orcDescriptor->animations = {
        {{Action::Walking, Direction::North}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Orc/Walk_Up.png"), 6, sf::Vector2i(48, 48), 8.f, true)},
        {{Action::Walking, Direction::South}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Orc/Walk_Down.png"), 6, sf::Vector2i(48, 48), 8.f, true)},
        {{Action::Walking, Direction::East}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Orc/Walk_Sideways.png"), 6, sf::Vector2i(48, 48), 8.f, true)},
        {{Action::Walking, Direction::West}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Orc/Walk_Sideways.png"), 6, sf::Vector2i(48, 48), 8.f, true)},
        {{Action::Dying, Direction::North}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Orc/Death_Up.png"), 6, sf::Vector2i(48, 48), 8.f, false)},
        {{Action::Dying, Direction::South}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Orc/Death_Down.png"), 6, sf::Vector2i(48, 48), 8.f, false)},
        {{Action::Dying, Direction::East}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Orc/Death_Sideways.png"), 6, sf::Vector2i(48, 48), 8.f, false)},
        {{Action::Dying, Direction::West}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Orc/Death_Sideways.png"), 6, sf::Vector2i(48, 48), 8.f, false)}
    };

    EnemyFactory::m_enemyDescriptors[EnemyType::Orc] = std::move(orcDescriptor);

    // Wolf
    std::unique_ptr<Enemy::EnemyDescriptor> wolfDescriptor = std::make_unique<Enemy::EnemyDescriptor>();
    wolfDescriptor->path = path;
    wolfDescriptor->maxHealth = 28.0f;
    wolfDescriptor->movementSpeed = 100.0f;
    wolfDescriptor->killMoney = 5.0f;
	wolfDescriptor->enemyType = EnemyType::Wolf;

    wolfDescriptor->animations = {
        {{Action::Walking, Direction::North}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Wolf/Walk_Up.png"), 6, sf::Vector2i(48, 48), 8.f, true)},
        {{Action::Walking, Direction::South}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Wolf/Walk_Down.png"), 6, sf::Vector2i(48, 48), 8.f, true)},
        {{Action::Walking, Direction::East}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Wolf/Walk_Sideways.png"), 6, sf::Vector2i(48, 48), 8.f, true)},
        {{Action::Walking, Direction::West}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Wolf/Walk_Sideways.png"), 6, sf::Vector2i(48, 48), 8.f, true)},
        {{Action::Dying, Direction::North}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Wolf/Death_Up.png"), 6, sf::Vector2i(48, 48), 8.f, false)},
        {{Action::Dying, Direction::South}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Wolf/Death_Down.png"), 6, sf::Vector2i(48, 48), 8.f, false)},
        {{Action::Dying, Direction::East}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Wolf/Death_Sideways.png"), 6, sf::Vector2i(48, 48), 8.f, false)},
        {{Action::Dying, Direction::West}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Wolf/Death_Sideways.png"), 6, sf::Vector2i(48, 48), 8.f, false)}
    };

    EnemyFactory::m_enemyDescriptors[EnemyType::Wolf] = std::move(wolfDescriptor);

    // Wasp
    std::unique_ptr<Enemy::EnemyDescriptor> waspDescriptor = std::make_unique<Enemy::EnemyDescriptor>();
    waspDescriptor->path = path;
    waspDescriptor->maxHealth = 56.0f;
    waspDescriptor->movementSpeed = 50.0f;
    waspDescriptor->killMoney = 8.0f;
	waspDescriptor->enemyType = EnemyType::Wasp;

    waspDescriptor->animations = {
        {{Action::Walking, Direction::North}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Wasp/Walk_Up.png"), 6, sf::Vector2i(48, 48), 50.f, true)},
        {{Action::Walking, Direction::South}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Wasp/Walk_Down.png"), 6, sf::Vector2i(48, 48), 50.f, true)},
        {{Action::Walking, Direction::East}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Wasp/Walk_Sideways.png"), 6, sf::Vector2i(48, 48), 50.f, true)},
        {{Action::Walking, Direction::West}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Wasp/Walk_Sideways.png"), 6, sf::Vector2i(48, 48), 50.f, true)},
        {{Action::Dying, Direction::North}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Wasp/Death_Up.png"), 6, sf::Vector2i(48, 48), 50.f, false)},
        {{Action::Dying, Direction::South}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Wasp/Death_Down.png"), 6, sf::Vector2i(48, 48), 50.f, false)},
        {{Action::Dying, Direction::East}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Wasp/Death_Sideways.png"), 6, sf::Vector2i(48, 48), 50.f, false)},
        {{Action::Dying, Direction::West}, std::make_shared<AnimatedEntity::AnimationData>(AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/Wasp/Death_Sideways.png"), 6, sf::Vector2i(48, 48), 50.f, false)}
    };

    EnemyFactory::m_enemyDescriptors[EnemyType::Wasp] = std::move(waspDescriptor);

    return true;
}

std::shared_ptr<Enemy> EnemyFactory::createEnemy(const EnemyType& enemyType, const std::vector<sf::Vector2f>& path) {
    auto enemy = std::make_shared<Enemy>(); // Replace with derived classes if needed.
    enemy->init(*EnemyFactory::m_enemyDescriptors[enemyType]);
    return enemy;
}
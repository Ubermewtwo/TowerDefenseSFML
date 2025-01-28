#pragma once
#include <SFML/Audio.hpp>
#include <Core/TowerFactory.h>
#include <Core/EnemyFactory.h>
#include <map>
#include <vector>
#include <memory>

class SoundManager
{
	public:
		static SoundManager* getInstance();

		~SoundManager();

		bool init();

		void playButtonPressedSound() { playSound(m_buttonPressedBuffer); }
		void playWavesStartSound() { playSound(m_wavesStartBuffer); }
		void playBuildSound() { playSound(m_buildBuffer); }
		void playUpgradeSound() { playSound(m_upgradeBuffer); }
		void playSellSound() { playSound(m_sellBuffer); }
		void playLoseLifeSound() { playSound(m_loseLifeBuffer); }
		void playWinSound() { playSound(m_winBuffer); }
		void playLoseSound() { playSound(m_loseBuffer); }

		void playEnemyDeathSound(EnemyType type) { playSound(m_enemyDeathBuffers[type]); }
		void playTowerAttackSound(TowerType type) { playSound(m_towerAttackBuffers[type]); }
		void playTowerProjectileHitSound(TowerType type) { playSound(m_towerProjectileHitBuffers[type]); }

	private:
		static SoundManager* s_instance;

		sf::SoundBuffer m_buttonPressedBuffer;
		sf::SoundBuffer m_wavesStartBuffer;
		sf::SoundBuffer m_buildBuffer;
		sf::SoundBuffer m_upgradeBuffer;
		sf::SoundBuffer m_sellBuffer;
		sf::SoundBuffer m_loseLifeBuffer;
		sf::SoundBuffer m_winBuffer;
		sf::SoundBuffer m_loseBuffer;

		std::map<EnemyType, sf::SoundBuffer> m_enemyDeathBuffers;
		std::map<TowerType, sf::SoundBuffer> m_towerAttackBuffers;
		std::map<TowerType, sf::SoundBuffer> m_towerProjectileHitBuffers;

		std::vector<std::unique_ptr<sf::Sound>> m_activeSounds;

		void playSound(const sf::SoundBuffer& buffer);

		void cleanupSounds();
};
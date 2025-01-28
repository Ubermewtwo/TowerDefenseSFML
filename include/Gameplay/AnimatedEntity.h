#pragma once

#include <Gameplay/GameObject.h>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <memory>

namespace sf
{
	class RenderWindow;
}

enum class Direction { North, South, East, West };
enum class Action { Idle, Walking, Attacking, Dying };

class AnimatedEntity : public GameObject
{
	public:
		struct AnimationData {
			std::shared_ptr<sf::Texture> texture{ nullptr };   // The sprite sheet texture
			int frameCount{ 0 };        // Number of frames in the sprite sheet
			sf::Vector2i frameSize; // Size of each frame (width, height)
			float verticalOffset{ .0f };  // Vertical offset from the center of the sprite sheet
			bool isLooping{ true };

			AnimationData(std::shared_ptr<sf::Texture> texture, int frameCount, sf::Vector2i frameSize, float verticalOffset = 0.0f, bool isLooping = true)
				: texture(texture), frameCount(frameCount), frameSize(frameSize), verticalOffset(verticalOffset), isLooping(isLooping) {
			}
		};

		struct AnimatedEntityDescriptor
		{
			sf::Vector2f position;
			std::shared_ptr<AnimationData> animation{ nullptr };
		};

		~AnimatedEntity() override = default;

		void setAnimation(const std::shared_ptr<AnimationData> animation);
		bool init(const sf::Vector2f& position, const std::shared_ptr<AnimationData> animation);
		virtual void update(float deltaMilliseconds) override;
		virtual void render(sf::RenderWindow& window) override;

		sf::Vector2f getSpritePosition() const {
			return sf::Vector2f(
				m_sprite.getPosition().x,
				m_sprite.getPosition().y - m_currentAnimation->verticalOffset
			);
		}


	protected:
		sf::Sprite m_sprite;
		std::shared_ptr<AnimationData> m_currentAnimation{ nullptr };

		int m_currentFrame{ 0 };
		float m_frameTimer{ .0f };
		const float m_frameDuration{ .09f };
};
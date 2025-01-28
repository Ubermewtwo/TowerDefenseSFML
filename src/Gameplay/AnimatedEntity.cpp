#include <Gameplay/AnimatedEntity.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <algorithm>

void AnimatedEntity::setAnimation(const std::shared_ptr<AnimationData> animation) {
	if (!animation) {
		std::cerr << "Error: Provided animation is null!" << std::endl;
		return; // Exit the function if the animation is invalid
	}

	m_currentAnimation = animation;

	if (!m_currentAnimation->texture) {
		std::cerr << "Error: Animation texture is null!" << std::endl;
		return; // Exit the function if the texture is null
	}

	m_sprite.setTexture(*m_currentAnimation->texture); // Line with the error
	m_sprite.setOrigin(m_currentAnimation->frameSize.x / 2.f, m_currentAnimation->frameSize.y / 2.f + m_currentAnimation->verticalOffset);
	if (m_currentAnimation->isLooping) {
		m_currentFrame = std::min(m_currentFrame, m_currentAnimation->frameCount - 1);
	}
	else {
		m_currentFrame = 0;
	}
}

bool AnimatedEntity::init(const sf::Vector2f& position, const std::shared_ptr<AnimationData> animation) {
	m_position = position;
	m_sprite.setPosition(position);
	setAnimation(animation);

	return true;
}

void AnimatedEntity::update(float deltaMilliseconds) {
	float deltaSeconds = deltaMilliseconds / 1000.f;

	m_sprite.setPosition(m_position);

	// Change current frame based on elapsed time
	m_frameTimer += deltaSeconds;
	if (m_frameTimer >= m_frameDuration) {
		m_frameTimer = 0;
		if (m_currentAnimation->isLooping) {
			m_currentFrame = (m_currentFrame + 1) % m_currentAnimation->frameCount;
		}
		else {
			m_currentFrame = std::min(m_currentFrame + 1, m_currentAnimation->frameCount - 1);
		}
	}

	// Update rect based on current frame
	m_sprite.setTextureRect(sf::IntRect(
		m_currentFrame * m_currentAnimation->frameSize.x,
		0,
		m_currentAnimation->frameSize.x,
		m_currentAnimation->frameSize.y
	));
}

void AnimatedEntity::render(sf::RenderWindow& window) {
	window.draw(m_sprite);
}
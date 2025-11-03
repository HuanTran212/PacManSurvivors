#include "Animator.h"

Animator::Animator(sf::Sprite& sprite)
	: m_sprite(sprite), m_frameTime(0.1f), m_timer(0.f), m_currentFrame(0), m_currentAnimation("")
{
}
void Animator::addAnimation(const std::string& name, const std::vector<sf::IntRect>& frames, float frameTime)
{
	m_animations[name] = frames;
	if (m_currentAnimation.empty())
	{
		m_currentAnimation = name;
		m_frameTime = frameTime;
		m_sprite.setTextureRect(m_animations[m_currentAnimation][0]);
	}
}
void Animator::play(const std::string& name)
{
	if (m_currentAnimation != name && m_animations.find(name) != m_animations.end())
	{
		m_currentAnimation = name;
		m_currentFrame = 0;
		m_timer = 0.f;
		m_sprite.setTextureRect(m_animations[m_currentAnimation][0]);
	}
}

void Animator::update(float dt)
{
	if (m_currentAnimation.empty())
		return;
	m_timer += dt;
	if (m_timer >= m_frameTime)
	{
		m_timer -= m_frameTime;
		m_currentFrame++;
		if (m_currentFrame >= m_animations[m_currentAnimation].size())
		{
			m_currentFrame = 0; //Trở về frame 0
		}
		m_sprite.setTextureRect(m_animations[m_currentAnimation][m_currentFrame]);
	}
}

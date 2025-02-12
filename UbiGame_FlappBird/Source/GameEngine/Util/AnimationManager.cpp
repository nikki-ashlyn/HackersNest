#include "AnimationManager.h"


using namespace GameEngine;

AnimationManager* AnimationManager::sm_instance = nullptr;

AnimationManager::AnimationManager()
{

}


AnimationManager::~AnimationManager()
{

}


void AnimationManager::InitStaticGameAnimations()
{
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::BirdIdle,
			eTexture::PlayerIdle,
			sf::Vector2i(0, 0),
			1,
			1)
	);

	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::BirdFly,
			eTexture::Player,
			sf::Vector2i(0,0),
			8,
			15)
	);

	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::Smoke,
			eTexture::Particles,
			sf::Vector2i(0, 0),
			10,
			15)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::GoodBlock,
			eTexture::Good,
			sf::Vector2i(0, 0),
			1,
			1)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::BadBlock,
			eTexture::Bad,
			sf::Vector2i(0, 0),
			1,
			1)
	);
}


void AnimationManager::ReleaseStaticGameAnimations()
{
	m_animDefinitions.clear();
}


const SAnimationDefinition* AnimationManager::GetAnimDefinition(EAnimationId::type animId) const
{
	for (int a = 0; a < m_animDefinitions.size(); ++a)
	{
		if (m_animDefinitions[a].m_animId == animId)
			return &m_animDefinitions[a];
	}

	return nullptr;
}

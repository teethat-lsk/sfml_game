#pragma once
#include "Enemy.h"
class Boss :
	public Enemy
{
private:
	void initializeVariables();
	bool attack;
	sf::SoundBuffer attackbuffer;
	sf::Sound attacksound;

public:
	Boss(float speed, float hp, float x, float y, sf::Texture& texture_sheet);
	virtual ~Boss();

	
	void updateAnimation(const float& deltaTime);
	void Attack(const float& deltaTime);
	void update(const float& deltaTime);
	const sf::Vector2f getPosition();
	const sf::Vector2f& getHitboxPosition() const;
	const sf::FloatRect getHitboxGlobalBound() const;

	float getHealth();
};


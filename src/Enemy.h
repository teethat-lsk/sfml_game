#pragma once
#include "Player.h"


class Enemy :
	public Entity
{
private:
	virtual void initializeVariables() = 0;
	
	
public:
	Enemy(float x, float y, sf::Texture& texture_sheet);
	virtual ~Enemy();

	//Function
	

	virtual void updateAnimation(const float& deltaTime) = 0;
	virtual void update(const float& deltaTime)=0;
	virtual void render(sf::RenderTarget &target);
	
	const sf::Vector2f& getHitboxPosition() const;
	const sf::FloatRect getHitboxGlobalBound() const;
	
};


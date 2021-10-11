#pragma once
#include "Entity.h"
class Enemy :
	public Entity
{
private:
	virtual void initializeVariables() = 0;
	virtual void initializeAnimations() = 0;

		
	void updateMovement();

public:
	Enemy();
	virtual ~Enemy();

	//Functions
	virtual void updateAnimation(const float& deltaTime) = 0;

	virtual void update(const float& deltaTime) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
};



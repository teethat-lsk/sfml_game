#pragma once
#include"MovementComponent.h"
#include"AnimationComponent.h"
#include"HitboxComponent.h"
#include<SFML\System.hpp>
#include"Health.h"
#include<cstdlib>
#include<stdlib.h>

#include<math.h>
class Entity
{
private:
	void initializeVariable();

protected:
	
	sf::Sprite sprite;
	
	MovementComponent* movementComponent; 
	AnimationComponent* animationComponent;
	HitboxComponent* hitboxComponent;

public:
	Entity();
	virtual ~Entity();
	Health* health;
	
	//Component functions
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity, const float acceration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	
	

	//function
	virtual void setPosition(const float x, const float y);
	virtual void move( const float x, const float y,const float& dealtaTime);

	virtual const sf::Vector2f getPosition() =0;
	virtual void update(const float& deltaTime);
	virtual void render(sf::RenderTarget& target);
	
	
	virtual sf::Vector2f getHbcenter();
	virtual sf::Vector2f getHbrad();
	

};


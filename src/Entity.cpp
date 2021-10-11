#include "Entity.h"

void Entity::initializeVariable()
{
	
	this->movementComponent = nullptr;
	this->animationComponent = nullptr;
	this->hitboxComponent = nullptr;
}
 
Entity::Entity()
{
	this->initializeVariable();
	
}

Entity::~Entity()
{
	delete this->hitboxComponent;
	delete this->movementComponent;
	delete this->animationComponent;
}

//Component funtions
void Entity::setTexture(sf::Texture& texture)
{
	
	this->sprite.setTexture(texture);
}

void Entity::createMovementComponent(const float maxVelocity,const float acceration,const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite,maxVelocity,acceration,deceleration);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->animationComponent= new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offset_x,offset_y,width,height);
}



//Functions
void Entity::setPosition(const float x, const float y)
{
	
		this->sprite.setPosition(x, y);
	
}


void Entity::move( const float dir_x, const float dir_y,const float& deltaTime)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(dir_x, dir_y,deltaTime); //Set Velocity
		
	}
}

void Entity::update(const float& deltaTime)
{
	
}

void Entity::render(sf::RenderTarget& target)
{
	
		target.draw(this->sprite); //target = window => target->draw = window->draw
		if (this->hitboxComponent)
			this->hitboxComponent->render(target);
		
}



sf::Vector2f Entity::getHbcenter()
{
	return this->hitboxComponent->getHbcenter();
}


sf::Vector2f Entity::getHbrad()
{
	return this->hitboxComponent->getHbrad();
}





	

 
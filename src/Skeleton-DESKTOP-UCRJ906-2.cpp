#include "Skeleton.h"

void Skeleton::initializeVariables()
{

}

	
Skeleton::Skeleton(float speed,float hp,float x, float y, sf::Texture& texture_sheet)
	:Enemy(x,y,texture_sheet)
{	
	
	this->health = new Health(/*hp*/hp,/*BARwidth*/45, /*BARheight*/10, /*scale*/sf::Vector2f(0.125, 0.125));
	//this->attackbuffer.loadFromFile("Resource/Sound");
	this->initializeVariables();
	this->setPosition(x, y);
	this->createMovementComponent(speed, 10.f, 5.f);
	this->createAnimationComponent(texture_sheet);
	this->createHitboxComponent(this->sprite, 10.f, 50.f, 30.f, 60.f);

	this->animationComponent->addAnimation("IDLE", 25.f, 0, 2, 15, 2, texture_sheet.getSize().x / 18, texture_sheet.getSize().y / 3);

	this->animationComponent->addAnimation("WALK", 20.f, 0, 1, 12, 1, texture_sheet.getSize().x / 18, texture_sheet.getSize().y / 3);
	 
	this->animationComponent->addAnimation("ATTACK", 3.f, 0, 0, 17, 0, texture_sheet.getSize().x / 18, texture_sheet.getSize().y / 3);

	//this->animationComponent->addAnimation("DEAD",25.f, texture_sheet.getSize().x / 18, texture_sheet.getSize().y / 3)

	this->sprite.setScale(3, 3);
}

Skeleton::~Skeleton()
{
}



void Skeleton::stopmoving()
{
	this->movementComponent->stopmoving();
}

void Skeleton::updateAnimation(const float& deltaTime)
{
	if (this->movementComponent->getMovingState(IDLE))
	{
		this->attack = 1;
		if (this->attack) 
		{
			this->attack = 0;
			this->animationComponent->play("ATTACK", deltaTime);
		}
	}
	if (this->movementComponent->getMovingState(MOVING_RIGHT))
	{
		if (this->sprite.getScale().x < 0.f)
		{
			this->sprite.setOrigin(0, 0);
			this->sprite.setScale(3.f, 3.f);
		}
		this->animationComponent->play("WALK", deltaTime, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	if (this->movementComponent->getMovingState(MOVING_LEFT))
	{
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(20, 0);
			this->sprite.setScale(-3.f, 3.f);
		}
		this->animationComponent->play("WALK", deltaTime, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	if (this->movementComponent->getMovingState(MOVING_UP))
	{
		this->animationComponent->play("WALK", deltaTime, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	if (this->movementComponent->getMovingState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK", deltaTime, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	
}

void Skeleton::Attack(const float& deltaTime)
{
	
	this->animationComponent->play("ATTACK", deltaTime);
		
			std::cout << "ATTACK" << std::endl;
		
		
	
	
}


void Skeleton::update(const float& deltaTime)
{
	
	this->movementComponent->update(deltaTime);
	//this->updateAttack(deltaTime);
	this->updateAnimation(deltaTime);
	this->hitboxComponent->update();
	this->health->update(this->sprite.getPosition().x - 20.f, this->sprite.getPosition().y - 10, this->sprite.getPosition().x-10 , this->sprite.getPosition().y - 8);
}

const sf::Vector2f Skeleton::getPosition()
{
	return sf::Vector2f(this->sprite.getPosition().x,this->sprite.getPosition().y);
}



const sf::Vector2f& Skeleton::getHitboxPosition() const
{
	return this->hitboxComponent->getPosition();
	// TODO: insert return statement here
}

const sf::FloatRect Skeleton::getHitboxGlobalBound() const
{
	return this->hitboxComponent->getGlobalBound();
}

float Skeleton::getHealth()
{
	return this->health->getHealth();
}

//void Skeleton::render(sf::RenderTarget& target)
//{
//	target.draw(this->sprite);
//}

//void Skeleton::set_pt(Player* inp)
//{
//
//	player = inp;
//
//}


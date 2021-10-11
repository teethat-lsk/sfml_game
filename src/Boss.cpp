#include "Boss.h"

void Boss::initializeVariables()
{
}

Boss::Boss(float speed, float hp, float x, float y, sf::Texture& texture_sheet)
	:Enemy(x, y, texture_sheet)
{
	this->health = new Health(/*hp*/hp,/*BARwidth*/195, /*BARheight*/45, /*scale*/sf::Vector2f(0.5, 0.5));
	//this->attackbuffer.loadFromFile("Resource/Sound");
	this->initializeVariables();
	this->setPosition(x, y);
	this->createMovementComponent(speed, 10.f, 5.f);
	this->createAnimationComponent(texture_sheet);
	this->createHitboxComponent(this->sprite, 30.f, 130.f, 60.f, 120.f);

	this->animationComponent->addAnimation("IDLE", 25.f, 0, 2, 15, 2, texture_sheet.getSize().x / 18, texture_sheet.getSize().y / 3);

	this->animationComponent->addAnimation("WALK", 20.f, 0, 2, 12, 2, texture_sheet.getSize().x / 18, texture_sheet.getSize().y / 3);

	this->animationComponent->addAnimation("ATTACK", 13.f, 0, 0, 17, 0, texture_sheet.getSize().x / 18, texture_sheet.getSize().y / 3);

	this->sprite.setScale(1, 1);
}

Boss::~Boss()
{
	delete this->health;
}

void Boss::updateAnimation(const float& deltaTime)
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
			this->sprite.setScale(1.f, 1.f);
		}
		this->animationComponent->play("WALK", deltaTime, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	if (this->movementComponent->getMovingState(MOVING_LEFT))
	{
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(80, 0);
			this->sprite.setScale(-1.f, 1.f);
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

void Boss::Attack(const float& deltaTime)
{
}

void Boss::update(const float& deltaTime)
{
	this->movementComponent->update(deltaTime);
	//this->updateAttack(deltaTime);
	this->updateAnimation(deltaTime);
	this->hitboxComponent->update();
	this->health->update(this->sprite.getPosition().x - 20.f, this->sprite.getPosition().y - 10, this->sprite.getPosition().x+5 , this->sprite.getPosition().y);
}

const sf::Vector2f Boss::getPosition()
{
	return sf::Vector2f(this->sprite.getPosition().x, this->sprite.getPosition().y);
}

const sf::Vector2f& Boss::getHitboxPosition() const
{
	return this->hitboxComponent->getPosition();
}

const sf::FloatRect Boss::getHitboxGlobalBound() const
{
	return sf::FloatRect();
}

float Boss::getHealth()
{
	return this->health->getHealth();
}
